#include "SPCHESSFileAux.h"
#include "SPCHESSParser.h"

SPCHESSGame* getStateFromFile(char* path) {
	if (!path)
		return NULL;

	char tmpLine[SPCHESS_MAX_LINE_LENGTH];
	const char delim[8] = " \t\r\n";
	char* cleanLine = NULL;
	SPCHESSGame* loaded = spChessGameCreate(HISTORY_SIZE);
	//check if the file can be opened
	FILE* in = fopen(path, "r");
	if (!in) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return NULL;
	}

	while (fgets(tmpLine, SPCHESS_MAX_LINE_LENGTH, in)) {
		cleanLine = strtok(tmpLine, delim);
		if (cleanLine != NULL)
			fillGameDataDueToLine(cleanLine, loaded);
	}
	fclose(in);
	//fill pieces array acoording to game board
	for (int i = 0; i < NUM_OF_PIECES; i++) {
		for (int j = 0; j < DIM; j++) {
			loaded->piecesPlayer1[i][j] = EATEN;
			loaded->piecesPlayer2[i][j] = EATEN;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (loaded->gameBoard[i][j] != EMPTY) {
				int subArray[DIM] = { -1, -1 };
				getSubArrayFromPiece(loaded->gameBoard[i][j], subArray);
				//BLACK PIECE
				if (isupper(loaded->gameBoard[i][j])) {
					for (int k = subArray[1]; k >= subArray[0]; k--) {
						if (loaded->piecesPlayer2[k][0] == EATEN
								&& loaded->piecesPlayer2[k][1] == EATEN) {
							loaded->piecesPlayer2[k][0] = i;
							loaded->piecesPlayer2[k][1] = j;
							break;
						}
					}
				} else { //WHITE PIECE
					for (int k = subArray[1]; k >= subArray[0]; k--) {
						if (loaded->piecesPlayer1[k][0] == EATEN
								&& loaded->piecesPlayer1[k][1] == EATEN) {
							loaded->piecesPlayer1[k][0] = i;
							loaded->piecesPlayer1[k][1] = j;
							break;
						}
					}
				}
			}
		}
	}

	return loaded;
}

void fillGameDataDueToLine(char* cleanLine, SPCHESSGame* src) {
	const char delimTag[3] = "<>";
	char* tmpLine = NULL;
	char* data = NULL;
	int dataInt = 0;

	tmpLine = strtok(cleanLine, delimTag);

	//switch case according to the tag content:

	//current turn
	if (strstr(tmpLine, "current_turn") != NULL) {
		data = strtok(NULL, delimTag);
		dataInt = data[0] - '0';
		if (dataInt == 0)
			src->currentPlayer = SPCHESS_GAME_PLAYER_2_SYMBOL;
		else
			src->currentPlayer = SPCHESS_GAME_PLAYER_1_SYMBOL;
	}

	//game mode
	if (strstr(tmpLine, "game_mode") != NULL) {
		data = strtok(NULL, delimTag);
		dataInt = data[0] - '0';
		if (dataInt == 1)
			src->gameMode = 1;
		else
			src->gameMode = 2;
	}

	//difficulty
	if (strstr(tmpLine, "difficulty") != NULL) {
		data = strtok(NULL, delimTag);
		//no difficulty in case of game mode 2
		if (data[0] == '/')
			src->difficulty = DEFAULT_DIFFICULTY;
		else {
			dataInt = data[0] - '0';
			src->difficulty = dataInt;
		}
	}

	//user_color
	if (strstr(tmpLine, "user_color") != NULL) {
		data = strtok(NULL, delimTag);
		//no difficulty in case of game mode 2
		if (data[0] == '/')
			src->colorUser = DEFAULT_USER_COLOR;
		else {
			dataInt = data[0] - '0';
			if (dataInt == 0)
				src->colorUser = 0;
			else
				src->colorUser = 1;
		}
	}

	//row of board
	if (strstr(tmpLine, "row") != NULL) {
		dataInt = (tmpLine[strlen(tmpLine) - 1] - '0') - 1; //row number (0-base)
		data = strtok(NULL, delimTag);
		for (int i = 0; i < BOARD_SIZE; i++)
			src->gameBoard[dataInt][i] = data[i];
		return;
	}
}

int saveGameToFile(char* path, SPCHESSGame* game) {
	FILE* out;
	out = fopen(path, "w");
	if (!out)
		return -1;
	fprintf(out,
			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<game>\n\t<current_turn>");
	if (game->currentPlayer == SPCHESS_GAME_PLAYER_1_SYMBOL)
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
		if (game->colorUser == 1)
			fputs("1</user_color>\n\t<board>", out);
		else
			fputs("0</user_color>\n\t<board>", out);
	}
	for (int i = BOARD_SIZE - 1; i >= 0; i--) {
		fprintf(out, "\n\t\t<row_%d>", i + 1);
		for (int j = 0; j < BOARD_SIZE; j++) {
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
