/*
 * SPCHESSArrayList.c
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SPCHESSArrayList.h"

move* spCreateMove(int from[DIM], int to[DIM], char piece, char eaten) {

	move* newMove = (move*) malloc(sizeof(move));
	newMove->from[0] = from[0];
	newMove->from[1] = from[1];
	newMove->to[0] = from[0];
	newMove->to[1] = from[1];
	newMove->piece = piece;
	newMove->eaten = eaten;

	return newMove;
}

void spDestroyMove(move* elem) {
	if (!elem)
		return;

	free(elem);
}

move* spCopyMove(move* elem) {
	if (!elem)
		return NULL;

	move* res = spCreateMove(elem->from, elem->to, elem->piece, elem->eaten);

	if (!res)
		return NULL;

	return res;
}

SPCHESSArrayList* spArrayListCreate(int maxSize) {
	if (maxSize <= 0)
		return NULL;

	SPCHESSArrayList* res = (SPCHESSArrayList*) malloc(
			sizeof(SPCHESSArrayList));
	if (!res) {
		printf("spArrayListCreate has failed\n");
		free(res);
		exit(1);
	}
	res->elements = (move**) malloc(sizeof(move) * maxSize);
	if (!(res->elements)) {
		printf("spArrayListCreate has failed\n");
		free(res);
		exit(1);
	}
	//init values
	res->maxSize = maxSize;
	res->actualSize = 0;

	return res;
}

SPCHESSArrayList* spArrayListCopy(SPCHESSArrayList* src) {
	if (!src)
		return NULL;
	SPCHESSArrayList* copy = spArrayListCreate(src->maxSize);
	if (!copy)
		return NULL;

	copy->maxSize = src->maxSize;
	copy->actualSize = src->actualSize;

	//copy the array
	for (int i = 0; i < copy->actualSize; i++)
		copy->elements[i] = spCopyMove(src->elements[i]);
	return copy;
}

void spArrayListDestroy(SPCHESSArrayList* src) {
	if (!src)
		return;
	for (int i = 0; i < src->actualSize; i++)
		spDestroyMove(src->elements[i]);

	free(src->elements);
	free(src);
}

move* spArrayListGetAt(SPCHESSArrayList* src, int index) {
	if (!src || index < 0 || index >= src->actualSize)
		return NULL;
	return (src->elements[index]);
}

move* spArrayListGetFirst(SPCHESSArrayList* src) {
	if (!src)
		return NULL;
	return spArrayListGetAt(src, 0);
}

move* spArrayListGetLast(SPCHESSArrayList* src) {
	if (!src)
		return NULL;
	return spArrayListGetAt(src, src->actualSize - 1);
}

int spArrayListMaxCapacity(SPCHESSArrayList* src) {
	if (!src)
		return -1;
	return src->actualSize;
}

bool spArrayListIsFull(SPCHESSArrayList* src) {
	if (!src || src->actualSize < src->maxSize)
		return false;
	return true;
}

bool spArrayListIsEmpty(SPCHESSArrayList* src) {
	if (!src || src->actualSize != 0)
		return false;
	return true;
}
SPCHESS_ARRAY_LIST_MESSAGE spArrayListClear(SPCHESSArrayList* src) {
	if (!src)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	src->actualSize = 0;
	//maxSize not affected and elems not affected
	return SP_ARRAY_LIST_SUCCESS;
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddAt(SPCHESSArrayList* src, move* elem,
		int index) {
	if (!src || index < 0 || (index > src->actualSize))
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	if (src->actualSize == src->maxSize)
		return SP_ARRAY_LIST_FULL;

	//shift elements to the right, to make space for the new elem
	for (int i = src->actualSize; i > index; i--)
		src->elements[i] = src->elements[i - 1];

	//insert the new elem
	src->elements[index] = spCopyMove(elem);
	src->actualSize = src->actualSize + 1;
	return SP_ARRAY_LIST_SUCCESS;
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPCHESSArrayList* src,
		move* elem) {
	return spArrayListAddAt(src, elem, 0);
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddLast(SPCHESSArrayList* src, move* elem) {
	if (!src)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListAddAt(src, elem, src->actualSize);
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPCHESSArrayList* src, int index) {
	if (!src || index < 0 || index >= src->actualSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	if (src->actualSize == 0)
		return SP_ARRAY_LIST_EMPTY;

	spDestroyMove(src->elements[index]);
	//shift elements to the left, to overwrite the specified elem
	for (int i = index; i < src->actualSize - 1; i++) {
		src->elements[i] = src->elements[i + 1];
	}
	src->actualSize = src->actualSize - 1;
	return SP_ARRAY_LIST_SUCCESS;
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPCHESSArrayList* src) {
	return spArrayListRemoveAt(src, 0);
}

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPCHESSArrayList* src) {
	if (!src)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListRemoveAt(src, src->actualSize - 1);
}

