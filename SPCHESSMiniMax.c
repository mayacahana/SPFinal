/*
 * SPCHESSMiniMax.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

#include "SPCHESSMiniMax.h"

move* spChessMiniMaxSuggestMove(SPCHESSGame* src, unsigned int maxDepth) {
	if (!src || maxDepth <= 0)
		return NULL;

	int childValue = 0;
	int max = INT_MIN; //first iteration - max
	int from[DIM];
	int fromBest[DIM], toBest[DIM], legalMoves[MAX_STEPS_PIECE][DIM];
	SPCHESSGame* copy = spChessGameCopy(src);

	if (!copy)
		return NULL;

	//check if the game is in terminal state
	if (spChessGameCheckWinner(copy) != '\0'
			|| spChessGameCheckTie(copy) != '\0') {
		spChessGameDestroy(copy);
		return NULL;
	}

	char currentPlayer = spChessGameGetCurrentPlayer(copy);

	//first iteration "manually" to check which child is the best
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
		WHITE_P);
		getLegalMovesForPiece(src, step, legalMoves);
		spDestroyMove(step);
		for (int k = 0; k < MAX_STEPS_PIECE && legalMoves[k][0] != -1; k++) {
			int to[DIM] = { legalMoves[k][0], legalMoves[k][1] };
			if (!spChessGameIsKingRisker(copy, from, to)
					&& spChessGameSetMove(copy, from, to)
							== SPCHESS_GAME_SUCCESS) {
				childValue = computeValueRec(copy, maxDepth - 1, INT_MIN,
				INT_MAX, false, currentPlayer);
				if (childValue > max) {
					max = childValue;
					fromBest[0] = from[0];
					fromBest[1] = from[1];
					toBest[0] = to[0];
					toBest[1] = to[1];
				}
				spChessGameUndoPrevMove(copy);
			}
		}
//		//location where to move
//		for (int k = 0; k < BOARD_SIZE; k++) {
//			for (int p = 0; p < BOARD_SIZE; p++) {
//				int to[DIM] = { k, p };
//
//				if (!spChessGameIsKingRisker(copy, from, to)
//						&& spChessGameSetMove(copy, from, to)
//								== SPCHESS_GAME_SUCCESS) {
//					childValue = computeValueRec(copy, maxDepth - 1, INT_MIN,
//							INT_MAX, false, currentPlayer);
//					if (childValue > max) {
//						max = childValue;
//						fromBest[0] = from[0];
//						fromBest[1] = from[1];
//						toBest[0] = to[0];
//						toBest[1] = to[1];
//					}
//					spChessGameUndoPrevMove(copy);
//				}
//			}
//		}
	}
	char pieceBest = copy->gameBoard[fromBest[0]][fromBest[1]];
	char eatenBest = copy->gameBoard[toBest[0]][toBest[1]];
	move* best = spCreateMove(fromBest, toBest, pieceBest, eatenBest);
	spChessGameDestroy(copy);
	return best;
}

