#ifndef GAME_H
#define GAME_H


#include <memory>
#include <random>
#include <vector>
#include <thread>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"

#include "snake.h"
#include "collectable.h"
#include "cooldown.h"


class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  virtual ~Game();

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  SnakeGamePos GetRandomNonSnakePos();
  CollectableIter CheckIsThereCollect(const SnakeGamePos & pos);
  void PlaceCollectableRandomly(CollectableType type);
  void Update();


  // getters and setters
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  CollectablesContainer collectables;
  CoolDown coolDown;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  std::atomic_bool shouldStopSpawn = false;
  std::mutex mutex;
  std::condition_variable cv;

};

#endif