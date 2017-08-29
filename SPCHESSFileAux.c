/*
 * SPCHESSFileAux.c
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */
#include "SPCHESSFileAux.h"

SPCHESSGame* getStateFromFile(char* path) {
	printf("0");
	int i = 0, j = 0;
	char nextChar;
	char nextTag[13];
	char nextValue[100], userColor, compColor, nextTurn;
	int gameMode, difficulty;
	int subArray[DIM];
	char board[BOARD_SIZE][BOARD_SIZE];
	int piecesArrayPlayerW[NUM_OF_PIECES][DIM],
			piecesArrayPlayerB[NUM_OF_PIECES][DIM];
	FILE* in = fopen(path, "r");
	if (!in) {
		printf("Error: File doesn’t exist or cannot be opened\n");
		exit(0);
	}
	printf("1");
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
	printf("2");
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
	fclose(in);

	//fill the pieces array accordingly
	//initialize arrays to -17
	for (i = 0; i < NUM_OF_PIECES; i++) {
		for (j = 0; j < DIM; j++) {
			piecesArrayPlayerW[i][j] = -17;
			piecesArrayPlayerB[i][j] = -17;
		}
	}
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != EMPTY) {
				getSubArrayFromPiece(board[i][j], subArray);
				//BLACK
				if (board[i][j] >= 60 && board[i][j] <= 90) {
					for (int k = subArray[0]; k < subArray[1]; k++) {
						if (piecesArrayPlayerB[k][0] == -17) {
							piecesArrayPlayerB[k][0] = i;
							piecesArrayPlayerB[k][1] = j;
						}
					}
				} else { //WHITE
					for (int k = subArray[0]; k < subArray[1]; k++) {
						if (piecesArrayPlayerW[k][0] == -17) {
							piecesArrayPlayerW[k][0] = i;
							piecesArrayPlayerW[k][1] = j;
						}
					}
				}
			}
		}
	}
	//build board
	SPCHESSGame* newGame = spChessGameCreate(HISTORY_SIZE, gameMode, userColor,
			difficulty);
	//copy game board
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			newGame->gameBoard[i][j] = board[i][j];
	}
	newGame->currentPlayer = nextTurn;
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
		fputs("0</current_turn>\n\t", out);
	else {
		fputs("1</current_turn>\n\t<game_mode>", out);
	}
	if (game->gameMode == 2)
		fputs("2</game_mode>\n\t", out);
	else {
		fputs("1</game_mode>\n\t<difficulty>", out);
		fprintf(out, "%d", game->difficulty);
		fputs("</difficulty>\n\t<user_color>", out);
		if (game->colorUser == 'W') {
			fputs("1</user_color>\n\t<board>",out);
		} else {
			fputs("2</user_color>\n\t<board>",out);
		}
	}
	for (int j = 7; j >= 0; j--) {
		fprintf(out, "\n\t\t<row_%d>", j + 1);
		for (int i = 0; i < 8; i++) {
			if (game->gameBoard[i][j] == EMPTY)
				fputs("_", out);
			else
				fputc(game->gameBoard[i][j], out);
		}
		fprintf(out, "</row_%d>", j + 1);
	}
	fprintf(out, "\n\t</board>\n</game>\n");
	fclose(out);
	return 0;
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

