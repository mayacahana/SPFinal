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

	ASSERT_TRUE(scoringFunc(res, SPCHESS_GAME_PLAYER_1_SYMBOL) == 0);

	spChessGamePrintBoard(res);
	computeValueRec(res, 2, INT_MIN, INT_MAX, true, SPCHESS_GAME_PLAYER_1_SYMBOL);
	spChessGamePrintBoard(res);

	spChessGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spChessMiniMaxNodeBasicTest);
	return 0;
}

