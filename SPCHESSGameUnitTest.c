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
//
//	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
//	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
//	ASSERT_TRUE(res!=NULL);
//
//	//white's turn - pawn
//	int from[DIM] = { 1, 3 };
//	int to[DIM] = { 3, 3 };
//	ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);
//
//	//black's turn - pawn
//	int from1[DIM] = { 6, 0 };
//	int to1[DIM] = { 4, 0 };
//	ASSERT_TRUE(spChessGameSetMove(res, from1, to1) == SPCHESS_GAME_SUCCESS);
//
//	//white's turn - bishop
//	int from2[DIM] = { 0, 2 };
//	int to2[DIM] = { 3, 5 };
//	ASSERT_TRUE(spChessGameSetMove(res, from2, to2) == SPCHESS_GAME_SUCCESS);
//
//	//black's turn - rook
//	int from3[DIM] = { 7, 0 };
//	int to3[DIM] = { 5, 0 };
//	ASSERT_TRUE(spChessGameSetMove(res, from3, to3) == SPCHESS_GAME_SUCCESS);
//
//	//white's turn - queen
//	int from4[DIM] = { 0, 3 };
//	int to4[DIM] = { 3, 3 };
//	ASSERT_FALSE(spChessGameSetMove(res, from4, to4) == SPCHESS_GAME_SUCCESS);
//
//	spChessGamePrintBoard(res);
//	spChessGameDestroy(res);
//	return true;
//}
//
//static bool spChessGameCheckMateTest() {
//	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
//	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
//	ASSERT_TRUE(res!=NULL);
//
//	white's turn - pawn
//	int from[DIM] = { 1, 5 };
//	int to[DIM] = { 3, 5 };
//	ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);
//
//	//black's turn - pawn
//	int from1[DIM] = { 6, 4 };
//	int to1[DIM] = { 5, 4 };
//	ASSERT_TRUE(spChessGameSetMove(res, from1, to1) == SPCHESS_GAME_SUCCESS);
//
//	//white's turn - pawn
//	int from2[DIM] = { 1, 6 };
//	int to2[DIM] = { 3, 6 };
//	ASSERT_TRUE(spChessGameSetMove(res, from2, to2) == SPCHESS_GAME_SUCCESS);
//
//	//black's turn - queen to check!
//	int from3[DIM] = { 7, 3 };
//	int to3[DIM] = { 3, 7 };
//	ASSERT_TRUE(spChessGameSetMove(res, from3, to3) == SPCHESS_GAME_SUCCESS);
//
//	spChessGamePrintBoard(res);
//
//	ASSERT_FALSE(spChessGameCheckTie(res) == SPCHESS_GAME_TIE_SYMBOL);
//
//	spChessGameDestroy(res);
//	return true;
//}

static bool spChessGameUndoMoveTest() {
	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
	ASSERT_TRUE(res!=NULL);

	//white's turn - pawn
	int from[DIM] = { 1, 4 };
	int to[DIM] = { 3, 4 };
	ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);

	//black's turn - pawn
	int from1[DIM] = { 6, 3 };
	int to1[DIM] = { 4, 3 };
	ASSERT_TRUE(spChessGameSetMove(res, from1, to1) == SPCHESS_GAME_SUCCESS);

	//white's turn - pawn eats
	int from2[DIM] = { 3, 4 };
	int to2[DIM] = { 4, 3 };
	ASSERT_TRUE(spChessGameSetMove(res, from2, to2) == SPCHESS_GAME_SUCCESS);

	spChessGamePrintBoard(res);
	ASSERT_TRUE(spChessGameUndoPrevMove(res) == SPCHESS_GAME_SUCCESS);

	spChessGamePrintBoard(res);
	spChessGameDestroy(res);
	return true;
}

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

//static bool spChessGameBasicTest() {
//	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
//	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
//	ASSERT_TRUE(res!=NULL);
//	spChessGamePrintBoard(res);
//
//	SPCHESSGame* copy = spChessGameCopy(res);
//	ASSERT_TRUE(copy!=NULL);
//
//	ASSERT_TRUE(res->currentPlayer == copy->currentPlayer);
//
//	spChessGameDestroy(copy);
//	spChessGameDestroy(res);
//	return true;
//}

int main() {
	//RUN_TEST(spChessGameBasicTest);
	//RUN_TEST(spFiarGameSetMoveTest);
	RUN_TEST(spChessGameUndoMoveTest);
	//RUN_TEST(spChessGameCheckMateTest);
	//RUN_TEST(spFiarGameValidMoveTest);
	return 0;
}
