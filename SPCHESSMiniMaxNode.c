/*
 * SPCHESSMiniMaxNode.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

int scoringFunc(SPCHESSGame* src, char currentPlayer) {
	if (!src)
		return 0;
	int score = 0, tmp = 0, i, j;
	char opponentPlayer;

	if (strcmp(currentPlayer, "W") == 0)
		strcpy(opponentPlayer, "B");
	else {
		strcpy(opponentPlayer, "W");
	}
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			score += getPawnValue(src->gameBoard[i][j], currentPlayer);
		}
	}
	return score;
}

int scoringFuncBest(SPCHESSGame* src, char currentPlayer) {
	if (!src)
		return 0;
	int score = 0, tmp = 0, i, j;
	char opponentPlayer;

	if (strcmp(currentPlayer, "W") == 0)
		strcpy(opponentPlayer, "B");
	else {
		strcpy(opponentPlayer, "W");
	}
	/*spChessIfMate return char whose is losing */
	if (spChessIfMate(src) == opponentPlayer) {
		return (4000);
	}
	if (spChessIfMate(src) == currentPlayer) {
		return (-4000);
	}
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			score += getPawnValue(src->gameBoard[i][j], currentPlayer);
		}
	}
	return score;
}
int getPawnValue(char type, char playerColor) {
	int white_pawn;
	int white_knight;
	int white_bishop;
	int white_rook;
	int white_queen;
	int white_king;

	int black_pawn;
	int black_knight;
	int black_bishop;
	int black_rook;
	int black_queen;
	int black_king;
	/* White Player */
	if (strcmp(playerColor, "W") == 0) {
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
	} else { /*Black Player */
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
	switch (type) {
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
	default:
		return 0;
	}
}

