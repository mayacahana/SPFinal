/*
 * SPCHESSMiniMaxNodeUnitTest.c
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */

#include "unit_test_util.h"
#include "SPCHESSMiniMaxNode.h"

static bool spChessMiniMaxNodeBasicTest() {
	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
	ASSERT_TRUE(res!=NULL);

	//white's turn - pawn
	int from[DIM] = { 1, 3 };
	int to[DIM] = { 3, 3 };
	ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);

	ASSERT_TRUE(scoringFunc(res, SPCHESS_GAME_PLAYER_1_SYMBOL) == 0);
	ASSERT_TRUE(scoringFunc(res, SPCHESS_GAME_PLAYER_2_SYMBOL) == 0);

	spChessGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spChessMiniMaxNodeBasicTest);
	return 0;
}

