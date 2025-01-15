#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  Game game;
  init_game(&game);
  run_game(&game);
  quit_game(&game);

  return EXIT_SUCCESS;
}
