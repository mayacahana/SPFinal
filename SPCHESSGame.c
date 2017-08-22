/*
 * SPCHESSGame.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SPCHESSGame.h"

SPCHESSGame* spChessGameCreate(int historySize) {

	if (historySize <= 0)
		return NULL;

	SPCHESSGame* res = (SPCHESSGame*) malloc(sizeof(SPCHESSGame));
	if (!res) {
		printf("Error: spChessGameCreate has failed\n");
		exit(1);
	}
	initBoardGame(res->gameBoard);

	//init current player, assuming player 1 starts the game
	res->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;

	//init movesLists
	res->movesPlayer1 = spArrayListCreate(historySize / 2);
	res->movesPlayer2 = spArrayListCreate(historySize / 2);

	return res;
}

void initGameBoard(char gameBoard[BOARD_SIZE][BOARD_SIZE]) {

	//init white pieces:
	gameBoard[0][0] = WHITE_R;
	gameBoard[0][1] = WHITE_N;
	gameBoard[0][2] = WHITE_B;
	gameBoard[0][3] = WHITE_Q;
	gameBoard[0][4] = WHITE_K;
	gameBoard[0][5] = WHITE_B;
	gameBoard[0][6] = WHITE_N;
	gameBoard[0][7] = WHITE_R;
	for (int j = 0; j < BOARD_SIZE; j++)
		gameBoard[1][j] = WHITE_P;

	//init black pieces:
	gameBoard[BOARD_SIZE - 1][0] = BLACK_R;
	gameBoard[BOARD_SIZE - 1][1] = BLACK_N;
	gameBoard[BOARD_SIZE - 1][2] = BLACK_B;
	gameBoard[BOARD_SIZE - 1][3] = BLACK_Q;
	gameBoard[BOARD_SIZE - 1][4] = BLACK_K;
	gameBoard[BOARD_SIZE - 1][5] = BLACK_B;
	gameBoard[BOARD_SIZE - 1][6] = BLACK_N;
	gameBoard[BOARD_SIZE - 1][7] = BLACK_R;
	for (int j = 0; j < BOARD_SIZE; j++)
		gameBoard[BOARD_SIZE - 2][j] = BLACK_P;

	//init empty spots:
	for (int i = 2; i < BOARD_SIZE - 2; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			gameBoard[i][j] = EMPTY;
	}
}

SPCHESSGame* spChessGameCopy(SPCHESSGame* src) {
	if (!src)
		return NULL;

	SPCHESSGame* res = spChessGameCreate(2 * src->movesPlayer1->maxSize);
	if (!res) {
		spChessGameDestroy(src);
		print_message("Error: spChessGameCopy has failed\n");
		exit(1);
	}
	//copy board
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			res->gameBoard[i][j] = src->gameBoard[i][j];
	}

	//copy currentPlayer
	res->currentPlayer = src->currentPlayer;

	spArrayListDestroy(res->movesPlayer1);
	spArrayListDestroy(res->movesPlayer2);

	//copy movesPlayer
	res->movesPlayer1 = spArrayListCopy(src->movesPlayer1);
	if (res->movesPlayer1 == NULL) {
		free(res);
		return NULL;
	}
	res->movesPlayer2 = spArrayListCopy(src->movesPlayer2);
	if (res->movesPlayer2 == NULL) {
		free(res);
		return NULL;
	}
	return res;
}

void spChessGameDestroy(SPCHESSGame* src) {
	if (!src)
		return;

	spArrayListDestroy(src->movesPlayer1);
	spArrayListDestroy(src->movesPlayer2);
	free(src);

}

SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src) {
	if (!src)
		return SPCHESS_GAME_INVALID_ARGUMENT;

	for (int i = BOARD_SIZE - 1; i >= 0; i--) {
		printf("%d", i + 1);
		printf("| ");
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%c ", src->gameBoard[i][j]);
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");

	return SPCHESS_GAME_SUCCESS;
}

bool spChessGameIsValidMove(SPCHESSGame* src, move* elem) {

	if (!src || !elem)
		return false;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	int row_to = elem->to[0];
	int col_to = elem->to[1];

	bool isValidFrom = row_from >= 0&& row_from < BOARD_SIZE &&
	col_from >=0 && col_from < BOARD_SIZE;

	bool isValidTo = row_to >= 0&& row_to < BOARD_SIZE &&
	col_to >=0 && col_to < BOARD_SIZE;

	return isValidFrom && isValidTo;
}

bool spChessGameIsColorPos(SPCHESSGame* src, move* elem) {
	if (!src || !elem)
		return false;

	//assuming the cordin' are valid!
	int row_from = elem->from[0];
	int col_from = elem->from[1];
	char piece = src->gameBoard[row_from][col_from];
	char currentPlayer = src->currentPlayer;
	if (currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		if (piece == WHITE_N || piece == WHITE_R || piece == WHITE_K
				|| piece == WHITE_B || piece == WHITE_Q || piece == WHITE_P)
			return true;
		else
			return false;
	} else { //currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		if (piece == BLACK_N || piece == BLACK_R || piece == BLACK_K
				|| piece == BLACK_B || piece == BLACK_Q || piece == BLACK_P)
			return true;
		else
			return false;
	}
}

bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem) {
	if (!src || !elem)
		return false;

	//assuming the cordin' are valid and valid piece!
	int row_to = elem->to[0];
	int col_to = elem->to[1];
	bool validMove = false;

	int** movesforPiece = getLegalMovesForPiece(src, elem);
	//check if target piece is one of the legal moves above
	for (int i = 0; i < MAX_STEPS_PIECE; i++) {
		if (movesforPiece[i][0] == row_to && movesforPiece[i][1] == col_to) { //it's legal move!
			validMove = true;
			break;
		}
	}
	return validMove;

}

int** getLegalMovesForPiece(SPCHESSGame* src, move* elem) {

	char piece = elem->piece;

	//decide moves acoording to piece's type:
	if (piece == WHITE_R || piece == BLACK_R)
		return getLegalMovesForRook(src, elem);
	if (piece == WHITE_N || piece == BLACK_N)
		return getLegalMovesForKnight(src, elem);
	if (piece == WHITE_B || piece == BLACK_B)
		return getLegalMovesForBishop(src, elem);
	if (piece == WHITE_Q | piece == BLACK_Q)
		return getLegalMovesForQueen(src, elem);
	if (piece == WHITE_K || piece == BLACK_K)
		return getLegalMovesForKing(src, elem);
	else // piece == 'WHITE_P' || piece == 'BLACK_P'
		return getLegalMovesForPawn(src, elem);
}

bool isSameColorAsCurrent(SPCHESSGame* src, int row, int col) {
	if (!src)
		return false;
	char piece = src->gameBoard[row][col];
	char currentPlayer = src->currentPlayer;
	if (currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		if (piece == WHITE_N || piece == WHITE_R || piece == WHITE_K
				|| piece == WHITE_B || piece == WHITE_Q || piece == WHITE_P)
			return true;
		else
			return false;
	} else { //currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		if (piece == BLACK_N || piece == BLACK_R || piece == BLACK_K
				|| piece == BLACK_B || piece == BLACK_Q || piece == BLACK_P)
			return true;
		else
			return false;
	}

}

int** getLegalMovesForRook(SPCHESSGame* src, move* elem) {
	int ind = 0;
	int moves[MAX_STEPS_PIECE][2];
	int row_from = elem->from[0];
	int col_from = elem->from[1];

	//right direction
	for (int j = col_from + 1; j < BOARD_SIZE; j++) {
		if (src->gameBoard[row_from][j] == EMPTY) {
			moves[ind][0] = row_from;
			moves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsCurrent(src, row_from, j)) {
			moves[ind][0] = row_from;
			moves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

	}

	//left direction
	for (int j = col_from - 1; j >= 0; j--) {
		if (src->gameBoard[row_from][j] == EMPTY) {
			moves[ind][0] = row_from;
			moves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsCurrent(src, row_from, j)) { //oppnant piece - cannot continue after this direction
			moves[ind][0] = row_from;
			moves[ind][1] = j;
			ind++;
			break;
		} else //same color - cannot continue this direction
			break;

	}

	//up direction
	for (int i = row_from + 1; i < BOARD_SIZE; i++) {
		if (src->gameBoard[i][col_from] == EMPTY) {
			moves[ind][0] = i;
			moves[ind][1] = col_from;
			ind++;
		} else if (!isSameColorAsCurrent(src, i, col_from)) {
			moves[ind][0] = i;
			moves[ind][1] = col_from;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;
	}

	//down direction
	for (int i = row_from - 1; i >= 0; i--) {
		if (src->gameBoard[i][col_from] == EMPTY) {
			moves[ind][0] = i;
			moves[ind][1] = col_from;
			ind++;
		} else if (!isSameColorAsCurrent(src, i, col_from)) {
			moves[ind][0] = i;
			moves[ind][1] = col_from;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;
	}

	return moves;
}

SPCHESS_GAME_MESSAGE spChessMoveHandler(SPCHESSGame* src, move* elem) {
	if (!src || !elem)
		return SPCHESS_GAME_INVALID_ARGUMENT;

	//check if either one of the location is invalid
	if (!spChessGameIsValidMove(src, elem))
		return SPCHESS_GAME_INVALID_ARGUMENT;

	//check if the position contains a piece if the user's color
	if (!spChessGameIsColorPos(src, elem))
		return SPCHESS_GAME_INVALID_COLOR;

	//check if the move is legal for the current piece
	if (!spChessGameValidMoveLoc(src, elem))
		return SPCHESS_GAME_INVALID_MOVE;

	return SPCHESS_GAME_SUCCESS;

}

char spChessGameGetCurrentPlayer(SPCHESSGame* src) {
	//if (!src)
	//	SP_FIAR_GAME_EMPTY_ENTRY;
	//for some reason, the above if statment doesn't compile on NOVA
	return src->currentPlayer;
}

void spChessChangePlayer(SPCHESSGame* src) {
	if (!src)
		return;

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
		src->currentPlayer = SPCHESS_GAME_PLAYER_2_SYMBOL;
	else
		src->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;
}

