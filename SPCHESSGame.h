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

typedef enum spchess_game_message_t {
	SPCHESS_GAME_INVALID_MOVE,
	SPCHESS_GAME_INVALID_ARGUMENT,
	SPCHESS_GAME_NO_HISTORY,
	SPCHESS_GAME_SUCCESS,
	SPCHESS_GAME_INVALID_COLOR,
} SPCHESS_GAME_MESSAGE;

SPCHESSGame* spChessGameCreate(int historySize, int gameMode, char colorUser, int difficulty);
void initBoardGame(char gameBoard[BOARD_SIZE][BOARD_SIZE]);
void initPiecesArray(int piecesArray[NUM_OF_PIECES][DIM], char gameColor);

SPCHESSGame* spChessGameCopy(SPCHESSGame* src);

void spChessGameDestroy(SPCHESSGame* src);

SPCHESS_GAME_MESSAGE spChessMoveHandler(SPCHESSGame*, move* elem, char colorToMove);
bool spChessGameIsValidMove(SPCHESSGame* src, int from[DIM], int to[DIM]);
bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem);
bool isSameColorAsGiven(SPCHESSGame* src, int row, int col, char givenColor);
void getLegalMovesForPiece(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForRook(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForKnight(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForBishop(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForQueen(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForWhitePawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void getLegalMovesForBlackPawn(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
void  getLegalMovesForKing(SPCHESSGame* src, move* elem, int legalMoves[MAX_STEPS_PIECE][DIM]);
bool isInBoard(int row, int col);
char getColorFromPiece(char piece);

SPCHESS_GAME_MESSAGE spChessGameSetMove(SPCHESSGame* src, int from[DIM], int to[DIM]);

SPCHESS_GAME_MESSAGE spChessGameUndoPrevMove(SPCHESSGame* src);
void getSubArrayFromPiece(char piece, int subArray[DIM]);
char pawnFromArray(int index, char currentPlayer);
SPCHESS_GAME_MESSAGE spChessGameUndoPrevMoveWithPrint(SPCHESSGame* src);


char spChessIfMate(SPCHESSGame* src);
bool spChessIfPlayer1IsThreatening(SPCHESSGame* src);
bool spChessIfPlayer2IsThreatening(SPCHESSGame* src);

char spChessGameCheckWinner(SPCHESSGame* src);
bool spChessIfPlayer1Win(SPCHESSGame* src);
bool spChessIfPlayer2Win(SPCHESSGame* src);
bool existsPlayer1KingSaver(SPCHESSGame* src);
bool existsPlayer2KingSaver(SPCHESSGame* src);

char spChessGameCheckTie(SPCHESSGame* src);
bool existsValidMovePlayer1(SPCHESSGame* src);
bool existsValidMovePlayer2(SPCHESSGame* src);

SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src);

char spChessGameGetCurrentPlayer(SPCHESSGame* src);

void spChessChangePlayer(SPCHESSGame* src);

#endif /* SPCHESSGAME_H_ */
