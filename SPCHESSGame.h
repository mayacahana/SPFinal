/*
 * SPCHESSGame.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

#ifndef SPCHESSGAME_H_
#define SPCHESSGAME_H_
#include "SPCHESSArrayList.h"
#include <stdbool.h>


//Definitions:

#define BOARD_SIZE 8
#define SPCHESS_GAME_PLAYER_1_SYMBOL 'W'
#define SPCHESS_GAME_PLAYER_2_SYMBOL 'B'
#define SPCHESS_GAME_TIE_SYMBOL '-'
#define SPCHESS_GAME_EMPTY_ENTRY ' '

#define HISTORY_SIZE 6
#define MAX_STEPS_PIECE 27

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

typedef struct spchess_game_t {
	char gameBoard[BOARD_SIZE][BOARD_SIZE];
	char currentPlayer;
	SPCHESSArrayList* movesPlayer1;
	SPCHESSArrayList* movesPlayer2;
} SPCHESSGame;

typedef struct move_t{
    int from[2];
    int to[2];
    char piece;
    char eaten;
} move;

typedef enum spchess_game_message_t {
	SPCHESS_GAME_INVALID_MOVE,
	SPCHESS_GAME_INVALID_ARGUMENT,
	SPCHESS_GAME_NO_HISTORY,
	SPCHESS_GAME_SUCCESS,
	SPCHESS_GAME_INVALID_COLOR,
} SPCHESS_GAME_MESSAGE;



SPCHESSGame* spChessGameCreate(int historySize);
void initBoardGame(char gameBoard[BOARD_SIZE][BOARD_SIZE]);

SPCHESSGame* spChessGameCopy(SPCHESSGame* src);

void spChessGameDestroy(SPCHESSGame* src);


SPCHESS_GAME_MESSAGE spChessMoveHandler(SPCHESSGame*, move* elem);
bool spChessGameIsValidMove(SPCHESSGame* src, move* elem);
bool spChessGameIsColorPos(SPCHESSGame* src, move* elem);
bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem);
int** getLegalMovesForPiece(SPCHESSGame* src, move* elem);
int** getLegalMovesForRook(SPCHESSGame* src, move* elem);
int** getLegalMovesForKnight(SPCHESSGame* src, move* elem);
int** getLegalMovesForBishop(SPCHESSGame* src, move* elem);
int** getLegalMovesForQueen(SPCHESSGame* src, move* elem);
int** getLegalMovesForPawn(SPCHESSGame* src, move* elem);
int** getLegalMovesForKing(SPCHESSGame* src, move* elem);
bool isSameColorAsCurrent(SPCHESSGame* src, int row, int col);










SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src);

char spChessGameGetCurrentPlayer(SPCHESSGame* src);

void spChessChangePlayer(SPCHESSGame* src);


#endif /* SPCHESSGAME_H_ */
