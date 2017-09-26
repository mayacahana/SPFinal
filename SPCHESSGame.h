/*
 * SPCHESSGame.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

#ifndef SPCHESSGAME_H_
#define SPCHESSGAME_H_
#include "SPCHESSArrayList.h"

//Definitions:
#define BOARD_SIZE 8
#define SPCHESS_GAME_PLAYER_1_SYMBOL 'W'
#define SPCHESS_GAME_PLAYER_2_SYMBOL 'B'
#define DEFAULT_GAME_MODE 1
#define DEFAULT_DIFFICULTY 2
#define DEFAULT_USER_COLOR 1
#define SPCHESS_GAME_TIE_SYMBOL '-'
#define SPCHESS_GAME_EMPTY_ENTRY ' '
#define HISTORY_SIZE 6
#define MAX_STEPS_PIECE 27
#define NUM_OF_PIECES 16
#define DIM 2
#define EATEN -17

//pieces:
#define WHITE_P 'm'
#define BLACK_P 'M'

#define WHITE_B 'b'
#define BLACK_B 'B'

#define WHITE_R 'r'
#define BLACK_R 'R'

#define WHITE_N 'n'
#define BLACK_N 'N'

#define WHITE_Q 'q'
#define BLACK_Q 'Q'

#define WHITE_K 'k'
#define BLACK_K 'K'

#define EMPTY '_'
/*
 * Structure represents the chess game:
 * gameBoard - a N*N-size array represent the current board
 * currentPlayer - char represents the current player for the next turn
 * movesPlayer1 - array contain the last moves of player 1
 * movesPlayer2 - array contain the last moves of player 2
 * piecesPlayer1[NUM_OF_PIECES][DIM] - array contain the current position of every player 1's soldier
 * piecesPlayer2[NUM_OF_PIECES][DIM] - array contain the current position of every player 2's soldier
 * gameMode - 1 for player vs. computer 2 for two players mode
 * difficulty - the diffculty of the game
 * colorUser - represent the color of the current user
 */
typedef struct spchess_game_t {
	char gameBoard[BOARD_SIZE][BOARD_SIZE];
	char currentPlayer;
	SPCHESSArrayList* movesPlayer1;
	SPCHESSArrayList* movesPlayer2;
	int piecesPlayer1[NUM_OF_PIECES][DIM];
	int piecesPlayer2[NUM_OF_PIECES][DIM];
	int gameMode;
	int difficulty;
	char colorUser;
} SPCHESSGame;
/**
 * Type used for returning error codes from game functions
 */
typedef enum spchess_game_message_t {
	SPCHESS_GAME_INVALID_MOVE,
	SPCHESS_GAME_INVALID_ARGUMENT,
	SPCHESS_GAME_NO_HISTORY,
	SPCHESS_GAME_SUCCESS,
	SPCHESS_GAME_INVALID_COLOR,
} SPCHESS_GAME_MESSAGE;
/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
SPCHESSGame* spChessGameCreate(int historySize);
/**
 * Initializing a new board according to chess rules.
 * @param gameBoard - the board
 */
void initBoardGame(char gameBoard[BOARD_SIZE][BOARD_SIZE]);
/**
 * Initializing the locations of soldiers in the array for the starting position.
 * @param piecesArray - the array
 */
void initPiecesArray(int piecesArray[NUM_OF_PIECES][DIM], char gameColor);
/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
SPCHESSGame* spChessGameCopy(SPCHESSGame* src);
/**
 * Restarting the game to default setting.
 * @param src- the current game
 */
void spChessGameClear(SPCHESSGame* src);
/**
 * Restarting the game to default setting.
 * @param src- the current game
 */
void spChessGameRestart(SPCHESSGame* src); //for gui mode
/**
 * Copy al the info of the source game to the target game
 * @param trg- the target game
 * @param src - the source game
 */

void spChessGameCopyInfo(SPCHESSGame* trg, SPCHESSGame* src);
/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void spChessGameDestroy(SPCHESSGame* src);
/**
 * Helper function to "set move". checks if the
 * color of the selected soldier is the right one and checks if
 * its location is valid on the board
 * @param src- the game
 * @param move- the move
 * @color - the current player's color
 * @return
 * message regarding the results of the validations.
 */
SPCHESS_GAME_MESSAGE spChessMoveHandler(SPCHESSGame*, move* elem, char colorToMove);
/**
 * Checks if the specific soldier can be moved from its origin location to destination.
 * According to the rules.
 * @param src- the game
 * @param from - the origin location
 * @param to - the destination
 * @return
 * True if the move is valid, False otherwise.
 */
bool spChessGameIsValidMove(SPCHESSGame* src, int from[DIM], int to[DIM]);
/**
 * This function simulates the next move and check if the game is entering
 * to check state (the king is under threat)
 * @param src - the game
 * @param from - the origin location
 * @param to - the destination
 * @return
 * True if the king is under threat in the next move, False otherwise.
 */
bool spChessGameIsKingRisker(SPCHESSGame* src, int from[DIM], int to[DIM]);
/**
 * Helper function. checks if the destination location is
 * valid for the soldier.
 * @param src - the game
 * @param elem - the move
 * @return
 * True if the move is valid, False otherwise.
 */
bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem);
/**
 * Helper function - checks if the piece at the specific row and col
 * of the board is at the given color
 * @param src - the game
 * @param row
 * @param col
 * @param givenColor
 * @return
 * True if the piece matches the given color, False otherwise.
 */
bool isSameColorAsGiven(SPCHESSGame* src, int row, int col, char givenColor);
/**
 * These functions fills the legalMoves array with legal actions for the
 * piece, according to its type.
 * @param src - the game
 * @param elem - represent the piece
 * @param legalMoves - the desired array
 *
 */
void getLegalMovesForPiece(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForRook(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForKnight(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForBishop(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForQueen(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForWhitePawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForBlackPawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void  getLegalMovesForKing(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);

/**
 * Checks if the position is on board.
 * @param row
 * @param col
 * @return
 * True if success, False otherwise.
 */
bool isInBoard(int row, int col);
/**
 * Helper function. returns the color for the given piece.
 * @param piece - the piece
 * @return
 * 'W' if white, 'B' otherwise.
 */
char getColorFromPiece(char piece);
/**
 * This function sets (commit) the move on the specific game from the given origin
 * to the desired destination.
 * @param src - the game
 * @param from - origin location
 * @param to - destination location
 * @return
 * A message indicate the success(or failure) of the function.
 */
SPCHESS_GAME_MESSAGE spChessGameSetMove(SPCHESSGame* src, int from[DIM], int to[DIM]);
/**
 * Undo the last move commited at the game.
 * without print - for the set move check(check state etc.)
 * @param src - the game
 * @return
 * A message indicate the success(or failure) of the function.
 */
SPCHESS_GAME_MESSAGE spChessGameUndoPrevMove(SPCHESSGame* src);
/**
 * Helper function.
 * return the range of location for the specific piece.
 * @piece - the desired piece
 * @subArray - filled with the range at the end
 */
void getSubArrayFromPiece(char piece, int subArray[DIM]);
/**
 * Undo the last move commited at the game.
 * @param src - the game
 * @return
 * A message indicate the success(or failure) of the function.
 */
SPCHESS_GAME_MESSAGE spChessGameUndoPrevMoveWithPrint(SPCHESSGame* src);
/**
 * Check if the game is at check state. if it does,
 * return the symbol of the color which is in the state of mate or null otherwise.
 * @param src - the game
 * @return
 * symbol of color which is in state of mate.
 */
char spChessIfMate(SPCHESSGame* src);
/**
 * Checks if there is a threat by player 1.
 * @param src - the game
 * @return
 * True if player 2 is threathened by player 1, False otherwise.
 */
bool spChessIfPlayer1IsThreatening(SPCHESSGame* src);
/**
 * Checks if there is a threat by player 2.
 * @param src - the game
 * @return
 * True if player 1 is threathened by player 2, False otherwise.
 */
bool spChessIfPlayer2IsThreatening(SPCHESSGame* src);
/**
 * Checks if there is a winner for the game
 * @param src - the game
 * @return
 * the symbol of color represent the winner's color. '\0' otherwise.
 */
char spChessGameCheckWinner(SPCHESSGame* src);
/**
 * Helper functions. return the color symbol of the winner.
 * Help to determine if the user is really winning by checking
 * if the player is threathning the other and if the other player have
 * a king saver.
 * @param src - the game
 * @return
 * True if player 1/2 wins the game, False otherwise.
 */
bool spChessIfPlayer1Win(SPCHESSGame* src);
bool spChessIfPlayer2Win(SPCHESSGame* src);
/**
 * Helper functions. return the color symbol of the winner.
 * Help to determine if the user is really winning by checking
 * if the player is threathning the other and if the other player have
 * a king saver.
 * @param src - the game
 * @return
 * True if player 1/2 have a king saver, False otherwise.
 */
bool existsPlayer1KingSaver(SPCHESSGame* src);
bool existsPlayer2KingSaver(SPCHESSGame* src);
/**
 * Checks if there is a tie between the players.
 * @param src - the game
 * @return
 * a special symbol for a tie - SPCHESS_GAME_TIE_SYMBOL '-' if there
 * is a tie, '\0' otherwise.
 */
char spChessGameCheckTie(SPCHESSGame* src);
/**
 *Checks if there is a valid move, according to the current player
 *@param src -the game
 *@return
 *True if there is a move, False otherwise.
 */
bool existsValidMovePlayer1(SPCHESSGame* src);
bool existsValidMovePlayer2(SPCHESSGame* src);
/**
 * Prints the board game to the console.
 * Return success message or invalid argument message in case of a problem.
 * @param src - the game
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src is NULL
 * SP_CHESS_GAME_SUCCESS - otherwise
 */
SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src);
/**
 * Helper function. returns the char representing the player of the next move
 * in the game.
 * @param src - the game
 * @return
 * SPCHESS_GAME_PLAYER_1_SYMBOL 'W' or
 * PCHESS_GAME_PLAYER_2_SYMBOL 'B' according to the game settings.
 */
char spChessGameGetCurrentPlayer(SPCHESSGame* src);
/**
 * Helper function- change the current player to the opposite player.
 * @param src - the game
 */
void spChessChangePlayer(SPCHESSGame* src);

#endif /* SPCHESSGAME_H_ */
