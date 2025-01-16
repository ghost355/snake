#include "../include/logic.h"
#include "SDL3/SDL_events.h"

void reset_snake(Snake *snake) {
  SDL_Delay(1000);
  snake->head.x = screen_width / 2;
  snake->head.y = screen_height / 2;
}

bool snake_out_border(Snake *snake) {
  if (snake->head.x < 0 || snake->head.x + grid_size > screen_width ||
      snake->head.y < 0 || snake->head.y + grid_size > screen_height) {
    return true;
  }
  return false;
}

void input_handle(Game *game, SDL_Event *event) {
  while (SDL_PollEvent(event) != 0) {
    if (event->type == SDL_EVENT_QUIT) {
      game->running = false;
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
      switch (event->key.key) {
      case SDLK_UP:
        game->snake.direction = Up;
        break;
      case SDLK_DOWN:
        game->snake.direction = Down;
        break;
      case SDLK_LEFT:
        game->snake.direction = Left;
        break;
      case SDLK_RIGHT:
        game->snake.direction = Right;
        break;
      case SDLK_ESCAPE:
        game->running = false;
        break;
      default:
        break;
      }
    }
  }
}

void update(Game *game) {
  for (int i = game->snake.length - 1; i > 0; i--) {
    game->snake.body[i] = game->snake.body[i - 1];
  }
  game->snake.body[0] = game->snake.head;

  switch (game->snake.direction) {
  case Up:
    game->snake.head.y -= grid_size;
    break;
  case Down:
    game->snake.head.y += grid_size;
    break;
  case Left:
    game->snake.head.x -= grid_size;
    break;
  case Right:
    game->snake.head.x += grid_size;
    break;
  }

  if (snake_out_border(&game->snake)) {
    reset_snake(&game->snake);
  }
}
