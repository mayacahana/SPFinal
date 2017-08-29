/*
 * SPCHESSFileAuxUnitTest.c
 *
 *  Created on: Aug 29, 2017
 *      Author: mayacahana
 */
#include "unit_test_util.h"
#include "SPCHESSFileAux.h"

static bool spFileAuxTest() {
	char* path = "input.xml";

	SPCHESSGame* src = getStateFromFile(path);
	//ASSERT(src!= NULL);

	spChessGamePrintBoard(src);

	spChessGameDestroy(src);
	return true;
}

int main(){
	RUN_TEST(spFileAuxTest);

	return 0;
}
