#include "../include/render.h"

void render_snake(Game *game);
void render_fruit(Game *game);

void render(Game *game) {
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

  SDL_RenderClear(game->renderer);
  render_snake(game);
  /* render_fruit(game); */

  SDL_RenderPresent(game->renderer);
}

void render_snake(Game *game) {
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
  SDL_FRect head_rect = {game->snake.head.x, game->snake.head.y, grid_size,
                         grid_size};
  SDL_RenderFillRect(game->renderer, &head_rect);
  for (int i = 0; i < game->snake.length; i++) {
    SDL_FRect body_rect = {game->snake.body[i].x, game->snake.body[i].y,
                           grid_size, grid_size};
    SDL_RenderFillRect(game->renderer, &body_rect);
  }
}
