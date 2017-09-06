/*
 * SPCHESSMiniMaxNodeUnitTest.c
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */

#include "unit_test_util.h"
#include "SPCHESSMiniMaxNode.h"

static bool spChessMiniMaxNodeBasicTest() {
	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);

	int from[DIM], to[DIM];
	for (int i = 0; i < BOARD_SIZE / 2; i++) {
		from[0] = 1;
		from[1] = i;
		to[0] = 3;
		to[1] = i;
		ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);

		from[0] = 6;
		from[1] = i;
		to[0] = 4;
		to[1] = i;
		ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);

	}

	spChessGamePrintBoard(res);
	printf("the final value is: %d\n",
			computeValueRec(res, 1, INT_MIN, INT_MAX, true,
			SPCHESS_GAME_PLAYER_1_SYMBOL));

	spChessGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spChessMiniMaxNodeBasicTest);
	return 0;
}

