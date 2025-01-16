#ifndef LOGIC_H
#define LOGIC_H

#include "game.h"


void input_handle(Game* game, SDL_Event* event);
void update(Game* game);
void render(Game* game);

#endif
