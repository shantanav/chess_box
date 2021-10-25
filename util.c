#include "game.h"
#include <ctype.h>
#include <stdio.h>

int pgn_to_boardpos(char* pgn_move) {
        if (isupper(*pgn_move)) *pgn_move += ('a' - 'A'); // If it's uppercase, make it uppercasen't
        unsigned char letter = *pgn_move++; // read the square letter
        unsigned char number = *pgn_move++ - '0'; // read the square number
        int col = letter - 'a'; // Convert the letter to a column
        int row = (BOARD_WIDTH - (number % BOARD_WIDTH)) * BOARD_WIDTH; // Convert the number to a row
        return row + col;
}

void boardpos_to_pgn(int board_pos, char* move) {
    move[0] = 'a' + (board_pos % 8);
    move[1] = '0' + (8 - (board_pos / 8));
}
