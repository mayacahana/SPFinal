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
	int gameMode;
	char userColor;
	char compColor;
	int difficulty;
} SPCHESSGame;


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
bool spChessGameIsValidMove(SPCHESSGame* src, int from[2], int to[2]);
bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem);
bool isSameColorAsCurrent(SPCHESSGame* src, int row, int col);
void getLegalMovesForPiece(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForRook(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForKnight(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForBishop(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForQueen(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForWhitePawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void getLegalMovesForBlackPawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
void  getLegalMovesForKing(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][2]);
bool isInBoard(int row, int col);

SPCHESS_GAME_MESSAGE spChessGameSetMove(SPCHESSGame* src, int from[2], int to[2]);

SPCHESS_GAME_MESSAGE spChessGameUndoPrevMove(SPCHESSGame* src);

char spChessIfMate(SPCHESSGame* src);
bool spChessIfMateWhite(src);
bool spChessIfMateBlack(src);
void findBlackKing(src);
void findWhiteKing(src);




char spChessGameCheckWinner(SPCHESSGame* src);

SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src);

char spChessGameGetCurrentPlayer(SPCHESSGame* src);

void spChessChangePlayer(SPCHESSGame* src);






#endif /* SPCHESSGAME_H_ */
