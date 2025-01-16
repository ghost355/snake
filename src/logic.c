#include "../include/logic.h"
#include "SDL3/SDL_events.h"

void input_handle(Game* game, SDL_Event* event)
{
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_EVENT_QUIT) {
            game->running = false;
        }
        if (event->type == SDL_EVENT_KEY_DOWN) {
            switch (event->key.key) {
            case SDLK_UP: game->snake.direction = Up; break;
            case SDLK_DOWN: game->snake.direction = Down; break;
            case SDLK_LEFT: game->snake.direction = Left; break;
            case SDLK_RIGHT: game->snake.direction = Right; break;
            case SDLK_ESCAPE: game->running = false; break;
            default: break;
            }
        }
    }
}

void update(Game* game) { }

void render(Game* game) { }
