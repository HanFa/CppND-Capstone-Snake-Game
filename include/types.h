//
// Created by Fang Han on 11/6/19.
//

#ifndef SUPERSNAKE_TYPES_H
#define SUPERSNAKE_TYPES_H

enum CollectableType {
  Coffee, Marijuana, Alcohol, Coin, Food
};

enum CoolDownType {
  Poisoned, Drunk, Chill, None
};

struct SnakeGamePos {
  int x;
  int y;
};

#endif // SUPERSNAKE_TYPES_H
