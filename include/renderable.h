//
// Created by Fang Han on 11/6/19.
//

#ifndef SUPERSNAKE_RENDERABLE_H
#define SUPERSNAKE_RENDERABLE_H

#include <SDL_render.h>

// interfaces
class Renderable {
public:
  virtual void Render(SDL_Renderer *sdl_renderer, SDL_Rect &block,
                      int screenWidth, int screenHeight) = 0;
};

#endif // SUPERSNAKE_RENDERABLE_H
