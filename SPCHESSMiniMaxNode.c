/*
 * SPCHESSMiniMaxNode.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#include "SPCHESSGame.h"

int scoringFunc(SPCHESSGame* src, char currentPlayer) {
	if (!src)
		return 0;

	int score = 0;
	char opponentPlayer;

	if (currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
		opponentPlayer = SPCHESS_GAME_PLAYER_2_SYMBOL;
	else
		opponentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;

	//check if the state is mate (spChessIfMate return the char rep' the threatened side)
	if (spChessIfMate(src) == opponentPlayer)
		return 4000; // "plus inf"
	if (spChessIfMate(src) == currentPlayer)
		return -4000; //"minus inf"

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			score += getPieceValue(src->gameBoard[i][j], currentPlayer);
		}
	}
	return score;
}

int getPieceValue(char piece, char currentPlayer) {
	int white_pawn, white_knight, white_bishop, white_rook, white_queen,
			white_king;
	int black_pawn, black_knight, black_bishop, black_rook, black_queen,
			black_king;
	if (currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		white_pawn = 1;
		white_knight = 3;
		white_bishop = 3;
		white_rook = 5;
		white_queen = 9;
		white_king = 100;

		black_pawn = -1;
		black_knight = -3;
		black_bishop = -3;
		black_rook = -5;
		black_queen = -9;
		black_king = -100;
	} else {
		white_pawn = -1;
		white_knight = -3;
		white_bishop = -3;
		white_rook = -5;
		white_queen = -9;
		white_king = -100;

		black_pawn = 1;
		black_knight = 3;
		black_bishop = 3;
		black_rook = 5;
		black_queen = 9;
		black_king = 100;
	}

	switch (piece) {
	case WHITE_P:
		return white_pawn;
	case BLACK_P:
		return black_pawn;
	case WHITE_B:
		return white_bishop;
	case BLACK_B:
		return black_bishop;
	case WHITE_R:
		return white_rook;
	case BLACK_R:
		return black_rook;
	case WHITE_N:
		return white_knight;
	case BLACK_N:
		return black_knight;
	case WHITE_Q:
		return white_queen;
	case BLACK_Q:
		return black_queen;
	case WHITE_K:
		return white_king;
	case BLACK_K:
		return black_king;
	default: //EMPTY
		return 0;
	}
}

