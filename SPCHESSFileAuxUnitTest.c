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
	assert(src!=NULL);
	spChessGamePrintBoard(src);


}

int main(){
	RUN_TEST(spFileAuxTest);

	return 0;
}