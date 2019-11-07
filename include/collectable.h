//
// Created by Fang Han on 11/6/19.
//

#ifndef SUPERSNAKE_COLLECTABLE_H
#define SUPERSNAKE_COLLECTABLE_H

#include <memory>
#include <vector>

#include "renderable.h"
#include "types.h"


class Collectable : public Renderable {

public:
  Collectable(const SnakeGamePos &pos, CollectableType type);

  void Render(SDL_Renderer *sdl_renderer, SDL_Rect &block, int screenWidth,
              int screenHeight) override;

  void Update();

  // getters and setters
  [[nodiscard]] const SnakeGamePos &GetPos() const;
  CollectableType GetType() const;

private:
  SnakeGamePos _pos;
  CollectableType _type;

  SDL_Color _color;
};

typedef std::vector<Collectable> CollectablesContainer;
typedef std::vector<Collectable>::iterator CollectableIter;

#endif //SUPERSNAKE_COLLECTABLE_H
