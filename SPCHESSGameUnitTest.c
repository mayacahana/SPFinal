/*
 * SPCHESSGameUnitTest.c
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */
#include "unit_test_util.h"
#include "SPCHESSGame.h"

#define HISTORY_SIZE 6

//static bool spFiarGameValidMoveTest() {
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//	ASSERT_TRUE(res!=NULL);
//	int repeat = SP_FIAR_GAME_N_ROWS;
//	while (repeat-- > 0) {
//		ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//	}
//	ASSERT_FALSE(spFiarGameIsValidMove(res, 2));
//	ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_INVALID_MOVE);
//	spFiarGamePrintBoard(res);
//	spFiarGameDestroy(res);
//	return true;
//}
//
//static bool spFiarGameUndoMoveTest2() {
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//	ASSERT_TRUE(res!=NULL);
//	int repeat = 3;
//	while (repeat-- > 0) {
//		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//		}
//	}
//	repeat = 20;
//	while (repeat-- > 0) {
//		ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
//	}
//	ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_NO_HISTORY);
//	spFiarGamePrintBoard(res);
//	spFiarGameDestroy(res);
//	return true;
//}
//static bool spFiarGameUndoMoveTest() {
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//	ASSERT_TRUE(res!=NULL);
//	int repeat = 2;
//	while (repeat-- > 0) {
//		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//		}
//	}
//	repeat = 2;
//	while (repeat-- > 0) {
//		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//			ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
//		}
//	}
//	spFiarGamePrintBoard(res);
//	spFiarGameDestroy(res);
//	return true;
//}
//
//static bool spFiarGameSetMoveTest() {
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//	ASSERT_TRUE(res!=NULL);
//	int repeat = 2;
//	while (repeat-- > 0) {
//		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//		}
//	}
//	spFiarGamePrintBoard(res);
//	spFiarGameDestroy(res);
//	return true;
//}

static bool spChessGameBasicTest() {
	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
			SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
	ASSERT_TRUE(res!=NULL);

	spChessGamePrintBoard(res);

	spChessGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spChessGameBasicTest);
	//RUN_TEST(spFiarGameSetMoveTest);
	//RUN_TEST(spFiarGameUndoMoveTest);
	//RUN_TEST(spFiarGameUndoMoveTest2);
	//RUN_TEST(spFiarGameValidMoveTest);
	return 0;
}
