#include "game.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

                             //  1    2    3    4    5    6     (but it's binary)
const unsigned char pieces[] = {'P', 'N', 'B', 'R', 'Q', 'K'};

void display_game(game_t* game) { 
    unsigned int i, j;
    unsigned char value = 0;
    unsigned char print_val = 0;
    
    printf("White can castle kingside: %s\n", game->castling & 0b1000 ? "yes" : "no");
    printf("White can castle queenside: %s\n", game->castling & 0b0100 ? "yes" : "no");
    printf("Black can castle kingside: %s\n", game->castling & 0b0010 ? "yes" : "no");
    printf("Black can castle queenside: %s\n", game->castling & 0b0001 ? "yes" : "no");

    char move[2] = "00";
    game->en_passant != 0 ? boardpos_to_pgnmove(game->en_passant, move) : 0xDEADBEEF;
    printf("En passant target: %s\n", strcmp(move, "00") == 0 ? "None" : move);

    printf("Halfmove ply: %d\n", game->halfmove_ply);
    printf("Move number: %d\n\n", game->move_number);

    // Actually display the board now. Use the `pieces` array to determine the 
    // piece to be printed using the lower 3 bits of the value in the board.
    // Determine if the piece is white or black using the MSB.
    printf("%s to move\n", game->turn ? "White" : "Black");
    printf("  + - - - - - - - - +\n");
    for (i = 0; i < BOARD_HEIGHT; i++) {
        printf("%d | ", (8 - i));
        for (j = 0; j < BOARD_WIDTH; j++) {
            value = game->board[(BOARD_WIDTH * i) + j];
            if (value == 0) {
                printf("* ");
            } else {
                print_val = pieces[(value & 0b0111) - 1];
                if (value & 0b1000) {
                    print_val += ('a' - 'A');
                }
                printf("%c ", print_val);
            }
        }
        printf("|\n");
    }
    printf("  + - - - - - - - - +\n");
    printf("    a b c d e f g h  \n");
}

void game_to_fen(game_t* game, char* fen) {
    unsigned int i, j, count = 0;
    unsigned char value = 0;
    // Populate the board state using similar technique to how
    // it's displayed above
    for (i = 0; i < BOARD_HEIGHT; i++) {
        count = 0;
        for (j = 0; j < BOARD_WIDTH; j++) {
            value = game->board[(BOARD_WIDTH * i) + j];
            if (value == 0) {
                count++;
            } else {
                if (count != 0) *fen++ = '0' + count;
                count = 0;
                *fen = pieces[(value & 0b0111) - 1];
                if (value & 0b1000) {
                    *fen += ('a' - 'A');
                }
                fen++;
            }
        }
        if (count != 0) *fen++ = '0' + count;
        if (i != BOARD_HEIGHT - 1) *fen++ = '/'; // This monstrosity is to
                                                 // ensure that there isn't
                                                 // a trailing slash
    }
    *fen++ = ' '; // Add a space after board state field
    *fen++ = game->turn ? 'w' : 'b'; // Set who's turn it is
    *fen++ = ' '; // Add a space after turn field
    if (game->castling == 0) {
        *fen++ = '-'; // If no castling availability, make it a dash
    } else { // Otherwise actually populate it appropriately
        if (game->castling & 0b1000) *fen++ = 'K';
        if (game->castling & 0b0100) *fen++ = 'Q';
        if (game->castling & 0b0010) *fen++ = 'k';
        if (game->castling & 0b0001) *fen++ = 'q';
    }
    *fen++ = ' '; // Add a space after castling availability
    // Set the en passant target square in the string
    game->en_passant != 0 ? boardpos_to_pgnmove(game->en_passant, fen) : (*fen++ = '-');
    while (isalnum(*fen)) fen++; // Since fen isn't modified locally, skip to end of the field
    *fen++ = ' '; // Add a space after en passant target square
    char ply[4]; // Create a local array for reading in the ply
    sprintf(ply, "%d", game->halfmove_ply); // Turn the integer into a string
    strcpy(fen, ply); // Copy it into the FEN String
    while (*fen) fen++; // Skip ahead to null terminator
    *fen++ = ' ';       // and overwrite it with a space after ply field
    char move[7]; // Create a local array for reading in the ply
    sprintf(move, "%d", game->move_number); // Turn the integer into a string
    strcpy(fen, move); // Copy it into the FEN String
    // strcpy already copies in the null terminator for us! The string is appropriately terminated.
}
