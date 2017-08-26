/*
 * SPCHESSFileAux.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef SPCHESSFILEAUX_H_
#define SPCHESSFILEAUX_H_

#define BOARD_SIZE 8
#define SPCHESS_GAME_PLAYER_1_SYMBOL 'W'
#define SPCHESS_GAME_PLAYER_2_SYMBOL 'B'
#define EMPTY '_'
#define HISTORY_SIZE 6

typedef enum sp_array_list_message_t {
	SP_ARRAY_LIST_SUCCESS,
	SP_ARRAY_LIST_INVALID_ARGUMENT,
	SP_ARRAY_LIST_FULL,
	SP_ARRAY_LIST_EMPTY
} SP_ARRAY_LIST_MESSAGE;


#endif /* SPCHESSFILEAUX_H_ */
