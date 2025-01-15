#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>

typedef struct Point {
  int x, y;
} Point;

typedef enum Direction { Up, Down, Left, Right } Direction;

typedef struct Snake {
  Point head;
  Point *body;
  Direction direction;
} Snake;

typedef struct Fruit {
  Point fruit;
} Fruit;

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Snake snake;
  Fruit fruit;
  int score;
} Game

#endif
