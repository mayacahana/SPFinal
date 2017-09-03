/*
 * SPCHESSParser.c
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#include "SPCHESSParser.h"

bool spParserIsInt(const char* str) {

	if (*str == '-') // handle negative number
		++str;
	if (!*str) // handle empty string
		return false;

	while (*str) {
		if (!isdigit(*str)) // the i-th char is not a valid digit
			return false;
		else
			++str;
	}
	return true;
}

SPCHESS_GAME_SETTINGS_Command spParserPraseSettingLine(const char* str) {

	char *strcopy = (char*) malloc((strlen(str) + 1) * sizeof(char));
	if (!strcopy) {
		perror_message_malloc;
		free(strcopy);
		exit(1);
	}
	strcpy(strcopy, str); //copy the string

	SPCHESS_GAME_SETTINGS_Command res;
	res.cmd = SPCHESS_INVALID_LINE;
	res.validIntArg = false;
	res.validStrArg = false;
	bool seen_cmd = false, seen_cmd_with_int_arg = false,
			seen_cmd_with_string_arg = false;
	int arg = 0, val = 0;
	char *word = strtok(strcopy, " \t\r\n");

	if (!word) {
		//printf("Error: standard function strtok has failed\n");
		free(strcopy);
		return res;
	}

	//spliting the string
	while (word != NULL) {
		if (strcmp(word, "") != 0) { //not an empty word
			if (seen_cmd == false) {
				seen_cmd = true;
				arg = spParserSettingCommand(word);
				if (arg == SPCHESS_INVALID_LINE) { // invalid line
					break;
				} else if (arg == SPCHESS_GAME_MODE || arg == SPCHESS_DIFFICULTY
						|| arg == SPCHESS_USER_COLOR)
					seen_cmd_with_int_arg = true;
				else if (arg == SPCHESS_LOAD)
					seen_cmd_with_string_arg = true;

				res.cmd = arg;
				res.validIntArg = false;
				res.validStrArg = false;
			} else if (seen_cmd_with_int_arg && spParserIsInt(word)) { //game mode, difficulty, user color command
				val = atoi(word);
				res.validIntArg = true;
				res.arg = val;
				seen_cmd_with_int_arg = false;
			} else if (seen_cmd_with_string_arg) { //load command
				res.str = (char *) malloc((strlen(word) + 1) * sizeof(char));
				res.validStrArg = true;
				strcpy(res.str, word);
				seen_cmd_with_string_arg = false;
			} else { //the user add other words beside command, thus invalid command
				res.cmd = SPCHESS_INVALID_LINE; //maybe remove
				res.validIntArg = false;
				res.validStrArg = false;
				break;
			}

		}
		word = strtok(NULL, " \t\r\n");
	}

	free(strcopy);
	return res;
}

int spParserSettingCommand(char* str) {

	//create a copy
	char *strcopy = (char*) malloc((strlen(str) + 1) * sizeof(char));
	if (!strcopy) {
		perror_message_malloc;
		free(strcopy);
		exit(1);
	}
	strcpy(strcopy, str);

	//switch case command
	if (strcmp(strcopy, "game_mode") == 0) {
		free(strcopy);
		return SPCHESS_GAME_MODE;
	}
	if (strcmp(strcopy, "difficulty") == 0) {
		free(strcopy);
		return SPCHESS_DIFFICULTY;
	}
	if (strcmp(strcopy, "user_color") == 0) {
		free(strcopy);
		return SPCHESS_USER_COLOR;
	}
	if (strcmp(strcopy, "load") == 0) {
		free(strcopy);
		return SPCHESS_LOAD;
	}
	if (strcmp(strcopy, "default") == 0) {
		free(strcopy);
		return SPCHESS_DEFAULT;
	}
	if (strcmp(strcopy, "print_setting") == 0) {
		free(strcopy);
		return SPCHESS_PRINT_SETTING;
	}
	if (strcmp(strcopy, "quit") == 0) {
		free(strcopy);
		return SPCHESS_QUIT;
	}
	if (strcmp(strcopy, "start") == 0) {
		free(strcopy);
		return SPCHESS_START;
	}
	free(strcopy);
	return SPCHESS_INVALID_LINE;

}

SPCHESS_GAME_MODE_Command spParserPraseGameModeLine(const char* str) {

	char *strcopy = (char*) malloc((strlen(str) + 1) * sizeof(char));
	if (!strcopy) {
		perror_message_malloc;
		free(strcopy);
		exit(1);
	}
	strcpy(strcopy, str); //copy the string

	SPCHESS_GAME_MODE_Command res;
	res.cmd = SPCHESS_INVALID_LINE;
	res.validOneStr = false;
	res.validTwoStr = false;
	bool seen_cmd = false, seen_cmd_with_one_str_save = false,
			seen_cmd_with_one_str_get_moves = false, seen_cmd_with_two_str =
					false;
	int arg = 0;
	char *word = strtok(strcopy, " \t\r\n"), *pat;
	if (!word) {
		//print_message("Error: standard function strtok has failed\n");
		free(strcopy);
		return res;
	}

	//spliting the string
	while (word != NULL) {
		if (strcmp(word, "") != 0) { //not an empty word
			if (seen_cmd == false) {
				seen_cmd = true;
				arg = spParserGameModeCommand(word);
				if (arg == SPCHESS_INVALID_LINE) { // invalid line
					break;
				} else if (arg == SPCHESS_GET_MOVES)
					seen_cmd_with_one_str_get_moves = true;
				else if (arg == SPCHESS_SAVE)
					seen_cmd_with_one_str_save = true;
				else if (arg == SPCHESS_MOVE)
					seen_cmd_with_two_str = true;

				res.cmd = arg;
				res.validOneStr = false;
				res.validTwoStr = false;
			} else if (seen_cmd_with_two_str && checkPosPat(word))  { //move commmand

				pat = strtok(NULL, " \t\r\n");
				if(!pat || strcmp(pat, "to") != 0)
					break;
				pat = strtok(NULL, " \t\r\n");
				if(!pat)
					break;
				if (checkPosPat(pat)) { // check if <i,j>
					res.validTwoStr = true;
					res.strOne = (char *) malloc(
							(strlen(word) + 1) * sizeof(char));
					strcpy(res.strOne, word);
					res.strTwo = (char *) malloc(
							(strlen(pat) + 1) * sizeof(char));
					strcpy(res.strTwo, pat);
				}
				seen_cmd_with_two_str = false;
			} else if (seen_cmd_with_one_str_get_moves && checkPosPat(word)) { //get moves command
				res.strOne = (char *) malloc((strlen(word) + 1) * sizeof(char));
				strcpy(res.strOne, word);
				res.validOneStr = true;
				seen_cmd_with_one_str_get_moves = false;
			} else if (seen_cmd_with_one_str_save) { // save command
				res.strOne = (char *) malloc((strlen(word) + 1) * sizeof(char));
				strcpy(res.strOne, word);
				res.validOneStr = true;
				seen_cmd_with_one_str_save = false;
			} else { //the user add other words beside command, thus invalid command
				res.cmd = SPCHESS_INVALID_LINE; //maybe remove
				res.validOneStr = false;
				res.validTwoStr = false;
				break;
			}
		}
		word = strtok(NULL, " \t\r\n");
	}
	free(strcopy);
	return res;

}

int spParserGameModeCommand(char* str) {
	//create a copy
	char *strcopy = (char*) malloc((strlen(str) + 1) * sizeof(char));
	if (!strcopy) {
		perror_message_malloc;
		free(strcopy);
		exit(1);
	}
	strcpy(strcopy, str);

	//switch case command
	if (strcmp(strcopy, "move") == 0) {
		free(strcopy);
		return SPCHESS_MOVE;
	}
	if (strcmp(strcopy, "get_moves") == 0) {
		free(strcopy);
		return SPCHESS_GET_MOVES;
	}
	if (strcmp(strcopy, "save") == 0) {
		free(strcopy);
		return SPCHESS_SAVE;
	}
	if (strcmp(strcopy, "undo") == 0) {
		free(strcopy);
		return SPCHESS_UNDO;
	}
	if (strcmp(strcopy, "reset") == 0) {
		free(strcopy);
		return SPCHESS_RESET;
	}
	if (strcmp(strcopy, "quit") == 0) {
		free(strcopy);
		return SPCHESS_QUIT;
	}

	free(strcopy);
	return SPCHESS_INVALID_LINE;
}

bool checkPosPat(char *str) {

	if (strlen(str) >= 5 && str[0] == '<' && isdigit(str[1]) && str[2] == ','
			&& isupper(str[3]) && str[4] == '>')
		return true;

	return false;

}

