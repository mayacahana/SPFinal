/*
 * SPCHESSParser.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#ifndef SPCHESSPARSER_H_
#define SPCHESSPARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SP_MAX_LINE_LENGTH 1024
#define perror_message_malloc (perror("Error: standard function malloc has failed"))
#define perror_message_scanf (perror("Error: standard function scanf has failed"))
#define perror_message_printf (perror("Error: standard function printf has failed"))
#define print_message(message) (printf("%s\n", message))

bool spParserIsInt(const char* str);

typedef enum {
	SPCHESS_GAME_MODE,
	SPCHESS_DIFFICULTY,
	SPCHESS_USER_COLOR,
	SPCHESS_LOAD,
	SPCHESS_DEFAULT,
	SPCHESS_PRINT_SETTING,
	SPCHESS_QUIT,
	SPCHESS_START,
	SPCHESS_MOVE,
	SPCHESS_GET_MOVES,
	SPCHESS_SAVE,
	SPCHESS_UNDO,
	SPCHESS_RESET,
	SPCHESS_INVALID_LINE,
} SPCHESS_COMMAND;

typedef struct game_setting_command_t {
	SPCHESS_COMMAND cmd;
	bool validIntArg;
	bool validStrArg;
	int arg;
	char *str;
} SPCHESS_GAME_SETTINGS_Command;

SPCHESS_GAME_SETTINGS_Command spParserPraseSettingLine(const char* str);

int spParserSettingCommand(char* str);

typedef struct game_mode_command_t {
	SPCHESS_COMMAND cmd;
	bool validOneStr;
	bool validTwoStr;
	char *strOne, *strTwo;
} SPCHESS_GAME_MODE_Command;

SPCHESS_GAME_MODE_Command spParserPraseGameModeLine(const char* str);
int spParserGameModeCommand(char* str);

//return true iff str is the pattern '<x,y>' where x is int and y is an upper char
bool checkPosPat(char *str);

#endif /* SPCHESSPARSER_H_ */

//

