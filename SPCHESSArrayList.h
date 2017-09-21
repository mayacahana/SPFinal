#ifndef SPCHESSARRAYLIST_H_
#define SPCHESSARRAYLIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DIM 2

/*
 * structure represents a move in the game:
 * from[DIM] - a 2-size array contains row and col of the source location
 * to[DIM] - a 2-size array contains row and col of the destination location
 * char piece - char represents the current piece at 'from' location
 * char eaten - char represents the current piece at 'to' location (or EMPTY if there isn't one)
 */
typedef struct move_t {
	int from[DIM];
	int to[DIM];
	char piece;
	char eaten;
} move;

/*
 * structure represents an list of history plays.
 * Contains an array of moves, real size of list, and full capacity size.
 */
typedef struct sp_array_list_t {
	move* *elements;
	int actualSize;
	int maxSize;
} SPCHESSArrayList;


/*
 * enum represents a mssage for errors and success
 * of the list functions.
 */
typedef enum sp_array_list_message_t {
	SP_ARRAY_LIST_SUCCESS,
	SP_ARRAY_LIST_INVALID_ARGUMENT,
	SP_ARRAY_LIST_FULL,
	SP_ARRAY_LIST_EMPTY
} SPCHESS_ARRAY_LIST_MESSAGE;


/*
 * basic functions of structur move: create a new move,
 * destroy a move by freeing it's memory and copy of a move.
 */
move* spCreateMove(int from[DIM], int to[DIM], char piece, char eaten);
void spDestroyMove(move* elem);
move* spCopyMove(move* elem);

/*
 * basic functions of arrayList: create a new list (by setting it's max size),
 * copy an arrayList and destroy an arrayList (by freeing it's memory).
 */
SPCHESSArrayList* spArrayListCreate(int maxSize);
SPCHESSArrayList* spArrayListCopy(SPCHESSArrayList* src);
void spArrayListDestroy(SPCHESSArrayList* src);

/*
 * returns the move elem in the current index,
 * or an error msg if it doesn't exits or index is invalid.
 */
move* spArrayListGetAt(SPCHESSArrayList* src, int index);
/*
 * returns the first move elem of the list,
 * or an error msg if it doesn't exits or index is invalid.
 */
move* spArrayListGetFirst(SPCHESSArrayList* src);

/*
 * returns the last move elem of the list,
 * or an error msg if it doesn't exits or index is invalid.
 */
move* spArrayListGetLast(SPCHESSArrayList* src);
/*
 * general functions of the list: it's max capacity size,
 * it's actuall size, if it's full, and it's empty.
 */
int spArrayListMaxCapacity(SPCHESSArrayList* src);
int spArrayListSize(SPCHESSArrayList* src);
bool spArrayListIsFull(SPCHESSArrayList* src);
bool spArrayListIsEmpty(SPCHESSArrayList* src);

/*
 * functions clears the list by reset it's
 * actual size and clear all elements.
 */
SPCHESS_ARRAY_LIST_MESSAGE spArrayListClear(SPCHESSArrayList* src);
/*
 * function adds the specified elem at index location on the list, or msg error o/w.
 */
SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddAt(SPCHESSArrayList* src, move* elem,
		int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPCHESSArrayList* src,
		move* elem);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListAddLast(SPCHESSArrayList* src, move* elem);


/*
 * functions removes the current elem at index location, or error msg o/w.
 */
SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPCHESSArrayList* src, int index);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPCHESSArrayList* src);

SPCHESS_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPCHESSArrayList* src);

#endif /* SPCHESSARRAYLIST_H_ */
