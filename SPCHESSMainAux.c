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
	if (!fgets(input, SPCHESS_MAX_LINE_LENGTH, stdin)) {
		printf("Error: settingState has NOSUCCESSed\n");
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
		setLoad(src, act);
		free(act.str);
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
	if (src->gameMode != 1) {
		printf("Error: invalid command\n");
		return;
	}
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
	if (src->gameMode != 1) {
		printf("Error: invalid command\n");
		return;
	}
	if (act.validIntArg && (act.arg == 0 || act.arg == 1))
		src->colorUser = act.arg;
	else
		printf("Error: invalid command\n");

}

int setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (act.validStrArg) {
		//try to open the path, if yes - change the game, according o/w do nothing
		FILE* in = fopen(act.str, "r");
		if (!in) {
			printf("Error: File doesn't exist or cannot be opened\n");
			free(in);
			return NOSUCCESS;
		}
		fclose(in);
		SPCHESSGame* loaded = getStateFromFile(act.str);
		spChessGameClear(src);
		spChessGameCopyInfo(src, loaded);
		spChessGameDestroy(loaded);
		return SUCCESS;
	} else {
		printf("Error: invalid command\n");
		return NOSUCCESS;
	}
}
void printCurrentSetting(SPCHESSGame* src) {
	if (!src)
		return;

	printf("SETTINGS:\nGAME_MODE: %d\n", src->gameMode);
	if (src->gameMode == 1) {
		char* tmpColorUser = NULL;
		if (src->colorUser == 0)
			tmpColorUser = "BLACK";
		else
			tmpColorUser = "WHITE";
		printf("DIFFICULTY_LVL: %d\nUSER_CLR: %s\n", src->difficulty,
				tmpColorUser);
	}

}

void quitGame(SPCHESSGame* src) {
	printf("Exiting...\n");
	spChessGameDestroy(src);
	exit(0);
}

SPCHESS_COMMAND userTurn(SPCHESSGame* src) {
	char input[SPCHESS_MAX_LINE_LENGTH];
	if (!fgets(input, SPCHESS_MAX_LINE_LENGTH, stdin)) {
		printf("Error: userTurn has failed\n");
		exit(1);
	}
	SPCHESS_GAME_MODE_Command act;
	act = spParserPraseGameModeLine(input);
	//switch case game command

	if (act.cmd == SPCHESS_INVALID_LINE) {
		printf("Error: invalid command\n");
		printTurn(src);
		return userTurn(src);
	}
	if (act.cmd == SPCHESS_MOVE) {
		if (setUserMove(src, act) == SUCCESS) {
			checkGameStatusForUser(src, act);
			free(act.strOne);
			free(act.strTwo);
			return SPCHESS_MOVE;

		} else { //setUserMove(src, act) == NOSUCCESS
			if (act.validTwoStr) {
				free(act.strOne);
				free(act.strTwo);
			}
			return userTurn(src);
		}
	}
	if (act.cmd == SPCHESS_SAVE) {
		saveGame(src, act);
		free(act.strOne);
		printTurn(src);
		return userTurn(src);
	}
	if (act.cmd == SPCHESS_UNDO) {
		if (undoMove(src) == SUCCESS) {
			spChessGamePrintBoard(src);
			printTurn(src);
		}
		return userTurn(src);
	}
	if (act.cmd == SPCHESS_RESET) {
		resetGame(src);
		return SPCHESS_RESET;
	}
	if (act.cmd == SPCHESS_QUIT)
		quitGame(src);

	return SPCHESS_SUCCESS;
}

int setUserMove(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act) {
	if (act.validTwoStr) {
		int row_from = (act.strOne[1] - '0') - 1; //the user enters row as 1-index base
		int col_from = (int) (act.strOne[3] - 'A'); //the user enters col as an uppercase letter
		int row_to = (act.strTwo[1] - '0') - 1;
		int col_to = (int) (act.strTwo[3] - 'A');

		int from[DIM] = { row_from, col_from };
		int to[DIM] = { row_to, col_to };

		if (!spChessGameIsValidMove(src, from, to)) {
			printf("Invalid position on the board\n");
			printTurn(src);
			return NOSUCCESS;
		}
		if (spChessGameIsKingRisker(src, from, to)) {
			printf("Illegal move\n");
			printTurn(src);
			return NOSUCCESS;
		}
		SPCHESS_GAME_MESSAGE msg = spChessGameSetMove(src, from, to);
		if (msg == SPCHESS_GAME_INVALID_COLOR) {
			printf("The specified position does not contain your piece\n");
			printTurn(src);
			return NOSUCCESS;
		}
		if (msg == SPCHESS_GAME_INVALID_MOVE) {
			printf("Illegal move\n");
			printTurn(src);
			return NOSUCCESS;
		}
		return SUCCESS;

	} else {
		printf("Error: invalid command\n");
		printTurn(src);
		return NOSUCCESS;
	}
}

void checkGameStatusForUser(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act) {
	char winner = spChessGameCheckWinner(src);
	if (winner != '\0') {
		if (winner == SPCHESS_GAME_PLAYER_1_SYMBOL) {
			printf("Checkmate! white player wins the game\n");
		} else {
			//winner == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("Checkmate! black player wins the game\n");
		}
		//the game has reached terminal state
		free(act.strOne);
		free(act.strTwo);
		spChessGameDestroy(src);
		exit(0);
	}
	char whoisincheck = spChessIfMate(src);
	if (whoisincheck != '\0') {
		if (whoisincheck == SPCHESS_GAME_PLAYER_1_SYMBOL)
			printf("Check: white King is threatened!\n");
		else
			// whoisincheck == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("Check: black King is threatened!\n");

		return;
	}
	char istie = spChessGameCheckTie(src);
	if (istie == SPCHESS_GAME_TIE_SYMBOL) {
		printf("The game is tied\n");

		//the game has reached terminal state
		free(act.strOne);
		free(act.strTwo);
		spChessGameDestroy(src);
		exit(0);
	}
}

int saveGame(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act) {
	if (act.validOneStr) {
		//try to open the path, if yes - save the game, according o/w do nothing
		if (saveGameToFile(act.strOne, src) == -1) {
			printf("File cannot be created or modified\n");
			return NOSUCCESS;
		}
		return SUCCESS;
	} else {
		printf("Error: invalid command\n");
		return NOSUCCESS;
	}
}

int undoMove(SPCHESSGame* src) {
	if (src->gameMode != 1) {
		printf("Undo command not available in 2 players mode\n");
		return NOSUCCESS;
	}

	SPCHESS_GAME_MESSAGE msg = spChessGameUndoPrevMoveWithPrint(src);
	if (msg == SPCHESS_GAME_INVALID_ARGUMENT
			|| msg == SPCHESS_GAME_NO_HISTORY) {
		printf("Empty history, move cannot be undone\n");
		return NOSUCCESS;
	}
	spChessGameUndoPrevMoveWithPrint(src);
	return SUCCESS;
}

void resetGame(SPCHESSGame* src) {
	printf("Restarting...\n");
	spChessGameClear(src);
	printf(
			"Specify game setting or type 'start' to begin a game with the current setting:\n");
	settingState(src);
}

void computerTurn(SPCHESSGame* src) {
	move* compMove = spChessMiniMaxSuggestMove(src, src->difficulty);
	spChessGameSetMove(src, compMove->from, compMove->to);

	printf("Computer: move %s at <%d,%c> to <%d,%c>\n",
			getNameFromPiece(compMove->piece), compMove->from[0] + 1,
			(char) (compMove->from[1] + 'A'), compMove->to[0] + 1,
			(char) (compMove->to[1] + 'A'));

	spDestroyMove(compMove);
	checkGameStatusForComputer(src);
}

void checkGameStatusForComputer(SPCHESSGame* src) {
	char winner = spChessGameCheckWinner(src);
	if (winner != '\0') {
		if (winner == SPCHESS_GAME_PLAYER_1_SYMBOL) {
			printf("Checkmate! white player wins the game\n");
		} else { //winner == SPCHESS_GAME_PLAYER_2_SYMBOL
			printf("Checkmate! black player wins the game\n");
		}
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

	return "";
}

void printTurn(SPCHESSGame* src) {
	if (!src)
		return;

	if (src->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
		printf("white player - enter your move:\n");
	else
		//src->currentPlayer == SPCHESS_GAME_PLAYER_2_SYMBOL
		printf("black player - enter your move:\n");
}

