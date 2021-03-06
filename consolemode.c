#include "consolemode.h"

int activeconsole() {
	SP_BUFF_SET();
	SPCHESSGame* game = spChessGameCreate(HISTORY_SIZE);
	bool userIsWhite;
	if (!game) {
		printf("spChessGameCreate has failed\n");
		spChessGameDestroy(game);
		exit(1);
	}
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
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
				if (game->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL) {
					spChessGamePrintBoard(game);
					printTurn(game);
					if (userTurn(game) == SPCHESS_RESET)
						continue;
				} else
					computerTurn(game);
			} else { // user is black player
				if (game->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
					computerTurn(game);
				else {
					spChessGamePrintBoard(game);
					printTurn(game);
					if (userTurn(game) == SPCHESS_RESET)
						continue;
				}
			}
		}
	}
	return 0;
}
