#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

#include "renderable.h"
#include "cooldown.h"

class Snake : public Renderable {

 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2), type(None) {}

  void Update();
  void Render(SDL_Renderer *sdl_renderer, SDL_Rect &block, int screenWidth,
              int screenHeight) override;
  void GrowBody(int length);
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  CoolDownType type;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int growing{0};
  int grid_width;
  int grid_height;
};

#endif