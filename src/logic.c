#include "../include/logic.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_timer.h"

bool is_collision(Point* a, Point* b) {
  return !(a->x + grid_size <= b->x || a->x >= b->x + grid_size || a->y + grid_size <= b->y
           || a->y >= b->y + grid_size);
}

void snake_dead(Game* game) {
  SDL_Delay(1000);
  game->last_time = SDL_GetTicks();
  game->timer     = SDL_GetTicks();
  for (int i = initial_len; i < game->snake.length; i++) {
    game->snake.body[i] = (Point){0, 0};
  }
  game->snake.length = initial_len;
  for (int i = 0; i < initial_len; i++) {
    game->snake.body[i].x = game->snake.head.x - i * grid_size;
    game->snake.body[i].y = game->snake.head.y;
  }

  game->snake.head.x = screen_width / 2;
  game->snake.head.y = screen_height / 2;
}

bool snake_out_border(Snake* snake) {
  if (snake->head.x < 0 || snake->head.x + grid_size > screen_width || snake->head.y < 0
      || snake->head.y + grid_size > screen_height) {
    return true;
  }
  return false;
}

bool snake_eat_self(Snake* snake) {
  for (int i = 0; i < snake->length; i++) {
    if (is_collision(&snake->head, &snake->body[i])) {
      return true;
    }
  }
  return false;
}

bool snake_eat_fruit(Game* game) {
  if (is_collision(&game->snake.head, &game->fruit)) {
    return true;
  }
  return false;
}

void input_handle(Game* game, SDL_Event* event) {
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

void body_move(Game* game) {
  for (int i = game->snake.length - 1; i > 0; i--) {
    game->snake.body[i] = game->snake.body[i - 1];
  }
  game->snake.body[0] = game->snake.head;
}

void snake_move(Game* game) {
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
}

void fruit_init(Game* game) {
  do {
    // 1 and 1 are the offset from borders
    game->fruit.x = 1 + grid_size + SDL_rand(screen_width - grid_size * 2) - 1;
    game->fruit.y = 1 + grid_size + SDL_rand(screen_height - grid_size * 2) - 1;
  } while (snake_eat_fruit(game));
  game->fruit_eaten = false;
}

void update(Game* game) {
  game->timer = SDL_GetTicks();

  if (game->fruit_eaten) {
    fruit_init(game);
    game->snake.length++;
  }

  body_move(game);

  snake_move(game);

  if (snake_out_border(&game->snake) || snake_eat_self(&game->snake)) {
    snake_dead(game);
  }

  if (snake_eat_fruit(game)) {
    game->score++;
    game->fruit_eaten = true;
  }
}
