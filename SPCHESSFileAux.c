/*
 * SPCHESSFileAux.c
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */
#include "SPCHESSFileAux.h"

SPCHESSGame* getStateFromFile(char* path) {
	int i = 0;
	char nextChar;
	char nextTag[13];
	char nextValue[6], userColor, compColor, nextTurn;
	int gameMode, difficulty;
	char board[BOARD_SIZE][BOARD_SIZE];
	FILE* in = fopen(path, "r");
	if (!in) {
		printf("Error: File doesn’t exist or cannot be opened\n");
		exit(0);
	}
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "current_turn") == 0) {
		if (strcmp(nextValue, "black") == 0) {
			nextTurn = SPCHESS_GAME_PLAYER_2_SYMBOL;
		} else {
			nextTurn = SPCHESS_GAME_PLAYER_1_SYMBOL;
		}
	} else {
		//error
	}
	//next tag - game_mode
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "game_mode") == 0) {
		if (strcmp(nextValue, "1") == 0)
			gameMode = 1;
		else
			gameMode = 2;
	}
	//next tag - difficulty
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "difficulty") == 0) {
		difficulty = (int) (nextValue[0] - '0');
	}
	//next tag - user_color
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "current_turn") == 0) {
		if (strcmp(nextValue, "black") == 0) {
			userColor = SPCHESS_GAME_PLAYER_2_SYMBOL;
			compColor = SPCHESS_GAME_PLAYER_1_SYMBOL;
		} else {
			userColor = SPCHESS_GAME_PLAYER_1_SYMBOL;
			compColor = SPCHESS_GAME_PLAYER_2_SYMBOL;
		}
	}
	//next tag - board
	getNextTag(in, nextTag);
	getNextValue(in, nextValue);
	if (strcmp(nextTag, "board") == 0) {
		//rows
		for (int j = 7; j >= 0; j--) {
			nextChar = fgetc(in);
			while (nextChar != '>') //moving on <row_i>
				nextChar = fgetc(in);
			for (i = 0; i < 8; i++) {
				nextChar = fgetc(in);
				if (nextChar == '_')
					board[i][j] = EMPTY;
				else
					board[i][j] = nextChar;
			}
			nextChar = fgetc(in);
			while (nextChar != '>') //moving on </row_i>
				nextChar = fgetc(in);
		}
	}
	assert(fclose(in) == 0);
	//build board
	SPCHESSGame* newGame = spChessGameCreate(HISTORY_SIZE);
	newGame->gameboard = board;
	newGame->currentPlayer = nextTurn;
	newGame->gameMode = gameMode;
	newGame->userColor = userColor;
	newGame->compColor = compColor;
	newGame->difficulty = difficulty;
	return newGame;
}

int saveGameToFile(char* path, SPCHESSGame* game) {
	FILE* out;
	int i, j;
	out = fopen(path, "w");
	if (!out)
		return -1;
	fprintf(out,
			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<game>\n\t<current_turn>");
	if (game->currentPlayer == 'W')
		fputs("0</current_turn>\n\t",out);
	else {
		fputs("1</current_turn>\n\t<game_mode>",out);
	}
	if (game->gameMode == 2)
		fputs("2</game_mode>\n\t",out);
	else {
		fputs("1</game_mode>\n\t<difficulty>",out);
		fprintf(out,"%d",game->difficulty);
		fputs("</difficulty>\n\t<user_color>",out);
		if(game->userColor == 'W'){
			fputs("1</user_color>\n\t")
		}
	}
}

void getNextTag(FILE* in, char nextTag[13]) {
	int i = 0;
	char nextChar = fgetc(in);
	nextChar = fgetc(in);
	while (nextChar != '<') { /* reading the closing tag */
		nextChar = fgetc(in);
	}
	nextChar = fgetc(in); // last char '<'
//reading the tag
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
