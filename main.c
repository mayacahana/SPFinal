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
	if (!game) {
		printf("spChessGameCreate has failed\n");
		spChessGameDestroy(game);
		exit(1);
	}
	printf("Specify game setting to type 'start' to begin a game with the current setting:\n");
	settingState(game);
	//continue in the game, until the game has reached terminal state or 'quit' command has entered
	if (game->gameMode == 2) { //two players mode
		while (true) { //continue in the game, until the game has reached terminal state or 'quit' command has entered
			userTurn(game);
			userTurn(game);
		}
	} else { //game->gameMode == 1
		bool userIsWhite = (game->colorUser == 1); //white alwys starts the game
		//maybe to add turns according to current player
		if (userIsWhite) {
			while (true) {
				userTurn(game);
				computerTurn(game);
			}
		} else {  //user is black
			while(true) {
				computerTurn(game);
				userTurn(game);
			}
		}
	}
	return 0;
}

