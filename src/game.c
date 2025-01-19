#include "../include/game.h"
#include "../include/logic.h"
#include "../include/render.h"
#include "SDL3/SDL_log.h"
#include "SDL3_ttf/SDL_ttf.h"

bool game_init(Game* game)
{

    if (!(SDL_Init(SDL_INIT_VIDEO))) {
        SDL_Log("SDL initialized failed %s", SDL_GetError());
        return false;
    }
    if (!(TTF_Init())) {
        SDL_Log("TTF initialized failed %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    if (!(game->window
          = SDL_CreateWindow("snake", screen_width, screen_height, 0))) {
        SDL_Log("SDL Window creation failed %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    if (!(game->renderer = SDL_CreateRenderer(game->window, 0))) {
        SDL_Log("SDL Renderer creation failed %s", SDL_GetError());
        SDL_DestroyWindow(game->window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    if (!(game->font
          = TTF_OpenFont("/Users/pavel/github/snake/font/font.ttf", 32))) {
        SDL_Log("Can't open font: %s", SDL_GetError());
        return false;
    }


    Snake snake = {
        .head      = { screen_width / 2, screen_height / 2 },
        .direction = Right,
        .length    = initial_len
    };

    for (int i = 0; i < initial_len; i++) {
        snake.body[i].x = snake.head.x - i * grid_size;
        snake.body[i].y = snake.head.y;
    }

    game->snake       = snake;
    game->fruit       = (Point) { 0, 0 };
    game->score       = 0;
    game->timer       = 0;
    game->last_time   = 0;
    game->running     = true;
    game->fruit_eaten = true;
    return true;
}

void run_game(Game* game)
{
    SDL_Event event;
    SDL_zero(event);
    game->last_time = SDL_GetTicks();

    while (game->running) {
        input_handle(game, &event);
        update(game);
        render(game);
    }
}

void quit_game(Game* game)
{
    TTF_CloseFont(game->font);
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    TTF_Quit();
    SDL_Quit();
}
