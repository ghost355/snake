#include "../include/game.h"
#include "SDL3/SDL_log.h"

bool game_init(Game* game)
{

    if (!(SDL_Init(SDL_INIT_VIDEO))) {
        SDL_Log("SDL initialized failed %s", SDL_GetError());
        return false;
    }
    else if (!(game->window
               = SDL_CreateWindow("snake", screen_width, screen_height, 0))) {
        SDL_Log("SDL Window creation failed %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    if (!(game->renderer = SDL_CreateRenderer(game->window, 0))) {
        SDL_Log("SDL Renderer creation failed %s", SDL_GetError());
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        return false;
    }

    Snake snake = {
        { screen_width / 2, screen_height / 2 },
        NULL, Right
    };
    Fruit fruit = {
        { 0, 0 }
    };

    game->snake   = snake;
    game->fruit   = fruit;
    game->score   = 0;
    game->running = true;

    return true;
}

void run_game(Game* game)
{
    input_handle(game);
    update(game);
    render(game);
}

void quit_game(Game* game)
{
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
}
