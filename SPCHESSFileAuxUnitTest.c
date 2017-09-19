/*
 * SPCHESSFileAuxUnitTest.c
 *
 *  Created on: Aug 29, 2017
 *      Author: mayacahana
 */
#include "unit_test_util.h"
#include "SPCHESSFileAux.h"

static bool spFileAuxTest() {
	char* path = "1.xml";

	SPCHESSGame* src = getStateFromFile(path);

	for(int i = 0; i< NUM_OF_PIECES; i++) {
		printf("the white piece loc is: <%d,%d>\n", src->piecesPlayer1[i][0], src->piecesPlayer1[i][1]);
		//printf("the black piece loc is: <%d,%d>\n", src->piecesPlayer2[i][0], src->piecesPlayer2[i][1]);
	}
	spChessGamePrintBoard(src);
	spChessGameDestroy(src);
	return true;
}

int fileauxtest(){
	RUN_TEST(spFileAuxTest);
	return 0;
}
