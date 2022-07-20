#pragma once
#define PLAYERS 5
#define PROPABILITY 30 //probability of the game to change crystal position
#include <utility>

typedef std::pair<int, int> Position;

typedef enum
{
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE
} Color;

typedef enum
{
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE
} Control;