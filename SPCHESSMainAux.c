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
		return;
	}
	if (act.cmd == SPCHESS_DEFAULT) {
		setDefaultSetting(src);
		settingState(src);
	}
	if(act.cmd == SPCHESS_PRINT_SETTING) {
		printCurrentSetting(src);
		settingState(src);
	}
	if(act.cmd == SPCHESS_QUIT) {
		quitGame(src);
	}
	if(act.cmd == SPCHESS_START)
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

void setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act) {
	if (act->validStrArg) {
		//try to open the path, if yes - change the game, according o/w do nothing
		FILE* in = fopen(act.str, "r");
		if (!in) {
			printf("Error: File doesn’t exist or cannot be opened\n");
			free(in);
			return;
		}
		free(in);
		SPCHESSGame* loaded = getStateFromFile(act.str);
		// clear src (?)
		src = spChessGameCopy(loaded);
		spChessGameDestroy(loaded);
	} else
		printf("Error: invalid command\n");
}

void printCurrentSetting(SPCHESSGame* src) {
	if(!src)
		return;

	printf("SETTINGS:\nGAME_MODE: %d\n", src->gameMode);
	if(src->gameMode == 2)
		printf("DIFFICULTY_LVL: %d\nUSER_CLR: %d\n", src->difficulty, src->colorUser);
}

void quitGame(SPCHESSGame* src) {
	printf("Exiting...\n");
	spChessGameDestroy(src);
	exit(0);
}



