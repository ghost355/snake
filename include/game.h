#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>

#define screen_width 800
#define screen_height 600
#define grid_size 10
#define initial_len 2
#define max_lenght 100

typedef struct Point
{
    int x, y;
} Point;

typedef enum Direction
{
    Up,
    Down,
    Left,
    Right
} Direction;

typedef struct Snake
{
    Point     head;
    Point     body[max_lenght];
    Direction direction;
    int       length;
} Snake;

typedef struct Game
{
    SDL_Window*   window;
    SDL_Renderer* renderer;
    Snake         snake;
    Point         fruit;
    int           score;
    bool          running;
    bool          fruit_eaten;
    // TODO add State to Game and enum for States
} Game;

bool game_init(Game* game);

void run_game(Game* game);

void quit_game(Game* game);

#endif
