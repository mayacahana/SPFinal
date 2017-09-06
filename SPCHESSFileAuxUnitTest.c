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

	spChessGameDestroy(src);
	return true;
}

int main(){
	RUN_TEST(spFileAuxTest);
	return 0;
}
