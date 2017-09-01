/*
 * main.c
 *
 *  Created on: 31 באוג׳ 2017
 *      Author: uri
 */

#include "SPCHESSMainAux.h"

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);
	SPCHESSGame* game = spChessGameCreate(HISTORY_SIZE, DEFAULT_GAME_MODE,
	DEFAULT_USER_COLOR, DEFAULT_DIFFICULTY);
	bool userIsWhite;
	if (!game) {
		printf("spChessGameCreate has failed\n");
		spChessGameDestroy(game);
		exit(1);
	}
	printf("Specify game setting to type 'start' to begin a game with the current setting:\n");
	settingState(game);
	//continue in the game, until the game has reached terminal state or 'quit' command has entered
	while (true) {
		if (game->gameMode == 2) { //two players mode
			spChessGamePrintBoard(game);
			printTurn(game);
			if (userTurn(game) == SPCHESS_RESET)
				continue;
		} else { //game->gameMode == 1
			userIsWhite = (game->colorUser == 1);
			if (userIsWhite) {
				spChessGamePrintBoard(game);
				printTurn(game);
				if (userTurn(game) == SPCHESS_RESET)
					continue;
				computerTurn(game);
			} else { // user is black player
				computerTurn(game);
				spChessGamePrintBoard(game);
				printTurn(game);
				if (userTurn(game) == SPCHESS_RESET)
					continue;
			}
		}
	}
	return 0;
}

