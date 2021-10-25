#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "game.h"

// This function is a little bit of a nightmare
// Refactor in future
void read_fen(game_t* game, char* fen) {
    unsigned char* board = game->board;
    unsigned char* board_position = board;
    // Clear game data to zeroes, mostly so that the board is empty
    //          (empty squares in the input FEN string are *NOT* overwritten)
    memset(game, 0, sizeof(game_t));
    // Read the board position into the board array
    while ((board_position - board) < TOTAL_SQUARES) {
        switch (*fen++) {
            case 'p': *board_position++ = 0b1001; break; // Black pawn
            case 'n': *board_position++ = 0b1010; break; // Black knight
            case 'b': *board_position++ = 0b1011; break; // Black bishop
            case 'r': *board_position++ = 0b1100; break; // Black rook
            case 'q': *board_position++ = 0b1101; break; // Black queen
            case 'k': *board_position++ = 0b1110; break; // Black king
            case 'P': *board_position++ = 0b0001; break; // White pawn
            case 'N': *board_position++ = 0b0010; break; // White knight
            case 'B': *board_position++ = 0b0011; break; // White bishop
            case 'R': *board_position++ = 0b0100; break; // White rook 
            case 'Q': *board_position++ = 0b0101; break; // White queen
            case 'K': *board_position++ = 0b0110; break; // White king
            case '/': break;                             // Skip / characters
            case '1': board_position += 1; break;        // Handle numeric values
            case '2': board_position += 2; break;
            case '3': board_position += 3; break;
            case '4': board_position += 4; break;
            case '5': board_position += 5; break;
            case '6': board_position += 6; break;
            case '7': board_position += 7; break;
            case '8': board_position += 8; break;
            default: break;
        }
    }
    fen++; // Skip the space after the board field
    game->turn = *fen++ == 'w' ? 1 : 0; // Check which player's turn it is
    fen++; // Skip the space after the player turn field
    // Read in which sides can castle and where
    while (!isspace(*fen)) {
        switch (*fen++) {
            case 'K': game->castling = game->castling | 0b1000; break; // White can castle kingside
            case 'Q': game->castling = game->castling | 0b0100; break; // White can castle queenside
            case 'k': game->castling = game->castling | 0b0010; break; // Black can castle kingside
            case 'q': game->castling = game->castling | 0b0001; break; // Black can castle queenside
            default: break;
        }
    }
    fen++; // Skip the space after the castling availability field
    if (*fen == '-') {
        fen++; // If it's a dash then skip it
    } else {
        game->en_passant = pgn_to_boardpos(fen); // Convert the move string to a board position value
        while (!isspace(*fen)) fen++; // Since the fen pointer is untouched in this scope, 
                                      // advance it to the next space
    }
    fen++; // Skip the space after the en passant target field
    char number[3]; // Declare a field for the eventual number
    int i = 0;
    // Copy the ply into the number array
    while (!isspace(*fen) && i < strlen(number)) number[i++] = *fen++;
    game->halfmove_ply = atoi(number); // Convert to an integer and store in game object
    fen++; // Skip the space after the ply field
    game->move_number = atoi(fen++); // Read the rest of the FEN, which contains the move number
}
