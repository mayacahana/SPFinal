#ifndef SPCHESSARRAYLIST_H_
#define SPCHESSARRAYLIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DIM 2

/*
 * Structure represents a move in the game:
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
 * Structure represents an list of history plays.
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
 * basic functions of structure move: create a new move,
 * destroy a move by freeing it's memory and copy of a move.
 */

/*
 *Create a move object with the specified targets.
 *@param from[DIM] - represent the start position
 *@param to[DIM] - represent the target position
 *@param piece - indicates the type of the soldier
 *@param eaten - indicates if the soldier was eaten in this specific move
 *@return
 *the move object
 */
move* spCreateMove(int from[DIM], int to[DIM], char piece, char eaten);
/*
 * Frees all memory resources associated with the move object.
 * If the source is NULL, then the function does nothing.
 * @param elem - the move
 */
void spDestroyMove(move* elem);
/*
 *	Creates an exact copy of the move object.
 *	@param src - the source move.
 *	@return
 *	NULL if either an allocation error occurs or src == NULL.
 *	A new copy of the move object, otherwise.
 */
move* spCopyMove(move* elem);

/*
 * basic functions of arrayList: create a new list (by setting it's max size),
 * copy an arrayList and destroy an arrayList (by freeing it's memory).
 */

/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
SPCHESSArrayList* spArrayListCreate(int maxSize);
/**
 *	Creates an exact copy of the src array list. Elements in the new copy will
 *	be in the same order as they appeared in the source list.
 *	@param src - the source array list.
 *	@return
 *	NULL if either an allocation error occurs or src == NULL.
 *	A new copy of the source array list, otherwise.
 */
SPCHESSArrayList* spArrayListCopy(SPCHESSArrayList* src);
/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void spArrayListDestroy(SPCHESSArrayList* src);

/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
move* spArrayListGetAt(SPCHESSArrayList* src, int index);
/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
move* spArrayListGetFirst(SPCHESSArrayList* src);

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
move* spArrayListGetLast(SPCHESSArrayList* src);
/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int spArrayListMaxCapacity(SPCHESSArrayList* src);
/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int spArrayListSize(SPCHESSArrayList* src);
/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool spArrayListIsFull(SPCHESSArrayList* src);
/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
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
