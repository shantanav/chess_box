#ifndef INCLUDE_BOARD_H
#define INCLUDE_BOARD_H

// Board size stuff
#define BOARD_HEIGHT        (8)
#define BOARD_WIDTH         (8)
#define TOTAL_SQUARES       (BOARD_HEIGHT * BOARD_WIDTH)

// FEN stuff
#define FEN_STR_MAX_LEN     (TOTAL_SQUARES * 2) // This seemed appropriate 
                                                // given my brief research

/**
 * game_t:
 * Structural representation of a game using it's FEN information
 *      board:          array representation of the board
 *      turn:           denote which player's turn it is
 *      castling:       denote the castling availability using 4 bits
 *                          If bit 3 is high: White can castle kingside
 *                          If bit 2 is high: White can castle queenside
 *                          If bit 1 is high: Black can castle kingside
 *                          If bit 0 is high: Black can castle queenside
 *      en_passant:     en passant target square in the position if it exists
 *      halfmove_ply:   number of moves since last move capture 
 *                          (used for calculating 50 move draws)
 *      move_number:    current move number
 */
typedef struct {
    unsigned char board[TOTAL_SQUARES];
    unsigned char turn;
    unsigned char castling;
    unsigned char en_passant;
    unsigned int halfmove_ply;
    unsigned int move_number;
} game_t;

/**
 * display_board:
 * Print a human readable representation of the board
 * to stdout.
 * 
 * @param game  The game to be printed
 */
extern void display_game(game_t* game);

/**
 * read_fen:
 * Read a FEN string into a board.
 * 
 * This isn't error handled and is expecting a largely 
 * correct FEN string. Take pity on my code and don't give
 * it broken data please :)
 * 
 * @param game   The game
 * @param fen    The FEN string
 */
extern void read_fen(game_t* game, char* fen);

/**
 * game_to_fen:
 * Create a FEN string of the current position
 * 
 * @param game  The game
 * @param fen   The output FEN string. Must be TOTAL_SQUARES * 2 
 *              characters long
 */
extern void game_to_fen(game_t* game, char* fen);

/**
 * pgnmove_to_boardpos:
 * Converts a PGN format (<file_letter><rank_number>) to
 * a numeric value for the board representation.
 * 
 * @param pgn_move  string containing the PGN move
 * @return          The integer board position
 */
extern int pgnmove_to_boardpos(char* pgn_move);

/**
 * boardpos_to_pgnmove:
 * Converts a numeric value for the board representation
 * to a PGN format (<file_letter><rank_number>).
 * 
 * @param board_pos The integer board position
 * @param move      String to overwrite with the PGN format
 * 
 * @post            0 and 1 position of "move" parameter is 
 *                  populated with PGN move
 */
extern void boardpos_to_pgnmove(int board_pos, char* move);

#endif
