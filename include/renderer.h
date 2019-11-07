#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>
#include "collectable.h"
#include "snake.h"
#include "renderable.h"
#include "cooldown.h"

class Renderer {

public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);

    ~Renderer();

    void Render(Snake &snake, std::vector<Collectable> &, CoolDown &);

    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif