//
// Created by Fang Han on 11/6/19.
//
#include <iostream>

#include "collectable.h"

Collectable::Collectable(const SnakeGamePos &pos, CollectableType type)
    : _pos(pos), _type(type) {
  if (_type == Food)
    _color = {0xFF, 0x88, 0x00, 0xFF};
  else if (_type == Coffee)
    _color = {0x00, 0x00, 0xFF, 0xFF};
  else if (_type == Marijuana)
    _color = {0xFF, 0x00, 0x00, 0xFF};

}

const SnakeGamePos &Collectable::GetPos() const { return _pos; }
CollectableType Collectable::GetType() const { return _type; }



void Collectable::Render(SDL_Renderer *sdl_renderer, SDL_Rect &block,
                         int screenWidth, int screenHeight) {

  SDL_SetRenderDrawColor(sdl_renderer, _color.r, _color.g, _color.b, _color.a);

  block.x = _pos.x * block.w;
  block.y = _pos.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);



}
void Collectable::Update() {


}
