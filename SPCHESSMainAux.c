/*
 * SPCHESSMainAux.c
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */
#include "SPCHESSMainAux.h"

SPCHESSGame* settingState() {
	//default values of init game
	int gameMode = 1;
	int colorUser = 1;
	int difficulty = 2;
	char input[SPCHESS_MAX_LINE_LENGTH];
	SPCHESS_GAME_SETTINGS_Command act;

	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	if (!fgets(input, SP_MAX_LINE_LENGTH, stdin)) {
		printf("Error: settingState has failed\n");
		exit(1);
	}

	//while not command to exit

	act = spParserPraseSettingLine(input);
	if(act.cmd == SPCHESS_GAME_MODE) {
		if(act.validIntArg && (act.arg == 1 || act.arg == 2)) {
			switch(act.arg) {
			case 1:
				printf("Game mode is set to 1 player\n");
				break;
			case 2:
				printf("Game mode is set to 2 players\n");
			}
		} else
			printf("Worng game mode\n");
	}




}

