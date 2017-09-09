/*
 * SPCHESSFileAux.c
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */
#include "SPCHESSFileAux.h"

SPCHESSGame* getStateFromFile(char* path) {
	int i = 0, j = 0;
	char nextChar;
	char nextTag[13];
	char nextValue[100], nextTurn;
	int gameMode, difficulty = 2, userColor = 1;
	char board[BOARD_SIZE][BOARD_SIZE];
	int piecesArrayPlayerW[NUM_OF_PIECES][DIM],
			piecesArrayPlayerB[NUM_OF_PIECES][DIM];
	FILE* in = fopen(path, "r");

	if (!in) {
		printf("Error: File doesn’t exist or cannot be opened\n");
		return NULL;
	}

	while (i < 47) {
		nextChar = fgetc(in);
		i++;
	}
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "current_turn") == 0) {
		if (strcmp(nextValue, "0") == 0)
			nextTurn = SPCHESS_GAME_PLAYER_2_SYMBOL;
		else
			nextTurn = SPCHESS_GAME_PLAYER_1_SYMBOL;
	}
	getNextTag(in, nextTag);
	nextChar = fgetc(in);
	nextChar = fgetc(in);

	//next tag - game_mode
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "game_mode") == 0) {
		if (strcmp(nextValue, "1") == 0)
			gameMode = 1;
		else
			gameMode = 2;
	}
	getNextTag(in, nextTag);
	nextChar = fgetc(in);
	nextChar = fgetc(in);

	//next tag - difficulty
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);

	if (strcmp(nextTag, "difficulty") == 0) {
		if (strcmp(nextValue, "5") == 0) {
			printf("Expert level not supported\n");
			return NULL;
		}
		difficulty = (int) (nextValue[0] - '0');
		getNextTag(in, nextTag);
		nextChar = fgetc(in);
		nextChar = fgetc(in);
		//next tag - user_color
		getNextTag(in, nextTag);
		getNextValue(in, nextValue);

		if (strcmp(nextTag, "user_color") == 0) {

			if (strcmp(nextValue, "0") == 0) {
				userColor = 0;
			} else {
				userColor = 1;
			}
		}
		getNextTag(in, nextTag);
		nextChar = fgetc(in);
		nextChar = fgetc(in);
		//next tag - board
		getNextTag(in, nextTag);
		getNextValue(in, nextValue);
	}
	if (strcmp(nextTag, "board") == 0) {
		for (int i = BOARD_SIZE - 1; i >= 0; i--) {
			nextChar = fgetc(in);
			while (nextChar != '>') //moving on <row_i>
				nextChar = fgetc(in);
			for (j = 0; j < BOARD_SIZE; j++) {
				nextChar = fgetc(in);
				board[i][j] = nextChar;
			}
			nextChar = fgetc(in);
			while (nextChar != '>') //moving on </row_i>
				nextChar = fgetc(in);
		}
	}
	fclose(in);

	//fill the pieces array accordingly
	//initialize arrays to -17
	for (i = 0; i < NUM_OF_PIECES; i++) {
		for (j = 0; j < DIM; j++) {
			piecesArrayPlayerW[i][j] = EATEN;
			piecesArrayPlayerB[i][j] = EATEN;
		}
	}
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != EMPTY) {
				int subArray[DIM] = {-1, -1};
				getSubArrayFromPiece(board[i][j], subArray);
				//BLACK
				if (isupper(board[i][j])) {
					for (int k = subArray[0]; k <= subArray[1]; k++) {
						if (piecesArrayPlayerB[k][0] == EATEN && piecesArrayPlayerB[k][1] == EATEN) {
							piecesArrayPlayerB[k][0] = i;
							piecesArrayPlayerB[k][1] = j;
							break;
						}
					}
				} else { //WHITE
					for (int k = subArray[0]; k <= subArray[1]; k++) {
						if (piecesArrayPlayerW[k][0] == EATEN && piecesArrayPlayerB[k][1] == EATEN) {
							piecesArrayPlayerW[k][0] = i;
							piecesArrayPlayerW[k][1] = j;
							break;
						}
					}
				}
			}
		}
	}
	//create new game
	SPCHESSGame* newGame = spChessGameCreate(HISTORY_SIZE);

	newGame->gameMode = gameMode;
	newGame->colorUser = userColor;
	newGame->difficulty = difficulty;
	newGame->currentPlayer = nextTurn;
	//copy game board
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			newGame->gameBoard[i][j] = board[i][j];
	}
	//copy pieces array
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		for (int j = 0; j < DIM; j++) {
			newGame->piecesPlayer1[i][j] = piecesArrayPlayerW[i][j];
			newGame->piecesPlayer2[i][j] = piecesArrayPlayerB[i][j];
		}
	}
	return newGame;
}

int saveGameToFile(char* path, SPCHESSGame* game) {
	FILE* out;
	out = fopen(path, "w");
	if (!out)
		return -1;
	fprintf(out,
			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<game>\n\t<current_turn>");
	if (game->currentPlayer == 'W')
		fputs("1</current_turn>\n\t<game_mode>", out);
	else {
		fputs("0</current_turn>\n\t<game_mode>", out);
	}
	if (game->gameMode == 2)
		fputs("2</game_mode>\n\t<board>", out);
	else {
		fputs("1</game_mode>\n\t<difficulty>", out);
		fprintf(out, "%d", game->difficulty);
		fputs("</difficulty>\n\t<user_color>", out);
		if (game->colorUser == 1) {
			fputs("1</user_color>\n\t<board>", out);
		} else {
			fputs("0</user_color>\n\t<board>", out);
		}
	}
	for (int i = 7; i >= 0; i--) {
		fprintf(out, "\n\t\t<row_%d>", i + 1);
		for (int j = 0; j < 8; j++) {
			if (game->gameBoard[i][j] == EMPTY)
				fputs("_", out);
			else
				fputc(game->gameBoard[i][j], out);
		}
		fprintf(out, "</row_%d>", i + 1);
	}
	fprintf(out, "\n\t</board>\n</game>\n");
	fclose(out);
	return 0;
}

void getNextTag(FILE* in, char nextTag[13]) {
	int i = 0;
	char nextChar = fgetc(in);
	nextChar = fgetc(in);
	while (nextChar != '>') {
		nextTag[i] = nextChar;
		i++;
		nextChar = fgetc(in);
	}
	nextTag[i] = '\0';
}
void getNextValue(FILE* in, char nextValue[6]) {
	int i = 0;
	char nextChar = fgetc(in);
	while (nextChar != '<') {
		nextValue[i] = nextChar;
		i++;
		nextChar = fgetc(in);
	}
	nextValue[i] = '\0';
}

