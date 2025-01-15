#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>

#define screen_width 800
#define screen_height 600
#define grid_size 10

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
  bool running;
  // TODO add State to Game and enum for States
} Game;

bool game_init(Game *game);

void run_game(Game *game);

void quit_game(Game *game);

#endif
