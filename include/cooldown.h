//
// Created by Fang Han on 11/6/19.
//

#ifndef SUPERSNAKE_COOLDOWN_H
#define SUPERSNAKE_COOLDOWN_H

#include "renderable.h"
#include "types.h"

class CoolDown : public Renderable {

public:
  CoolDown(float timeLeft, const SDL_Color &color);

  void StartCountDown(float numFrames, CoolDownType type);

  void Render(SDL_Renderer *renderer, SDL_Rect &rect, int screenWidth,
              int screenHeight) override;

  void Update();

  CoolDownType GetType() const;

private:
  float _maxFrameLeft;
  float _frameLeft;
  CoolDownType _type;
  SDL_Color _color;

};

#endif // SUPERSNAKE_COOLDOWN_H
