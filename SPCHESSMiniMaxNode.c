/*
 * SPCHESSMiniMaxNode.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#include "SPCHESSMiniMaxNode.h"

int scoringFunc(SPCHESSGame* src, char currentPlayer) {
	if (!src)
		return 0;

	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			score += getPieceValue(src->gameBoard[i][j], currentPlayer);
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
	case EMPTY:
		return 0;
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
	}
	return 0;
}

int computeValueRec(SPCHESSGame* src, int maxRecLvl, int alpha, int beta,
		bool flag, char colorForFunc) {

	//halts conditions
	char winner = spChessGameCheckWinner(src);
	if (winner != '\0') {
		if (winner == colorForFunc)
			return (4000); //plus "inf"
		else
			return (-4000); //minus "inf"
	} else if (maxRecLvl == 0)
		return scoringFunc(src, colorForFunc);

	//init value
	int value = (flag) ? INT_MIN : INT_MAX;
	int from[DIM], legalMoves[MAX_STEPS_PIECE][DIM];

	for (int i = 0; i < NUM_OF_PIECES; i++) {
		//who's pieces to check
		if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
			if (src->piecesPlayer1[i][0] >= 0
					&& src->piecesPlayer1[i][1] >= 0) {
				from[0] = src->piecesPlayer1[i][0];
				from[1] = src->piecesPlayer1[i][1];
			} else
				continue;
		} else {
			if (src->piecesPlayer2[i][0] >= 0
					&& src->piecesPlayer2[i][1] >= 0) {
				from[0] = src->piecesPlayer2[i][0];
				from[1] = src->piecesPlayer2[i][1];
			} else
				continue;
		}

		move* step = spCreateMove(from, from, src->gameBoard[from[0]][from[1]],
				EMPTY);
		getLegalMovesForPiece(src, step, legalMoves);
		spDestroyMove(step);

		for (int k = 0; k < MAX_STEPS_PIECE && legalMoves[k][0] != -1; k++) {
			int to[DIM] = { legalMoves[k][0], legalMoves[k][1] };
			if (!spChessGameIsKingRisker(src, from, to)
					&& spChessGameSetMove(src, from, to)
					== SPCHESS_GAME_SUCCESS) {
				value = decider(value,
						computeValueRec(src, maxRecLvl - 1, alpha, beta, !flag,
								colorForFunc), flag);
				spChessGameUndoPrevMove(src);

				if (flag)
					alpha = decider(alpha, value, flag);
				else
					beta = decider(beta, value, flag);

				if (beta <= alpha)
					break;

			}
		}
		//location where to go
		//		for (int k = 0; k < BOARD_SIZE; k++) {
		//			for (int p = 0; p < BOARD_SIZE; p++) {
		//				int to[DIM] = { k, p };
		//				if (!spChessGameIsKingRisker(src, from, to)
		//						&& spChessGameSetMove(src, from, to)
		//								== SPCHESS_GAME_SUCCESS) {
		//					value = decider(value,
		//							computeValueRec(src, maxRecLvl - 1, alpha, beta,
		//									!flag, colorForFunc), flag);
		//					spChessGameUndoPrevMove(src);
		//
		//					if (flag)
		//						alpha = decider(alpha, value, flag);
		//					else
		//						beta = decider(beta, value, flag);
		//
		//					if (beta <= alpha) {
		//						printf("gizom!\n");
		//						break;
		//					}
		//				}
		//			}
		//		}
	}
	return value;
}

int decider(int value, int curr, bool flag) {
	//if the flag equals TRUE, take a MAX between elems
	if (flag)
		return MAX(value, curr);
	else
		return MIN(value, curr);
}

