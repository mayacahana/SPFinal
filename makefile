#compiler and flags
CC = gcc
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags\
-lSDL2 -lSDL2main
VPATH = graphics
EXEC = chessprog

#objects for exec
CONSOLE_OBJS = SPCHESSMiniMaxNode.o SPCHESSMiniMax.o SPCHESSGame.o SPCHESSArrayList.o SPCHESSParser.o SPCHESSFileAux.o SPCHESSMainAux.o consolemode.o
GUI_OBJS = SPCHESSGUIButton.o SPCHESSGUICommon.o SPCHESSGUIMainWin.o SPCHESSGUILoadWin.o SPCHESSGUISetWin.o SPCHESSGameWin.o SPCHESSGUIManager.o guimode.o
ALL_OBJS = $(CONSOLE_OBJS) $(GUI_OBJS) main.o

#objects for tests
GAME_TEST_OBJS = SPCHESSArrayList.o SPCHESSGame.o SPCHESSGameUnitTest.o
ARRAY_LIST_TEST_OBJS = SPCHESSArrayListUnitTest.o SPCHESSArrayList.o
PARSER_TEST_OBJS = SPCHESSParser.o SPCHESSParserUnitTest.o
MINMAXNode_TEST_OBJ = SPCHESSMiniMaxNode.o SPCHESSMiniMaxNodeUnitTest.o SPCHESSGame.o SPCHESSArrayList.o
FILEAUX_TEST_OBJ = SPCHESSFileAux.o SPCHESSFileAuxUnitTest.o SPCHESSGame.o SPCHESSArrayList.o
MINMAX_TEST_OBJ = SPMiniMaxNode.o SPMiniMax.o SPMiniMaxUnitTest.o SPCHESSGame.o SPArrayList.o
MAINAUX_TEST_OBJS = SPMainAux.o SPArrayList.o SPCHESSGame.o SPMiniMax.o SPMiniMaxNode.o
UNIT_TESTS = SPCHESSParserUnitTest SPCHESSArrayListUnitTest SPCHESSGameUnitTest SPCHESSMiniMaxUnitTest\
SPMiniMaxNodeUnitTest SPCHESSFileAuxUnitTest SPMainAuxUnitTest

#The exec file
$(EXEC): $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o $@

#testers rules	
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
SPCHESSFileAuxUnitTest: $(FILEAUX_TEST_OBJ)
	$(CC) $(FILEAUX_TEST_OBJ) -o $@	
SPMainAuxUnitTest: $(MAINAUX_TEST_OBJS)
	$(CC) $(MAINAUX_TEST_OBJS) -o $@
SPCHESSGameUnitTest.o: SPCHESSGameUnitTest.c unit_test_util.h SPCHESSArrayList.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPArrayListUnitTest.o: SPArrayListUnitTest.c SPArrayList.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParserUnitTest.o: SPCHESSParserUnitTest.c SPCHESSParser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxUnitTest.o: SPCHESSMiniMaxUnitTest.c SPCHESSMiniMax.h SPCHESSGame.h SPCHESSMiniMaxNode.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSMiniMaxNodeUnitTest.o: SPCHESSMiniMaxNodeUnitTest.c SPCHESSMiniMaxNode.h unit_test_util.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSFileAuxUnitTest.o: SPCHESSFileAuxUnitTest.c SPCHESSFileAux.h unit_test_util.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c

#console rules
SPCHESSArrayList.o: SPCHESSArrayList.h SPCHESSArrayList.c
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSGame.o: SPCHESSGame.c SPCHESSGame.h SPCHESSArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSFileAux.o: SPCHESSFileAux.c SPCHESSGame.h SPCHESSArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSParser.o: SPCHESSParser.c SPCHESSParser.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSMiniMaxNode.o: SPCHESSMiniMaxNode.c SPCHESSMiniMaxNode.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c 
SPCHESSMiniMax.o: SPCHESSMiniMax.c SPCHESSMiniMax.h SPCHESSMiniMaxNode.h SPCHESSGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPCHESSMainAux.o: SPCHESSMainAux.c SPCHESSMainAux.h SPCHESSGame.h SPCHESSMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
consolemode.o: consolemode.c SPCHESSMainAux.h SPCHESSGame.h SPCHESSMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
	
#gui rules
graphics/SPCHESSGUIButton.o: SPCHESSGUIButton.c SPCHESSGUIButton.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUICommon.o: SPCHESSGUICommon.c SPCHESSGUICommon.h SPCHESSGUIButton.h SPCHESSMainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUIMainWin.o: SPCHESSGUIMainWin.c SPCHESSGUIMainWin.h SPCHESSGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUILoadWin.o: SPCHESSGUILoadWin.c SPCHESSGUILoadWin.h SPCHESSGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUISetWin.o: SPCHESSGUISetWin.c SPCHESSGUISetWin.h SPCHESSGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUIGameWin.o: SPCHESSGUIGameWin.c SPCHESSGUIGameWin.h SPCHESSGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPCHESSGUIManager.o: SPCHESSGUIManager.c SPCHESSGUIManager.h SPCHESSGUILoadWin.h SPCHESSGUILoadWin.h SPCHESSGUISetWin.h SPCHESSGUIGameWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/guimode.o: guimode.c SPCHESSGUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
	
#main rule
main.o: main.c SPCHESSGUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
	
#clean rule	
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
