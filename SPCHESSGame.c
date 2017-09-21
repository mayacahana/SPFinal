/*
 * SPCHESSGame.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

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

	res->difficulty = DEFAULT_DIFFICULTY;
	res->colorUser = DEFAULT_USER_COLOR;
	res->gameMode = DEFAULT_GAME_MODE;

	//player 1 - white - always starts the game
	res->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;
	res->movesPlayer1 = spArrayListCreate(historySize / 2);
	res->movesPlayer2 = spArrayListCreate(historySize / 2);

	initPiecesArray(res->piecesPlayer1, SPCHESS_GAME_PLAYER_1_SYMBOL);
	initPiecesArray(res->piecesPlayer2, SPCHESS_GAME_PLAYER_2_SYMBOL);

	return res;

}
void initBoardGame(char gameBoard[BOARD_SIZE][BOARD_SIZE]) {

	//init white pieces:
	gameBoard[0][0] = WHITE_R;
	gameBoard[0][1] = WHITE_N;
	gameBoard[0][2] = WHITE_B;
	gameBoard[0][3] = WHITE_Q;
	gameBoard[0][4] = WHITE_K;
	gameBoard[0][5] = WHITE_B;
	gameBoard[0][6] = WHITE_N;
	gameBoard[0][7] = WHITE_R;
	for (int j = 0; j < BOARD_SIZE; j++) //pawns
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
	for (int j = 0; j < BOARD_SIZE; j++) //pwans
		gameBoard[BOARD_SIZE - 2][j] = BLACK_P;

	//init empty spots:
	for (int i = 2; i < BOARD_SIZE - 2; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			gameBoard[i][j] = EMPTY;
	}
}
void initPiecesArray(int piecesArray[NUM_OF_PIECES][DIM], char gameColor) {
	if (gameColor == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		//init pawns
		for (int i = 0; i < BOARD_SIZE; i++) {
			piecesArray[i][0] = 1;
			piecesArray[i][1] = i;

		}
		//init knights
		piecesArray[8][0] = 0;
		piecesArray[8][1] = 1;

		piecesArray[9][0] = 0;
		piecesArray[9][1] = BOARD_SIZE - 2;

		//init bishops
		piecesArray[10][0] = 0;
		piecesArray[10][1] = 2;

		piecesArray[11][0] = 0;
		piecesArray[11][1] = BOARD_SIZE - 3;

		//init rooks
		piecesArray[12][0] = 0;
		piecesArray[12][1] = 0;

		piecesArray[13][0] = 0;
		piecesArray[13][1] = BOARD_SIZE - 1;

		//init queen
		piecesArray[14][0] = 0;
		piecesArray[14][1] = 3;

		//init king
		piecesArray[15][0] = 0;
		piecesArray[15][1] = 4;
	} else {
		//init pawns
		for (int i = 0; i < BOARD_SIZE; i++) {
			piecesArray[i][0] = BOARD_SIZE - 2;
			piecesArray[i][1] = i;

		}
		//init knights
		piecesArray[8][0] = BOARD_SIZE - 1;
		piecesArray[8][1] = 1;

		piecesArray[9][0] = BOARD_SIZE - 1;
		piecesArray[9][1] = BOARD_SIZE - 2;

		//init bishops
		piecesArray[10][0] = BOARD_SIZE - 1;
		piecesArray[10][1] = 2;

		piecesArray[11][0] = BOARD_SIZE - 1;
		piecesArray[11][1] = BOARD_SIZE - 3;

		//init rooks
		piecesArray[12][0] = BOARD_SIZE - 1;
		piecesArray[12][1] = 0;

		piecesArray[13][0] = BOARD_SIZE - 1;
		piecesArray[13][1] = BOARD_SIZE - 1;

		//init queen
		piecesArray[14][0] = BOARD_SIZE - 1;
		piecesArray[14][1] = 3;

		//init king
		piecesArray[15][0] = BOARD_SIZE - 1;
		piecesArray[15][1] = 4;
	}

}

void spChessGameCopyInfo(SPCHESSGame* trg, SPCHESSGame* src) {
	if (!src)
		return;

	//copy board
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			trg->gameBoard[i][j] = src->gameBoard[i][j];
	}

	//copy piecesArray
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		for (int j = 0; j < DIM; j++) {
			trg->piecesPlayer1[i][j] = src->piecesPlayer1[i][j];
			trg->piecesPlayer2[i][j] = src->piecesPlayer2[i][j];
		}
	}

	//copy currentPlayer
	trg->currentPlayer = src->currentPlayer;
	trg->difficulty = src->difficulty;
	trg->colorUser = src->colorUser;
	trg->gameMode = src->gameMode;

	spArrayListDestroy(trg->movesPlayer1);
	spArrayListDestroy(trg->movesPlayer2);

	//copy movesPlayer
	trg->movesPlayer1 = spArrayListCopy(src->movesPlayer1);
	if (trg->movesPlayer1 == NULL) {
		return;
	}
	trg->movesPlayer2 = spArrayListCopy(src->movesPlayer2);
	if (trg->movesPlayer2 == NULL) {
		return;
	}
}

SPCHESSGame* spChessGameCopy(SPCHESSGame* src) {
	if (!src)
		return NULL;

	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE);
	if (!res) {
		spChessGameDestroy(src);
		printf("Error: spChessGameCopy has failed\n");
		exit(1);
	}
	//copy board
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			res->gameBoard[i][j] = src->gameBoard[i][j];
	}

	//copy piecesArray
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		for (int j = 0; j < DIM; j++) {
			res->piecesPlayer1[i][j] = src->piecesPlayer1[i][j];
			res->piecesPlayer2[i][j] = src->piecesPlayer2[i][j];
		}
	}

	//copy currentPlayer
	res->currentPlayer = src->currentPlayer;
	res->difficulty = src->difficulty;
	res->colorUser = src->colorUser;
	res->gameMode = src->gameMode;

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

void spChessGameClear(SPCHESSGame* src) {
	if (!src)
		return;

	initBoardGame(src->gameBoard);

	src->difficulty = DEFAULT_DIFFICULTY;
	src->colorUser = DEFAULT_USER_COLOR;
	src->gameMode = DEFAULT_GAME_MODE;

	//player 1 - white - always starts the game
	src->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;

	spArrayListDestroy(src->movesPlayer1);
	spArrayListDestroy(src->movesPlayer2);

	src->movesPlayer1 = spArrayListCreate(HISTORY_SIZE / 2);
	src->movesPlayer2 = spArrayListCreate(HISTORY_SIZE / 2);

	initPiecesArray(src->piecesPlayer1, SPCHESS_GAME_PLAYER_1_SYMBOL);
	initPiecesArray(src->piecesPlayer2, SPCHESS_GAME_PLAYER_2_SYMBOL);

}

void spChessGameRestart(SPCHESSGame* src) { //for gui mode
	if (!src)
		return;

	initBoardGame(src->gameBoard);

	//player 1 - white - always starts the game
	src->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;

	spArrayListDestroy(src->movesPlayer1);
	spArrayListDestroy(src->movesPlayer2);

	src->movesPlayer1 = spArrayListCreate(HISTORY_SIZE / 2);
	src->movesPlayer2 = spArrayListCreate(HISTORY_SIZE / 2);

	initPiecesArray(src->piecesPlayer1, SPCHESS_GAME_PLAYER_1_SYMBOL);
	initPiecesArray(src->piecesPlayer2, SPCHESS_GAME_PLAYER_2_SYMBOL);
}

SPCHESS_GAME_MESSAGE spChessGamePrintBoard(SPCHESSGame* src) {
	if (!src)
		return SPCHESS_GAME_INVALID_ARGUMENT;

	for (int i = BOARD_SIZE - 1; i >= 0; i--) {
		//printf("%d", i);
		printf("%d", i + 1);
		printf("| ");
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%c ", src->gameBoard[i][j]);
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
	//printf("   0 1 2 3 4 5 6 7\n");
	return SPCHESS_GAME_SUCCESS;
}

bool spChessGameIsValidMove(SPCHESSGame* src, int from[DIM], int to[DIM]) {

	if (!src)
		return false;

	int row_from = from[0];
	int col_from = from[1];
	int row_to = to[0];
	int col_to = to[1];

	return isInBoard(row_from, col_from) && isInBoard(row_to, col_to);
}
bool isInBoard(int row, int col) {
	bool isValidRow = row >= 0 && row < BOARD_SIZE;
	bool isValidCol = col >= 0 && col < BOARD_SIZE;

	return isValidRow && isValidCol;
}

bool spChessGameIsKingRisker(SPCHESSGame* src, int from[DIM], int to[DIM]) {
	if (!src)
		return false;

	SPCHESSGame* copy = spChessGameCopy(src);
	bool risker = false;
	if (spChessGameSetMove(copy, from, to) == SPCHESS_GAME_SUCCESS) {
		//player has changed!
		if (copy->currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL)
			risker = spChessIfPlayer2IsThreatening(copy);
		else
			risker = spChessIfPlayer1IsThreatening(copy);

		spChessGameUndoPrevMove(copy);
	}
	spChessGameDestroy(copy);
	return risker;
}

bool spChessGameValidMoveLoc(SPCHESSGame* src, move* elem) {
	if (!src || !elem)
		return false;

	//assuming the cordin' are valid and valid piece!
	int row_to = elem->to[0];
	int col_to = elem->to[1];
	bool validMove = false;

	int legalMoves[MAX_STEPS_PIECE][DIM]; //pre-allocated array of legal moves
	//init values with -1's
//	for (int i = 0; i < MAX_STEPS_PIECE; i++) {
//		for (int j = 0; j < DIM; j++) {
//			legalMoves[i][j] = -1;
//		}
//	}
	getLegalMovesForPiece(src, elem, legalMoves);
	//check if target location is one of the legal moves above
	for (int i = 0; i < MAX_STEPS_PIECE && legalMoves[i][0] != -1; i++) {
		if (legalMoves[i][0] == row_to && legalMoves[i][1] == col_to) { //it's legal move!
			validMove = true;
			break;
		}
	}
	return validMove;

}

void getLegalMovesForPiece(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {

	for (int i = 0; i < MAX_STEPS_PIECE; i++) {
		for (int j = 0; j < DIM; j++) {
			legalMoves[i][j] = -1;
		}
	}
	char piece = elem->piece;

	//decide moves acording to piece's type:
	if (piece == WHITE_R || piece == BLACK_R) {
		getLegalMovesForRook(src, elem, legalMoves);
		return;
	}
	if (piece == WHITE_N || piece == BLACK_N) {
		getLegalMovesForKnight(src, elem, legalMoves);
		return;
	}
	if (piece == WHITE_B || piece == BLACK_B) {
		getLegalMovesForBishop(src, elem, legalMoves);
		return;
	}
	if (piece == WHITE_Q || piece == BLACK_Q) {
		getLegalMovesForQueen(src, elem, legalMoves);
		return;
	}
	if (piece == WHITE_K || piece == BLACK_K) {
		getLegalMovesForKing(src, elem, legalMoves);
		return;
	}
	if (piece == WHITE_P) {
		getLegalMovesForWhitePawn(src, elem, legalMoves);
		return;
	} else
		getLegalMovesForBlackPawn(src, elem, legalMoves);
}

bool isSameColorAsGiven(SPCHESSGame* src, int row, int col, char givenColor) {
	if (!src)
		return false;
	char piece = src->gameBoard[row][col];
	if (givenColor == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		if (piece == WHITE_N || piece == WHITE_R || piece == WHITE_K
				|| piece == WHITE_B || piece == WHITE_Q || piece == WHITE_P)
			return true;
		else
			return false;
	} else { //givenPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		if (piece == BLACK_N || piece == BLACK_R || piece == BLACK_K
				|| piece == BLACK_B || piece == BLACK_Q || piece == BLACK_P)
			return true;
		else
			return false;
	}

}

void getLegalMovesForRook(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	char currentColor = getColorFromPiece(elem->piece);
	int row_from = elem->from[0];
	int col_from = elem->from[1];

	//right direction
	for (int j = col_from + 1; j < BOARD_SIZE; j++) {
		if (src->gameBoard[row_from][j] == EMPTY) {
			legalMoves[ind][0] = row_from;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, row_from, j, currentColor)) {
			legalMoves[ind][0] = row_from;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

	}

	//left direction
	for (int j = col_from - 1; j >= 0; j--) {
		if (src->gameBoard[row_from][j] == EMPTY) {
			legalMoves[ind][0] = row_from;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, row_from, j, currentColor)) { //opponant piece - cannot continue after this location in this direction
			legalMoves[ind][0] = row_from;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

	}

	//up direction
	for (int i = row_from + 1; i < BOARD_SIZE; i++) {
		if (src->gameBoard[i][col_from] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = col_from;
			ind++;
		} else if (!isSameColorAsGiven(src, i, col_from, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = col_from;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;
	}

	//down direction
	for (int i = row_from - 1; i >= 0; i--) {
		if (src->gameBoard[i][col_from] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = col_from;
			ind++;
		} else if (!isSameColorAsGiven(src, i, col_from, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = col_from;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;
	}
}

void getLegalMovesForBishop(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	int i, j;
	char currentColor = getColorFromPiece(elem->piece);

	//up-right direction
	i = row_from + 1;
	j = col_from + 1;
	while (i < BOARD_SIZE && j < BOARD_SIZE) {
		if (src->gameBoard[i][j] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, i, j, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

		i++;
		j++;
	}

	//up-left direction
	i = row_from + 1;
	j = col_from - 1;
	while (i < BOARD_SIZE && j >= 0) {
		if (src->gameBoard[i][j] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, i, j, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

		i++;
		j--;
	}

//down-right direction
	i = row_from - 1;
	j = col_from + 1;
	while (i >= 0 && j < BOARD_SIZE) {
		if (src->gameBoard[i][j] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, i, j, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

		i--;
		j++;
	}

//down-left direction
	i = row_from - 1;
	j = col_from - 1;
	while (i >= 0 && j >= 0) {
		if (src->gameBoard[i][j] == EMPTY) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
		} else if (!isSameColorAsGiven(src, i, j, currentColor)) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
			break;
		} else
			//same color - cannot continue this direction
			break;

		i--;
		j--;
	}
}

void getLegalMovesForKing(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	char currentColor = getColorFromPiece(elem->piece);
	//square 3*3 - 1
	for (int i = row_from - 1; i < row_from + 2; i++) {
		for (int j = col_from - 1; j < col_from + 2; j++) {
			if (i == row_from && j == col_from) // curr position of king, ignore
				continue;
			else {
				if (isInBoard(i, j)
						&& (src->gameBoard[i][j] == EMPTY
								|| !isSameColorAsGiven(src, i, j, currentColor))) {
					legalMoves[ind][0] = i;
					legalMoves[ind][1] = j;
					ind++;
				}
			}
		}
	}
}

void getLegalMovesForQueen(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {

	getLegalMovesForRook(src, elem, legalMoves);

	int movesAsBishop[MAX_STEPS_PIECE][DIM];
	for (int i = 0; i < MAX_STEPS_PIECE; i++) {
		for (int j = 0; j < DIM; j++)
			movesAsBishop[i][j] = -1;
	}
	getLegalMovesForBishop(src, elem, movesAsBishop);

	//concatenate the two arrays, assuming there are -1's in the end of eath one
	int ind = 0;
	while (legalMoves[ind][0] != -1)
		ind++;

	int i = 0;
	while (movesAsBishop[i][0] != -1) {
		legalMoves[ind][0] = movesAsBishop[i][0];
		legalMoves[ind][1] = movesAsBishop[i][1];
		ind++;
		i++;
	}
}

void getLegalMovesForKnight(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	int i, j;
	char currentColor = getColorFromPiece(elem->piece);
	int knightPossibleLoc[8][DIM] = { { row_from + 2, col_from - 1 }, { row_from
			+ 2, col_from + 1 }, { row_from + 1, col_from + 2 }, { row_from - 1,
			col_from + 2 }, { row_from - 2, col_from - 1 }, { row_from - 2,
			col_from + 1 }, { row_from + 1, col_from - 2 }, { row_from - 1,
			col_from - 2 } };

	for (int k = 0; k < 8; k++) {
		i = knightPossibleLoc[k][0];
		j = knightPossibleLoc[k][1];
		if (isInBoard(i, j)
				&& (src->gameBoard[i][j] == EMPTY
						|| !isSameColorAsGiven(src, i, j, currentColor))) {
			legalMoves[ind][0] = i;
			legalMoves[ind][1] = j;
			ind++;
		}
	}

}

void getLegalMovesForWhitePawn(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	int i, j;
	bool isPiece;
	char currentColor = getColorFromPiece(elem->piece);
	//up-left munch
	i = row_from + 1;
	j = col_from - 1;
	isPiece = src->gameBoard[i][j] != EMPTY;
	if (isInBoard(i, j) && isPiece
			&& !isSameColorAsGiven(src, i, j, currentColor)) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//up-right munch
	i = row_from + 1;
	j = col_from + 1;
	isPiece = src->gameBoard[i][j] != EMPTY;
	if (isInBoard(i, j) && isPiece
			&& !isSameColorAsGiven(src, i, j, currentColor)) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//up 1 regular
	i = row_from + 1;
	j = col_from;
	if (isInBoard(i, j) && src->gameBoard[i][j] == EMPTY) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//up 2 in case of first turn
	i = row_from + 2;
	j = col_from;
	if (row_from
			== 1&& src->gameBoard[i - 1][j] == EMPTY && src->gameBoard[i][j] == EMPTY) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}
}

void getLegalMovesForBlackPawn(SPCHESSGame* src, move* elem,
		int legalMoves[MAX_STEPS_PIECE][DIM]) {
	int ind = 0;

	int row_from = elem->from[0];
	int col_from = elem->from[1];
	int i, j;
	bool isPiece;
	char currentColor = getColorFromPiece(elem->piece);

	//down-left munch
	i = row_from - 1;
	j = col_from - 1;
	isPiece = src->gameBoard[i][j] != EMPTY;

	if (isInBoard(i, j) && isPiece
			&& !isSameColorAsGiven(src, i, j, currentColor)) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//down-right munch
	i = row_from - 1;
	j = col_from + 1;
	isPiece = src->gameBoard[i][j] != EMPTY;
	if (isInBoard(i, j) && isPiece
			&& !isSameColorAsGiven(src, i, j, currentColor)) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//down 1 regular
	i = row_from - 1;
	j = col_from;
	if (isInBoard(i, j) && src->gameBoard[i][j] == EMPTY) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}

	//down 2 in case of first turn
	i = row_from - 2;
	j = col_from;
	if (row_from
			== BOARD_SIZE
					- 2&& src->gameBoard[i + 1][j] == EMPTY && src->gameBoard[i][j] == EMPTY) {
		legalMoves[ind][0] = i;
		legalMoves[ind][1] = j;
		ind++;
	}
}

SPCHESS_GAME_MESSAGE spChessMoveHandler(SPCHESSGame* src, move* elem,
		char colorToMove) {
	if (!src || !elem)
		return SPCHESS_GAME_INVALID_ARGUMENT;

	//check if the position contains a piece if the user's color
	if (!isSameColorAsGiven(src, elem->from[0], elem->from[1], colorToMove))
		return SPCHESS_GAME_INVALID_COLOR;

	//check if the move is legal for the current piece or the move is king risker
	if (!spChessGameValidMoveLoc(src, elem))
		return SPCHESS_GAME_INVALID_MOVE;

	return SPCHESS_GAME_SUCCESS;

}

SPCHESS_GAME_MESSAGE spChessGameSetMove(SPCHESSGame* src, int from[DIM],
		int to[DIM]) {

	if (!src || !spChessGameIsValidMove(src, from, to))
		return SPCHESS_GAME_INVALID_ARGUMENT;

	//the move is valid-index thus it is safe to create move for other validation checks
	char piece = src->gameBoard[from[0]][from[1]];
	char eaten = src->gameBoard[to[0]][to[1]];
	bool isEaten = eaten != EMPTY;
	move* elem = spCreateMove(from, to, piece, eaten);

	SPCHESS_GAME_MESSAGE msg = spChessMoveHandler(src, elem,
			src->currentPlayer);
	if (msg != SPCHESS_GAME_SUCCESS) {
		spDestroyMove(elem);
		return msg;
	}

	//the move is completly valid thus can change game and history acoordingly
	src->gameBoard[from[0]][from[1]] = EMPTY;
	src->gameBoard[to[0]][to[1]] = piece;

	//update piecesArray
	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {

		//find the piece according to current location

		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer1[i][0] == from[0]
					&& src->piecesPlayer1[i][1] == from[1]) {
				src->piecesPlayer1[i][0] = to[0];
				src->piecesPlayer1[i][1] = to[1];
			}
		}
		if (isEaten) {
			for (int i = 0; i < NUM_OF_PIECES; i++) {
				if (src->piecesPlayer2[i][0] == to[0]
						&& src->piecesPlayer2[i][1] == to[1]) {
					src->piecesPlayer2[i][0] = EATEN;
					src->piecesPlayer2[i][1] = EATEN;
				}
			}
		}
	} else {
		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer2[i][0] == from[0]
					&& src->piecesPlayer2[i][1] == from[1]) {
				src->piecesPlayer2[i][0] = to[0];
				src->piecesPlayer2[i][1] = to[1];
			}
		}
		if (isEaten) {
			for (int i = 0; i < NUM_OF_PIECES; i++) {
				if (src->piecesPlayer1[i][0] == to[0]
						&& src->piecesPlayer1[i][1] == to[1]) {
					src->piecesPlayer1[i][0] = EATEN;
					src->piecesPlayer1[i][1] = EATEN;
				}
			}
		}
	}

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		//if the list moves is full, make room by removing the last elem
		if (spArrayListIsFull(src->movesPlayer1))
			spArrayListRemoveLast(src->movesPlayer1);
		spArrayListAddFirst(src->movesPlayer1, elem);
	} else { //currentPlayer = SPCHESS_GAME_PLAYER_2_SYMBOL
		if (spArrayListIsFull(src->movesPlayer2))
			spArrayListRemoveLast(src->movesPlayer2);
		spArrayListAddFirst(src->movesPlayer2, elem);
	}

	//change the player in the end of the turn
	spChessChangePlayer(src);
	spDestroyMove(elem);
	return SPCHESS_GAME_SUCCESS;

}

//undo move do to the other player
SPCHESS_GAME_MESSAGE spChessGameUndoPrevMove(SPCHESSGame* src) {
	if (!src)
		return SPCHESS_GAME_INVALID_ARGUMENT;
	move* elem;

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		if (spArrayListIsEmpty(src->movesPlayer2))
			return SPCHESS_GAME_NO_HISTORY;

		elem = spArrayListGetFirst(src->movesPlayer2);
		spArrayListRemoveFirst(src->movesPlayer2);
	} else {
		if (spArrayListIsEmpty(src->movesPlayer1))
			return SPCHESS_GAME_NO_HISTORY;

		elem = spArrayListGetFirst(src->movesPlayer1);
		spArrayListRemoveFirst(src->movesPlayer1);
	}
	//change the game back according to the last move
	src->gameBoard[elem->from[0]][elem->from[1]] = elem->piece;
	src->gameBoard[elem->to[0]][elem->to[1]] = elem->eaten; // can be empty if wasn't eaten
	bool isEaten = elem->eaten != EMPTY;

	//update piecesArray
	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer2[i][0] == elem->to[0]
					&& src->piecesPlayer2[i][1] == elem->to[1]) {
				src->piecesPlayer2[i][0] = elem->from[0];
				src->piecesPlayer2[i][1] = elem->from[1];
			}
		}
		if (isEaten) {
			int subArr[DIM] = { -1, -1 };
			getSubArrayFromPiece(elem->eaten, subArr);
			for (int i = subArr[0]; i <= subArr[1]; i++) {
				if (src->piecesPlayer1[i][0] == EATEN
						&& src->piecesPlayer1[i][1] == EATEN) {
					src->piecesPlayer1[i][0] = elem->to[0];
					src->piecesPlayer1[i][1] = elem->to[1];
				}
			}
		}
	} else {
		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer1[i][0] == elem->to[0]
					&& src->piecesPlayer1[i][1] == elem->to[1]) {
				src->piecesPlayer1[i][0] = elem->from[0];
				src->piecesPlayer1[i][1] = elem->from[1];
			}
		}
		if (isEaten) {
			int subArr[DIM] = { -1, -1 };
			getSubArrayFromPiece(elem->eaten, subArr);
			for (int i = subArr[0]; i <= subArr[1]; i++) {
				if (src->piecesPlayer2[i][0] == EATEN
						&& src->piecesPlayer2[i][1] == EATEN) {
					src->piecesPlayer2[i][0] = elem->to[0];
					src->piecesPlayer2[i][1] = elem->to[1];
				}
			}
		}
	}
	spChessChangePlayer(src); //change the turn
	return SPCHESS_GAME_SUCCESS;
}

SPCHESS_GAME_MESSAGE spChessGameUndoPrevMoveWithPrint(SPCHESSGame* src) {
	if (!src)
		return SPCHESS_GAME_INVALID_ARGUMENT;
	move* elem;

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		if (spArrayListIsEmpty(src->movesPlayer2))
			return SPCHESS_GAME_NO_HISTORY;

		elem = spArrayListGetFirst(src->movesPlayer2);
		spArrayListRemoveFirst(src->movesPlayer2);
	} else {
		if (spArrayListIsEmpty(src->movesPlayer1))
			return SPCHESS_GAME_NO_HISTORY;

		elem = spArrayListGetFirst(src->movesPlayer1);
		spArrayListRemoveFirst(src->movesPlayer1);
	}
	//change the game back according to the last move
	src->gameBoard[elem->from[0]][elem->from[1]] = elem->piece;
	src->gameBoard[elem->to[0]][elem->to[1]] = elem->eaten; // can be empty if wasn't eaten
	bool isEaten = elem->eaten != EMPTY;

	//update piecesArray
	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer2[i][0] == elem->to[0]
					&& src->piecesPlayer2[i][1] == elem->to[1]) {
				src->piecesPlayer2[i][0] = elem->from[0];
				src->piecesPlayer2[i][1] = elem->from[1];
			}
		}
		if (isEaten) {
			int subArr[DIM] = { -1, -1 };
			getSubArrayFromPiece(elem->eaten, subArr);
			for (int i = subArr[0]; i <= subArr[1]; i++) {
				if (src->piecesPlayer1[i][0] == EATEN
						&& src->piecesPlayer1[i][1] == EATEN) {
					src->piecesPlayer1[i][0] = elem->to[0];
					src->piecesPlayer1[i][1] = elem->to[1];
				}
			}
		}
	} else {
		for (int i = 0; i < NUM_OF_PIECES; i++) {
			if (src->piecesPlayer1[i][0] == elem->to[0]
					&& src->piecesPlayer1[i][1] == elem->to[1]) {
				src->piecesPlayer1[i][0] = elem->from[0];
				src->piecesPlayer1[i][1] = elem->from[1];
			}
		}
		if (isEaten) {
			int subArr[DIM] = { -1, -1 };
			getSubArrayFromPiece(elem->eaten, subArr);
			for (int i = subArr[0]; i <= subArr[1]; i++) {
				if (src->piecesPlayer2[i][0] == EATEN
						&& src->piecesPlayer2[i][1] == EATEN) {
					src->piecesPlayer2[i][0] = elem->to[0];
					src->piecesPlayer2[i][1] = elem->to[1];
				}
			}
		}
	}
	spChessChangePlayer(src); //change the turn

	//print the undo move
	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
		printf("Undo move for player white: <%d,%c> -> <%d,%c>\n",
				elem->from[0] + 1, (char) (elem->from[1] + 'A'),
				elem->to[0] + 1, (char) (elem->to[1] + 'A'));
	} else { //src->currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		printf("Undo move for player black: <%d,%c> -> <%d,%c>\n",
				elem->from[0] + 1, (char) (elem->from[1] + 'A'),
				elem->to[0] + 1, (char) (elem->to[1] + 'A'));
	}
	return SPCHESS_GAME_SUCCESS;
}

//return the symbol of the color which is in the state of mate, if there is, null o/w.
char spChessIfMate(SPCHESSGame* src) {
	if (!src)
		return '\0';

	SPCHESSGame* copy = spChessGameCopy(src);

	if (spChessIfPlayer1IsThreatening(copy)) {
		spChessGameDestroy(copy);
		return SPCHESS_GAME_PLAYER_2_SYMBOL;
	} else if (spChessIfPlayer2IsThreatening(copy)) {
		spChessGameDestroy(copy);
		return SPCHESS_GAME_PLAYER_1_SYMBOL;
	}
	spChessGameDestroy(copy);
	return '\0';

}

bool spChessIfPlayer1IsThreatening(SPCHESSGame* src) {
	bool isMate = false;
	int to[DIM] = { src->piecesPlayer2[15][0], src->piecesPlayer2[15][1] }; //black king's location
	char piece, king = src->gameBoard[to[0]][to[1]];
	//find pieces who can threaten the black king
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer1[i][0] >= 0 && src->piecesPlayer1[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer1[i][0], src->piecesPlayer1[i][1] };
			piece = src->gameBoard[from[0]][from[1]];
			move* elem = spCreateMove(from, to, piece, king);
			if (spChessMoveHandler(src, elem, SPCHESS_GAME_PLAYER_1_SYMBOL)
					== SPCHESS_GAME_SUCCESS) { //found a piece
				isMate = true;
				spDestroyMove(elem);
				break;
			}
			spDestroyMove(elem);
		}
	}
	return isMate;
}

bool spChessIfPlayer2IsThreatening(SPCHESSGame* src) {
	bool isMate = false;
	int to[DIM] = { src->piecesPlayer1[15][0], src->piecesPlayer1[15][1] }; //white king's location
	char piece, king = src->gameBoard[to[0]][to[1]];

//find pieces who can threaten the white king
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer2[i][0] >= 0 && src->piecesPlayer2[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer2[i][0], src->piecesPlayer2[i][1] };

			piece = src->gameBoard[from[0]][from[1]];
			move* elem = spCreateMove(from, to, piece, king);
			if (spChessMoveHandler(src, elem, SPCHESS_GAME_PLAYER_2_SYMBOL)
					== SPCHESS_GAME_SUCCESS) { //found a piece
				isMate = true;
				spDestroyMove(elem);
				break;
			}
			spDestroyMove(elem);
		}
	}
	return isMate;
}

char spChessGameCheckWinner(SPCHESSGame* src) {
	if (!src)
		return '\0';

	char winner = '\0';

	SPCHESSGame* copy1 = spChessGameCopy(src);
	if (!copy1)
		return '\0';

	SPCHESSGame* copy2 = spChessGameCopy(src);
	if (!copy2)
		return '\0';

	if (spChessIfPlayer1Win(copy1))
		winner = SPCHESS_GAME_PLAYER_1_SYMBOL;
	else if (spChessIfPlayer2Win(copy2))
		winner = SPCHESS_GAME_PLAYER_2_SYMBOL;

	spChessGameDestroy(copy2);
	spChessGameDestroy(copy1);
	return winner;

}

bool spChessIfPlayer1Win(SPCHESSGame* src) {
	if (!src)
		return false;

	return spChessIfPlayer1IsThreatening(src) && !existsPlayer2KingSaver(src);
}

bool spChessIfPlayer2Win(SPCHESSGame* src) {
	if (!src)
		return false;

	return spChessIfPlayer2IsThreatening(src) && !existsPlayer1KingSaver(src);
}

bool existsPlayer2KingSaver(SPCHESSGame* src) {
	if (!src)
		return false;

	src->currentPlayer = SPCHESS_GAME_PLAYER_2_SYMBOL; // (?)
	bool exist = false;
//check if there is a move that after it the king is not threated
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer2[i][0] >= 0 && src->piecesPlayer2[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer2[i][0], src->piecesPlayer2[i][1] };
			for (int m = 0; m < BOARD_SIZE; m++) {
				for (int k = 0; k < BOARD_SIZE; k++) {
					int to[DIM] = { m, k };
					if (spChessGameSetMove(src, from, to)
							== SPCHESS_GAME_SUCCESS) {
						if (!spChessIfPlayer1IsThreatening(src)) {
							exist = true;
							spChessGameUndoPrevMove(src);
							break;
						}
						spChessGameUndoPrevMove(src);
					}
				}
			}
		}
	}
	return exist;
}

bool existsPlayer1KingSaver(SPCHESSGame* src) {
	if (!src)
		return false;

	src->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL; // (?)
	bool exist = false;
//check if there is a move that after it the king is not threated
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer1[i][0] >= 0 && src->piecesPlayer1[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer1[i][0], src->piecesPlayer1[i][1] };
			for (int m = 0; m < BOARD_SIZE; m++) {
				for (int k = 0; k < BOARD_SIZE; k++) {
					int to[DIM] = { m, k };

					if (spChessGameSetMove(src, from, to)
							== SPCHESS_GAME_SUCCESS) {
						if (!spChessIfPlayer2IsThreatening(src)) {
							exist = true;
							spChessGameUndoPrevMove(src);
							break;
						}
						spChessGameUndoPrevMove(src);
					}
				}
			}
		}
	}
	return exist;
}

char spChessGameCheckTie(SPCHESSGame* src) {
	if (!src)
		return '\0';

	SPCHESSGame* copy1 = spChessGameCopy(src);
	if (!copy1)
		return '\0';

	SPCHESSGame* copy2 = spChessGameCopy(src);
	if (!copy2)
		return '\0';

	char tie = '\0';

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) { //a tie in white
		if (!spChessIfPlayer2IsThreatening(copy1)
				&& !existsValidMovePlayer1(copy1))
			tie = SPCHESS_GAME_TIE_SYMBOL;
	} else {
		if (!spChessIfPlayer1IsThreatening(copy2)
				&& !existsValidMovePlayer2(copy2))
			tie = SPCHESS_GAME_TIE_SYMBOL;
	}

	spChessGameDestroy(copy2);
	spChessGameDestroy(copy1);
	return tie;

}

bool existsValidMovePlayer1(SPCHESSGame* src) {
	if (!src)
		return false;

	move* elem;
	bool exist = false;
	char piece, eaten;
//check if there is a move that after it the king is not threated
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer1[i][0] >= 0 && src->piecesPlayer1[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer1[i][0], src->piecesPlayer1[i][1] };
			for (int m = 0; m < BOARD_SIZE; m++) {
				for (int k = 0; k < BOARD_SIZE; k++) {
					int to[DIM] = { m, k };
					piece = src->gameBoard[from[0]][from[1]];
					eaten = src->gameBoard[to[0]][to[1]];
					elem = spCreateMove(from, to, piece, eaten);
					if (spChessMoveHandler(src, elem,
					SPCHESS_GAME_PLAYER_1_SYMBOL) == SPCHESS_GAME_SUCCESS
							&& !spChessGameIsKingRisker(src, from, to)) {
						exist = true;
						spDestroyMove(elem);
						break;
					}
					spDestroyMove(elem);
				}
			}
		}
	}
	return exist;
}

bool existsValidMovePlayer2(SPCHESSGame* src) {
	if (!src)
		return false;

	move* elem;
	bool exist = false;
	char piece, eaten;
//check if there is a move that after it the king is not threated
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		if (src->piecesPlayer2[i][0] >= 0 && src->piecesPlayer2[i][1] >= 0) {
			int from[DIM] =
					{ src->piecesPlayer2[i][0], src->piecesPlayer2[i][1] };
			for (int m = 0; m < BOARD_SIZE; m++) {
				for (int k = 0; k < BOARD_SIZE; k++) {
					int to[DIM] = { m, k };
					piece = src->gameBoard[from[0]][from[1]];
					eaten = src->gameBoard[to[0]][to[1]];
					elem = spCreateMove(from, to, piece, eaten);
					if (spChessMoveHandler(src, elem,
					SPCHESS_GAME_PLAYER_2_SYMBOL) == SPCHESS_GAME_SUCCESS
							&& !spChessGameIsKingRisker(src, from, to)) {
						exist = true;
						spDestroyMove(elem);
						break;
					}
					spDestroyMove(elem);
				}
			}
		}
	}
	return exist;
}

char spChessGameGetCurrentPlayer(SPCHESSGame* src) {
//if (!src)
//	SPCHESS_GAME_EMPTY_ENTRY;
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

char getColorFromPiece(char piece) {
	if (piece == EMPTY)
		return '\0';

	if (piece == WHITE_N || piece == WHITE_R || piece == WHITE_K
			|| piece == WHITE_B || piece == WHITE_Q || piece == WHITE_P) {
		return SPCHESS_GAME_PLAYER_1_SYMBOL;
	}
//it is a black piece
	return SPCHESS_GAME_PLAYER_2_SYMBOL;
}

void getSubArrayFromPiece(char piece, int subArray[DIM]) {

	if (piece == WHITE_R || piece == BLACK_R) {
		subArray[0] = 12;
		subArray[1] = 13;
		return;
	}
	if (piece == WHITE_N || piece == BLACK_N) {
		subArray[0] = 8;
		subArray[1] = 9;
		return;
	}
	if (piece == WHITE_B || piece == BLACK_B) {
		subArray[0] = 10;
		subArray[1] = 11;
		return;
	}
	if (piece == WHITE_Q || piece == BLACK_Q) {
		subArray[0] = 14;
		subArray[1] = 14;
		return;
	}
	if (piece == WHITE_K || piece == BLACK_K) {
		subArray[0] = 15;
		subArray[1] = 15;
		return;
	}
	if (piece == WHITE_P || piece == BLACK_P) {
		subArray[0] = 0;
		subArray[1] = 7;
		return;
	}
}
