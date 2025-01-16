#include "../include/render.h"

void render_snake(Snake* snake);
void render_fruit(Fruit* fruit);

void render(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

    SDL_RenderClear(game->renderer);
    render_snake(&game->snake);
    render_fruit(&game->fruit);

    SDL_RenderPresent(game->renderer);
}
