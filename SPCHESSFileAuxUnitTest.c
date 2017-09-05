/*
 * SPCHESSFileAuxUnitTest.c
 *
 *  Created on: Aug 29, 2017
 *      Author: mayacahana
 */
#include "unit_test_util.h"
#include "SPCHESSFileAux.h"

static bool spFileAuxTest() {
	char* path = "in.xml";

	SPCHESSGame* src = getStateFromFile(path);

	spChessGamePrintBoard(src);
	ASSERT_TRUE(src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL);
	ASSERT_TRUE(src->gameMode == 1);
	ASSERT_TRUE(src->difficulty == 2);
	ASSERT_TRUE(src->colorUser == 0);

	spChessGameDestroy(src);
	return true;
}

int main(){
	RUN_TEST(spFileAuxTest);
	return 0;
}
