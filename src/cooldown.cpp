//
// Created by Fang Han on 11/6/19.
//

#include <SDL.h>
#include <future>
#include <iostream>
#include <thread>

#include "cooldown.h"

CoolDown::CoolDown(float timeLeft, const SDL_Color &color)
    : _maxFrameLeft(timeLeft), _frameLeft(timeLeft), _color(color), _type(None)
    {}

void CoolDown::Render(SDL_Renderer *renderer, SDL_Rect &rect, int screenWidth,
                      int screenHeight) {
  if (_type == None) return;

  SDL_Rect bar;
  bar.w = (int)((_frameLeft / _maxFrameLeft) * (float)screenWidth);
  bar.h = 10;
  bar.x = 0;
  bar.y = 0;

  if (_type == Chill) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x4F);
  } else if (_type == Poisoned) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x4F);
  }

  SDL_RenderFillRect(renderer, &bar);
}

void CoolDown::StartCountDown(float numFrames, CoolDownType type) {
  assert(type != None);
  _type = type;
  _frameLeft = _maxFrameLeft = numFrames;
}


void CoolDown::Update() {
  if (_type != None and _frameLeft > 0) {
    _frameLeft -= 1;
  } else if (_type != None and _frameLeft <= 0) {
    _type = None;
  }
}

CoolDownType CoolDown::GetType() const { return _type; }
