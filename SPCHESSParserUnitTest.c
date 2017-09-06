/*
 * SPCHESSParserUnitTest.c
 *
 *  Created on: 18 באוג׳ 2017
 *      Author: uri
 */

#include "unit_test_util.h"
#include "SPCHESSParser.h"

static bool spParserCheckIsInt() {
	ASSERT_TRUE(spParserIsInt("1"));
	ASSERT_TRUE(spParserIsInt("11"));
	ASSERT_TRUE(spParserIsInt("111"));
	ASSERT_TRUE(spParserIsInt("-1"));
	ASSERT_TRUE(spParserIsInt("-11"));
	ASSERT_TRUE(spParserIsInt("-111"));
	ASSERT_TRUE(spParserIsInt("01"));
	ASSERT_TRUE(spParserIsInt("011"));
	ASSERT_TRUE(spParserIsInt("0111"));
	ASSERT_TRUE(spParserIsInt("-01"));
	ASSERT_TRUE(spParserIsInt("-011"));
	ASSERT_TRUE(spParserIsInt("-0111"));
	return true;
}
static bool spParserCheckParseLine() {
	SPCHESS_GAME_MODE_Command cmd;
	//valid commands for game:

	cmd = spParserPraseGameModeLine("move <2,A> to <3,A>");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_MOVE && !cmd.validOneStr && cmd.validTwoStr
					&& strcmp(cmd.strOne, "<2,A>") == 0
					&& strcmp(cmd.strTwo, "<3,A>") == 0);

	free(cmd.strOne);
	free(cmd.strTwo);
	cmd = spParserPraseGameModeLine("get_moves <2,B>");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_GET_MOVES && cmd.validOneStr && !cmd.validTwoStr
					&& strcmp(cmd.strOne, "<2,B>") == 0);

	free(cmd.strOne);

	cmd = spParserPraseGameModeLine("save path");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_SAVE && cmd.strOne
					&& strcmp(cmd.strOne, "path") == 0);

	free(cmd.strOne);

	cmd = spParserPraseGameModeLine("undo");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_UNDO && !cmd.validOneStr && !cmd.validTwoStr);

	cmd = spParserPraseGameModeLine("reset");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_RESET && !cmd.validOneStr && !cmd.validTwoStr);

	cmd = spParserPraseGameModeLine("quit");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_QUIT && !cmd.validOneStr && !cmd.validTwoStr);

	cmd = spParserPraseGameModeLine("invalid fgfg");
	ASSERT_TRUE(
			cmd.cmd == SPCHESS_INVALID_LINE && !cmd.validOneStr
					&& !cmd.validTwoStr);

	char* pat = "<1,C>";
	ASSERT_TRUE(checkPosPat(pat));

	return true;
}
int main() {
	RUN_TEST(spParserCheckIsInt);
	RUN_TEST(spParserCheckParseLine);
	return 0;
}
