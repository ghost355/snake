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

void any_text_render(char* str_array, SDL_Renderer* renderer, TTF_Font* font,
                     SDL_Color color, int x, int y)
{
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, str_array, 0, color);
    SDL_Texture* scoreTexture
      = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_DestroySurface(scoreSurface);
    SDL_FRect scoreRect = { x, y, scoreTexture->w, scoreTexture->h };
    SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
}

void render_text(Game* game)
{
    SDL_Color white = { 255, 255, 255, 255 };
    char      timer[32];
    snprintf(timer, sizeof(timer), "Timer: %04d", game->score);
    any_text_render(timer, game->renderer, game->font, white, 600, 10);

    char score_label[32];
    snprintf(score_label, sizeof(score_label), "Score: %04d", game->score);
    any_text_render(score_label, game->renderer, game->font, white, 10, 10);

    char length_label[32];
    snprintf(length_label, sizeof(length_label), "Snake length: %02d",
             game->snake.length);
    any_text_render(length_label, game->renderer, game->font, white, 250, 10);
}

void render_border(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_FRect border_rect = { area_x, area_y, area_w, area_h };
    SDL_RenderRect(game->renderer, &border_rect);
}
