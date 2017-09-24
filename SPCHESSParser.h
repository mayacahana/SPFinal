#ifndef SPCHESSPARSER_H_
#define SPCHESSPARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SPCHESS_MAX_LINE_LENGTH 1024
#define perror_message_malloc (perror("Error: standard function malloc has failed"))

/*
 * helper fuction: returns ture iff the
 * str param is a valid integer.
 */
bool spParserIsInt(const char* str);

/*
 * enum to represents user's command type.
 */
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
	SPCHESS_SAVE,
	SPCHESS_UNDO,
	SPCHESS_RESET,
	SPCHESS_INVALID_LINE,
	SPCHESS_SUCCESS,
} SPCHESS_COMMAND;

/*
 * structure represents a user command in the setting state:
 * contains it's type,
 * a bool represents the validity of the
 * relavent param and the relavent param.
 */
typedef struct game_setting_command_t {
	SPCHESS_COMMAND cmd;
	bool validIntArg;
	bool validStrArg;
	int arg;
	char *str;
} SPCHESS_GAME_SETTINGS_Command;

/*
 * Parses a command line in the setting mode and returns a structure
 *  of a setting command with the above params.
 *  @param src - the input string
 *  @return
 *  the settings command
 */
SPCHESS_GAME_SETTINGS_Command spParserPraseSettingLine(const char* str);

/*
 * Helper function which returns the enum represents the string command recieved - setting state..
 */
int spParserSettingCommand(char* str);

/*
 * Structure represents a user command in the game setting:
 * contains it's type,
 * a bool represents the validity of the
 * relavent param and the relavent params.
 */
typedef struct game_mode_command_t {
	SPCHESS_COMMAND cmd;
	bool validOneStr;
	bool validTwoStr;
	char *strOne, *strTwo;
} SPCHESS_GAME_MODE_Command;


/*
 * Parses a command line in the game mode
 * and returns a structure of a game command with the above params.
 */
SPCHESS_GAME_MODE_Command spParserPraseGameModeLine(const char* str);

/*
 * helper function which returns the enum represents
 * the string command recieved - game mode.
 */
int spParserGameModeCommand(char* str);

/*
 * Aux function that helps parse the command.
 * return true iff str is the pattern '<x,y>'
 * where x is int and y is an upper char
 */
bool checkPosPat(char *str);

#endif /* SPCHESSPARSER_H_ */
