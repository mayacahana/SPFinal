CC = gcc
OBJS = SPCHESSMiniMaxNode.o SPCHESSMiniMax.o SPCHESSGame.o SPCHESSArrayList.o SPCHESSParser.o SPCHESSMainAux.o main.o
EXEC = chessprog
GAME_TEST_OBJS = SPArrayList.o SPFIARGame.o SPFIARGameUnitTest.o
ARRAY_LIST_TEST_OBJS = SPCHESSArrayListUnitTest.o SPCHESSArrayList.o
PARSER_TEST_OBJS = SPCHESSParser.o SPCHESSParserUnitTest.o
MINMAXNode_TEST_OBJ = SPMiniMaxNode.o SPMiniMaxNodeUnitTest.o SPFIARGame.o SPArrayList.o
MINMAX_TEST_OBJ = SPMiniMaxNode.o SPMiniMax.o SPMiniMaxUnitTest.o SPFIARGame.o SPArrayList.o
MAINAUX_TEST_OBJS = SPMainAux.o SPArrayList.o SPFIARGame.o SPMiniMax.o SPMiniMaxNode.o
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
UNIT_TESTS = SPCHESSParserUnitTest SPCHESSArrayListUnitTest SPFIARParser SPMiniMaxUnitTest\
SPMiniMaxNodeUnitTest SPMainAuxUnitTest

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
SPFIARGameUnitTest: $(GAME_TEST_OBJS)
	$(CC) $(GAME_TEST_OBJS) -o $@
SPCHESSArrayListUnitTest: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
SPCHESSParserUnitTest: $(PARSER_TEST_OBJS)
	$(CC) $(PARSER_TEST_OBJS) -o $@
SPMiniMaxUnitTest: $(MINMAX_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMiniMaxNodeUnitTest: $(MINMAXNode_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMainAuxUnitTest: $(MAINAUX_TEST_OBJS)
	$(CC) $(MAINAUX_TEST_OBJS) -o $@
SPFIARGameUnitTest.o: SPFIARGameUnitTest.c unit_test_util.h SPArrayList.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPArrayListUnitTest.o: SPArrayListUnitTest.c SPArrayList.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParserUnitTest.o: SPCHESSParserUnitTest.c SPCHESSParser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxUnitTest.o: SPMiniMaxUnitTest.c SPMiniMax.h SPFIARGame.h SPMiniMaxNode.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNodeUnitTest.o: SPMiniMaxNodeUnitTest.c SPMiniMaxNode.h unit_test_util.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSArrayList.o: SPCHESSArrayList.h SPCHESSArrayList.c
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARGame.o: SPFIARGame.c SPFIARGame.h SPArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParser.o: SPCHESSParser.c SPCHESSParser.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c 
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMainAux.o: SPMainAux.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
main.o: main.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
