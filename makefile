CC = gcc
OBJS = SPCHESSMiniMaxNode.o SPCHESSMiniMax.o SPCHESSGame.o SPCHESSArrayList.o SPCHESSParser.o SPCHESSMainAux.o main.o
EXEC = chessprog
GAME_TEST_OBJS = SPCHESSArrayList.o SPCHESSGame.o SPCHESSGameUnitTest.o
ARRAY_LIST_TEST_OBJS = SPCHESSArrayListUnitTest.o SPCHESSArrayList.o
PARSER_TEST_OBJS = SPCHESSParser.o SPCHESSParserUnitTest.o
MINMAXNode_TEST_OBJ = SPCHESSMiniMaxNode.o SPCHESSMiniMaxNodeUnitTest.o SPCHESSGame.o SPCHESSArrayList.o
MINMAX_TEST_OBJ = SPMiniMaxNode.o SPMiniMax.o SPMiniMaxUnitTest.o SPFIARGame.o SPArrayList.o
MAINAUX_TEST_OBJS = SPMainAux.o SPArrayList.o SPFIARGame.o SPMiniMax.o SPMiniMaxNode.o
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
UNIT_TESTS = SPCHESSParserUnitTest SPCHESSArrayListUnitTest SPCHESSGameUnitTest SPCHESSMiniMaxUnitTest\
SPMiniMaxNodeUnitTest SPMainAuxUnitTest

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
SPCHESSGameUnitTest: $(GAME_TEST_OBJS)
	$(CC) $(GAME_TEST_OBJS) -o $@
SPCHESSArrayListUnitTest: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
SPCHESSParserUnitTest: $(PARSER_TEST_OBJS)
	$(CC) $(PARSER_TEST_OBJS) -o $@
SPMiniMaxUnitTest: $(MINMAX_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPCHESSMiniMaxNodeUnitTest: $(MINMAXNode_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMainAuxUnitTest: $(MAINAUX_TEST_OBJS)
	$(CC) $(MAINAUX_TEST_OBJS) -o $@
SPCHESSGameUnitTest.o: SPCHESSGameUnitTest.c unit_test_util.h SPCHESSArrayList.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPArrayListUnitTest.o: SPArrayListUnitTest.c SPArrayList.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParserUnitTest.o: SPCHESSParserUnitTest.c SPCHESSParser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxUnitTest.o: SPMiniMaxUnitTest.c SPMiniMax.h SPFIARGame.h SPMiniMaxNode.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSMiniMaxNodeUnitTest.o: SPCHESSMiniMaxNodeUnitTest.c SPCHESSMiniMaxNode.h unit_test_util.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSArrayList.o: SPCHESSArrayList.h SPCHESSArrayList.c
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSGame.o: SPCHESSGame.c SPCHESSGame.h SPCHESSArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParser.o: SPCHESSParser.c SPCHESSParser.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSMiniMaxNode.o: SPCHESSMiniMaxNode.c SPCHESSMiniMaxNode.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c 
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMainAux.o: SPMainAux.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
main.o: main.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)