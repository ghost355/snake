#include "../include/game.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{

    Game game;
    game_init(&game);
    run_game(&game);
    quit_game(&game);

    return EXIT_SUCCESS;
}
