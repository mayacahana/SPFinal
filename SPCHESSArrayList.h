/*
 * SPCHESSArrayList.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */

#ifndef SPCHESSARRAYLIST_H_
#define SPCHESSARRAYLIST_H_

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

#define WHITE_P 'm'
#define BLACK_P 'M'
#define WHITE_B 'b'
#define BLACK_B 'B'
#define WHITE_R 'r'
#define BLACK_R 'R'
#define WHITE_N 'n'
#define BLACK_N 'N'
#define WHITE_Q 'q'
#define BLACK_Q 'Q'
#define WHITE_K 'k'
#define BLACK_K 'K'
#define EMPTY ' '

#define BOARD_SIZE 8
#define STRING_LEN 51
#define POS_LEN 6
#define PROM_LEN 7


typedef struct move_t {
	int from[2];
	int to[2];
	char piece;
	char eaten;
} move;

typedef struct sp_array_list_t {
	move* elements;
	int actualSize;
	int maxSize;
} SPCHESSArrayList;

typedef enum sp_array_list_message_t {
	SP_ARRAY_LIST_SUCCESS,
	SP_ARRAY_LIST_INVALID_ARGUMENT,
	SP_ARRAY_LIST_FULL,
	SP_ARRAY_LIST_EMPTY
} SPCHESS_ARRAY_LIST_MESSAGE;


move* spCreateMove(int* from, int* to, char piece, char eaten);

void spDestroyMove(move* move);

move* spCopyMove(move* move);

SPCHESSArrayList* spArrayListCreate(int maxSize);

SPCHESSArrayList* spArrayListCopy(SPCHESSArrayList* src);

void spArrayListDestroy(SPCHESSArrayList* src);

move* spArrayListGetAt(SPCHESSArrayList* src, int index);

move* spArrayListGetFirst(SPCHESSArrayList* src);

move* spArrayListGetLast(SPCHESSArrayList* src);

int spArrayListMaxCapacity(SPCHESSArrayList* src);

bool spArrayListIsFull(SPCHESSArrayList* src);

bool spArrayListIsEmpty(SPCHESSArrayList* src);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListClear(SPCHESSArrayList* src);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddAt(SPCHESSArrayList* src, move* elem, int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPCHESSArrayList* src, move* elem);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddLast(SPCHESSArrayList* src, move* elem);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPCHESSArrayList* src, int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPCHESSArrayList* src);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPCHESSArrayList* src);
#endif /* SPCHESSARRAYLIST_H_ */
