#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define screen_width 800
#define screen_height 600
#define grid_size 30
#define initial_len 2
#define max_lenght 100

#define area_x 10
#define area_y 50
#define area_w (screen_width - area_x)
#define area_h (screen_height - area_y)

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

typedef struct Text
{
    char score_label[32];
    char length_label[32];
} Text;

typedef struct Game
{
    SDL_Window*   window;
    SDL_Renderer* renderer;
    TTF_Font*     font;
    Snake         snake;
    Point         fruit;
    int           score;
    bool          running;
    bool          fruit_eaten;
    Text*         label;
    // TODO add State to Game and enum for States
} Game;

bool game_init(Game* game);

void run_game(Game* game);

void quit_game(Game* game);

#endif
