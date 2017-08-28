/*
 * SPCHESSArrayList.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */

#ifndef SPCHESSARRAYLIST_H_
#define SPCHESSARRAYLIST_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define DIM 2

//represent a move
typedef struct move_t {
	int from[DIM];
	int to[DIM];
	char piece;
	char eaten;

} move;

typedef struct sp_array_list_t {
	move* *elements;
	int actualSize;
	int maxSize;
} SPCHESSArrayList;

typedef enum sp_array_list_message_t {
	SP_ARRAY_LIST_SUCCESS,
	SP_ARRAY_LIST_INVALID_ARGUMENT,
	SP_ARRAY_LIST_FULL,
	SP_ARRAY_LIST_EMPTY
} SPCHESS_ARRAY_LIST_MESSAGE;

move* spCreateMove(int from[DIM], int to[DIM], char piece, char eaten);
void spDestroyMove(move* elem);
move* spCopyMove(move* elem);

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

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddAt(SPCHESSArrayList* src, move* elem,
		int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPCHESSArrayList* src,
		move* elem);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddLast(SPCHESSArrayList* src, move* elem);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPCHESSArrayList* src, int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPCHESSArrayList* src);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPCHESSArrayList* src);

#endif /* SPCHESSARRAYLIST_H_ */
