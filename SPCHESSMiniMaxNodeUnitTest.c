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

	spChessGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spChessMiniMaxNodeBasicTest);
	return 0;
}

