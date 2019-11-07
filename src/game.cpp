
#include <SDL.h>
#include <condition_variable>
#include <future>
#include <iostream>
#include <thread>

#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(grid_width) - 1),
      random_h(0, static_cast<int>(grid_height) - 1),
      coolDown(5.0, {128, 128, 128, 128}) {
  PlaceCollectableRandomly(CollectableType::Food);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  shouldStopSpawn = false;

  std::thread spawnCollectables = std::thread([&]() {
    while (not shouldStopSpawn) {
      std::unique_lock<std::mutex> lck(mutex);

      auto type = static_cast<CollectableType>(rand() % 2);

      PlaceCollectableRandomly(type);

      cv.wait_for(lck, std::chrono::seconds(10),
                  [&]() { return shouldStopSpawn == true; });
    }
  });

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, collectables, coolDown);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  std::unique_lock<std::mutex> lck(mutex);
  shouldStopSpawn = true;
  lck.unlock();
  cv.notify_all();

  spawnCollectables.join();
}

void Game::PlaceCollectableRandomly(CollectableType type) {
  collectables.emplace_back(GetRandomNonSnakePos(), type);
}

CollectableIter Game::CheckIsThereCollect(const SnakeGamePos &pos) {
  for (auto it = collectables.begin(); it != collectables.end(); ++it) {
    if (it->GetPos().x == pos.x and it->GetPos().y == pos.y)
      return it;
  }
  return collectables.end();
}

void Game::Update() {
  if (!snake.alive)
    return;

  snake.type = coolDown.GetType();
  snake.Update();
  coolDown.Update();
  for (auto &c : collectables) {
    c.Update();
  }

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there any collectables over here
  auto it = CheckIsThereCollect({new_x, new_y});
  if (it != collectables.end()) {

    std::unique_lock<std::mutex> lck(mutex);
    auto collectable = std::move(*it);
    auto type = collectable.GetType();
    collectables.erase(it);
    lck.unlock();

    if (type == CollectableType::Alcohol) {
      coolDown.StartCountDown(10.0f * 60, Drunk);

    } else if (type == CollectableType::Coffee) {
      // get a coffee to cool down
      coolDown.StartCountDown(10.0f * 60, Chill);
    } else if (type == CollectableType::Coin) {

    } else if (type == CollectableType::Marijuana) {
      coolDown.StartCountDown(10.0f * 60, Poisoned);
      for (int i = 0; i < 5; ++ i) {
        snake.GrowBody(1);
        snake.speed += 0.02;
        score += 10;
      }
    } else if (type == CollectableType::Food) {
      // Grow snake and increase speed.
      snake.GrowBody(1);
      snake.speed += 0.02;
      score += 10;
      std::unique_lock<std::mutex> lck(mutex);
      PlaceCollectableRandomly(CollectableType::Food);
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

Game::~Game() {}

SnakeGamePos Game::GetRandomNonSnakePos() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      return {x, y};
    }
  }
}
