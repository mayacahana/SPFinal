/*
 * SPCHESSMainAux.c
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */
#include "SPCHESSMainAux.h"

void setDefaultSetting(SPCHESSGame* src) {
	//init default values
	src->gameMode = DEFAULT_GAME_MODE;
	src->difficulty = DEFAULT_DIFFICULTY;
	src->colorUser = DEFAULT_USER_COLOR;
}

void settingState(SPCHESSGame* src) {

	char input[SPCHESS_MAX_LINE_LENGTH];
	if (!fgets(input, SP_MAX_LINE_LENGTH, stdin)) {
		printf("Error: settingState has failed\n");
		exit(1);
	}
	SPCHESS_GAME_SETTINGS_Command act;
	act = spParserPraseSettingLine(input);

	//switch case setting command
	if (act.cmd == SPCHESS_INVALID_LINE) {
		printf("Error: invalid command\n");
		settingState(src);
	}
	if (act.cmd == SPCHESS_GAME_MODE) {
		setGameMode(src, act);
		settingState(src);
	}
	if (act.cmd == SPCHESS_DIFFICULTY) {
		setDifficulty(src, act);
		settingState(src);
	}
	if (act.cmd == SPCHESS_USER_COLOR) {
		setUserColor(src, act);
		settingState(src);
	}
	if (act.cmd == SPCHESS_LOAD) {
		if (setLoad(src, act) == SUCCESS)
			return;
		else
			//setLoad(src, act) == FAIL
			settingState(src);
	}
	if (act.cmd == SPCHESS_DEFAULT) {
		setDefaultSetting(src);
		settingState(src);
	}
	if (act.cmd == SPCHESS_PRINT_SETTING) {
		printCurrentSetting(src);
		settingState(src);
	}
	if (act.cmd == SPCHESS_QUIT) {
		quitGame(src);
	}
	if (act.cmd == SPCHESS_START)
		return;
}

void setGameMode(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (act.validIntArg) {
		if ((act.arg == 1 || act.arg == 2)) {
			src->gameMode = act.arg;
			switch (act.arg) {
			case 1:
				printf("Game mode is set to 1 player\n");
				break;
			case 2:
				printf("Game mode is set to 2 players\n");
				break;
			}
		} else
			printf("Wrong game mode\n");
	} else
		printf("Error: invalid command\n");
}

void setDifficulty(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (src->gameMode != 1)
		printf("Error: invalid command\n");
	if (act.validIntArg) {
		if (act.arg >= 1 && act.arg <= 4)
			src->difficulty = act.arg;
		else if (act.arg == 5)
			printf(
					"Expert level not supported, please choose a value between 1 to 4:\n");
		else
			printf(
					"Wrong difficulty level. The value should be between 1 to 5\n");
	} else
		printf("Error: invalid command");
}

void setUserColor(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (src->gameMode != 1)
		printf("Error: invalid command\n");

	if (act.validIntArg && (act.arg == 0 && act.arg == 1))
		src->gameMode = act.arg;
	else
		printf("Error: invalid command");

}

int setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (act->validStrArg) {
		//try to open the path, if yes - change the game, according o/w do nothing
		FILE* in = fopen(act.str, "r");
		if (!in) {
			printf("Error: File doesn’t exist or cannot be opened\n");
			free(in);
			return FAIL;
		}
		free(in);
		SPCHESSGame* loaded = getStateFromFile(act.str);
		// clear src (?)
		src = spChessGameCopy(loaded);
		spChessGameDestroy(loaded);
		return SUCCESS;
	} else {
		printf("Error: invalid command\n");
		return FAIL;
	}
}
void printCurrentSetting(SPCHESSGame* src) {
	if (!src)
		return;

	printf("SETTINGS:\nGAME_MODE: %d\n", src->gameMode);
	if (src->gameMode == 2)
		printf("DIFFICULTY_LVL: %d\nUSER_CLR: %d\n", src->difficulty,
				src->colorUser);
}

void quitGame(SPCHESSGame* src) {
	printf("Exiting...\n");
	spChessGameDestroy(src);
	exit(0);
}

void userTurn(SPCHESSGame* src) {
	spChessGamePrintBoard(src);
	checkGameStatusForUser(src);
	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
		printf("white player - enter your move:\n");
	else
		//src->currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		printf("black player - enter your move:\n");

	char input[SPCHESS_MAX_LINE_LENGTH];
	if (!fgets(input, SP_MAX_LINE_LENGTH, stdin)) {
		printf("Error: userTurn has failed\n");
		exit(1);
	}
	SPCHESS_GAME_MODE_Command act;
	act = spParserPraseGameModeLine(input);

	//switch case game command
	if (act.cmd == SPCHESS_INVALID_LINE) {
		printf("Error: invalid command\n");
		userTurn(src);
	}
	if (act.cmd == SPCHESS_MOVE) {
		if (setUserMove(src, act) == SUCCESS)
			return;
		else
			//setUserMove(src, act) == FAIL
			userTurn(src);
	}
	if (act.cmd == SPCHESS_SAVE) {
		if (saveGame(src, act) == SUCCESS)
			return;
		else
			//saveGame(src, act) == FAIL
			userTurn(src);
	}
	if (act.cmd == SPCHESS_UNDO) {
		if (undoMove(src) == SUCCESS)
			return;
		else
			//undoMove(src, act) == FAIL
			userTurn(src);
	}
	if (act.cmd == SPCHESS_RESET)
		resetGame(src);
	if (act.cmd == SPCHESS_QUIT)
		quitGame(src);
}

int setUserMove(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act) {
	if (act.validTwoStr) {
		int row_from = act.strOne[1] - 1; //the user enters row as 1-index base
		int col_from = (int) (act.strOne[3] - 'A'); //the user enters col as an uppercase letter
		int row_to = act.strTwo[1] - 1;
		int col_to = (int) (act.strTwo[3] - 'A');

		int from[DIM] = { row_from, col_from };
		int to[DIM] = { row_to, col_to };

		SPCHESS_GAME_MESSAGE msg = spChessGameSetMove(src, from, to);
		if (msg == SPCHESS_GAME_INVALID_ARGUMENT) {
			printf("Invalid position on the board\n");
			return FAIL;
		}
		if (msg == SPCHESS_GAME_INVALID_COLOR) {
			printf("The specified position does not contain your piece\n");
			return FAIL;
		}
		if (msg == SPCHESS_GAME_INVALID_MOVE) {
			printf("Illegal move\n");
			return FAIL;
		}
		return SUCCESS;
	} else {
		printf("Error: invalid command\n");
		return FAIL;
	}
}

void checkGameStatusForUser(SPCHESSGame* src) {
	char winner = spChessGameCheckWinner(src);
	if (winner != '\0') {
		if (winner == SPCHESS_GAME_PLAYER_1_SYMBOL)
			printf("Checkmate! white player wins the game\n");
		else
			//winner == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("CheckMate! black player wins the game\n");

		//the game has reached terminal state
		spChessGameDestroy(src);
		exit(0);
	}
	char whoisincheck = spChessIfMate(src);
	if (whoisincheck != '\0') {
		if (whoisincheck == SPCHESS_GAME_PLAYER_1_SYMBOL)
			printf("Check: white King is threatend!\n");
		else
			// whoisincheck == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("Check: black King is threatend!\n");

		return;
	}
	char istie = spChessGameCheckTie(src);
	if (istie == SPCHESS_GAME_TIE_SYMBOL) {
		printf("The game is tied\n");

		//the game has reached terminal state
		spChessGameDestroy(src);
		exit(0);
	}
}

int saveGame(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act) {
	if (act.validOneStr) {
		//try to open the path, if yes - save the game, according o/w do nothing
		if (saveGameToFile(act.strOne, src) == -1) {
			printf("File cannot be created or modified\n");
			return FAIL;
		}
		return SUCCESS;
	} else {
		printf("Error: invalid command\n");
		return FAIL;
	}
}

int undoMove(SPCHESSGame* src) {
	if (src->gameMode != 1) {
		printf("Undo command not available in 2 players mode\n");
		return FAIL;
	}

	SPCHESS_GAME_MESSAGE msg = spChessGameUndoPrevMoveWithPrint(src);
	if (msg == SPCHESS_GAME_INVALID_ARGUMENT
			|| msg == SPCHESS_GAME_NO_HISTORY) {
		printf("Empty history, move cannot be undone\n");
		return FAIL;
	}
	spChessGameUndoPrevMoveWithPrint(src);
	return SUCCESS;
}

void resetGame(SPCHESSGame* src) {
	printf("Restarting...\n");
	spChessGameDestroy(src);
	src = spChessGameCreate(HISTORY_SIZE, DEFAULT_GAME_MODE, DEFAULT_USER_COLOR,
	DEFAULT_DIFFICULTY);
	//new game starts
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	settingState(src);
}

void computerTurn(SPCHESSGame* src) {
	checkGameStatusForComputer(src);
	move* compMove = spChessMiniMaxSuggestMove(src, src->difficulty);
	spChessGameSetMove(src, compMove->from, compMove->to);

	printf("Computer: move %s at <%d,%c> to <%d,%c>\n",
			getNameFromPiece(compMove->piece), compMove->from[0] + 1,
			(char) (compMove->from[1] + 'A'), compMove->to[0] + 1,
			(char) (compMove->to[1] + 'A'));

	spDestroyMove(compMove);
}

void checkGameStatusForComputer(SPCHESSGame* src) {
	char winner = spChessGameCheckWinner(src);
	if (winner != '\0') {
		if (winner == SPCHESS_GAME_PLAYER_1_SYMBOL)
			printf("Checkmate! white player wins the game\n");
		else
			//winner == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("CheckMate! black player wins the game\n");

		//the game has reached terminal state
		spChessGameDestroy(src);
		exit(0);
	}
	char whoisincheck = spChessIfMate(src);
	if (whoisincheck != '\0') {
		if (whoisincheck == SPCHESS_GAME_PLAYER_1_SYMBOL)
			printf("Check!\n");
		else
			// whoisincheck == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("Check!\n");

		return;
	}
	char istie = spChessGameCheckTie(src);
	if (istie == SPCHESS_GAME_TIE_SYMBOL) {
		printf("The game ends in a tie\n");

		//the game has reached terminal state
		spChessGameDestroy(src);
		exit(0);
	}
}

char* getNameFromPiece(char piece) {
	if (piece == WHITE_P || piece == BLACK_P)
		return "pawn";
	if (piece == WHITE_B || piece == BLACK_B)
		return "bishop";
	if (piece == WHITE_R || piece == BLACK_R)
		return "rook";
	if (piece == WHITE_N || piece == BLACK_N)
		return "knight";
	if (piece == WHITE_Q || piece == BLACK_Q)
		return "queen";
	if (piece == WHITE_K || piece == BLACK_K)
		return "king";

	return '\0';

}

