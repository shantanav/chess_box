#include "game.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    game_t game;
    char fen[TOTAL_SQUARES * 2];
    memset(fen, 0, TOTAL_SQUARES * 2);

    clock_t t = clock();
    read_fen(&game, argv[1]);
    game_to_fen(&game, fen);
    t = clock() - t;

    display_game(&game);
    puts(fen);
    printf("Time taken: %f seconds.\n", ((double)t)/CLOCKS_PER_SEC);
}
