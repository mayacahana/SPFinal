/*
 * SPCHESSMainUnitTest.c
 *
 *  Created on: Sep 2, 2017
 *      Author: mayacahana
 */
#include "unit_test_util.h"
#include "SPCHESSMainAux.h"
#include "SPCHESSGame.h"

//static bool spTestFiles() {
//	SPCHESSGame* res = spChessGameCreate(HISTORY_SIZE, 1,
//	SPCHESS_GAME_PLAYER_1_SYMBOL, 2);
//	//white's turn - pawn
//	int from[DIM] = { 1, 4 };
//	int to[DIM] = { 3, 4 };
//	ASSERT_TRUE(spChessGameSetMove(res, from, to) == SPCHESS_GAME_SUCCESS);
//
//	//black's turn - pawn
//	int from1[DIM] = { 6, 3 };
//	int to1[DIM] = { 4, 3 };
//	ASSERT_TRUE(spChessGameSetMove(res, from1, to1) == SPCHESS_GAME_SUCCESS);
//
//	//white's turn - pawn eats
//	int from2[DIM] = { 3, 4 };
//	int to2[DIM] = { 4, 3 };
//	ASSERT_TRUE(spChessGameSetMove(res, from2, to2) == SPCHESS_GAME_SUCCESS);
//
//	spChessGamePrintBoard(res);
//	//check save and load
//	//write:
//	saveGameToFile("output.xml",res);
//	ASSERT_TRUE(spChessGameUndoPrevMove(res) == SPCHESS_GAME_SUCCESS);
//	spChessGamePrintBoard(res);
//	spChessGameDestroy(res);
//	//load:
//	SPCHESSGame* game = spChessGameCreate(0,0,0,0);
//	game = getStateFromFile("output.xml");
//	spChessGamePrintBoard(res);
//
//}
//static bool spMainCreateTest() {
//	SPCHESSGame* game = spChessGameCreate(HISTORY_SIZE, DEFAULT_GAME_MODE,
//			DEFAULT_USER_COLOR, DEFAULT_DIFFICULTY);
//	bool userIsWhite;
//	ASSERT_TRUE(game != NULL);
//	//test the minimax nodes
//	return true;
//}

int maintester() {
	//RUN_TEST(spTestFiles);
	return 0;

}
