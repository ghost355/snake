#include "../include/render.h"
#include <SDL3_ttf/SDL_ttf.h>

void render_snake(Game* game);
void render_fruit(Game* game);
void render_text(Game* game);
void render_border(Game* game);

void render(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    render_snake(game);
    render_fruit(game);
    render_text(game);
    render_border(game);

    SDL_RenderPresent(game->renderer);
    SDL_Delay(1000 / 15);
}

void render_snake(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_FRect head_rect
      = { game->snake.head.x, game->snake.head.y, grid_size, grid_size };
    SDL_RenderFillRect(game->renderer, &head_rect);
    for (int i = 0; i < game->snake.length; i++) {
        SDL_FRect body_rect = { game->snake.body[i].x, game->snake.body[i].y,
                                grid_size, grid_size };
        SDL_RenderFillRect(game->renderer, &body_rect);
    }
}

void render_fruit(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    SDL_FRect fruit_rect
      = { game->fruit.x, game->fruit.y, grid_size, grid_size };
    SDL_RenderFillRect(game->renderer, &fruit_rect);
}

void render_text(Game* game)
{
    snprintf(game->label->score_label, sizeof(game->label->score_label),
             "Score: %d", game->score);
    SDL_Surface* scoreSurface
      = TTF_RenderText_Solid(game->font, game->label->score_label, 0,
                             (SDL_Color) { 255, 255, 255, 255 });
    SDL_Texture* scoreTexture
      = SDL_CreateTextureFromSurface(game->renderer, scoreSurface);
    SDL_DestroySurface(scoreSurface);
    SDL_FRect scoreRect = { 0, 0, scoreTexture->w, scoreTexture->h };
    SDL_RenderTexture(game->renderer, scoreTexture, NULL, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
}

void render_border(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_FRect border_rect = { area_x, area_y, area_w, area_h };
    SDL_RenderRect(game->renderer, &border_rect);
}
