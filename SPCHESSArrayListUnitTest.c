/*
 * SPCHESSArrayListUnitTest.c
 *
 *  Created on: 28 באוג׳ 2017
 *      Author: uri
 */
#include "unit_test_util.h"
#include "SPCHESSArrayList.h"
#define CAPACITY_SIZE 3

static bool spArrayListBasicGetTest() {

	SPCHESSArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);

	move* elem;
	int from[DIM] = { 0, 0 };
	int to[DIM] = { 5, 0 };
	char piece = 'r';
	char eaten = 'M';
	elem = spCreateMove(from, to, piece, eaten);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);

	spArrayListRemoveFirst(list);

	ASSERT_TRUE(spArrayListIsEmpty(list));

	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicCopyTest() {
	SPCHESSArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);

	move* elem;
	int from[DIM] = { 0, 0 };
	int to[DIM] = { 5, 0 };
	char piece = 'r';
	char eaten = 'M';
	elem = spCreateMove(from, to, piece, eaten);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 1);

	SPCHESSArrayList* copy = spArrayListCopy(list);

	ASSERT_TRUE(
			spArrayListGetFirst(copy)->to[0]
					== spArrayListGetFirst(list)->to[0]);
	ASSERT_TRUE(spArrayListMaxCapacity(copy) == spArrayListMaxCapacity(list));

	spArrayListDestroy(copy);
	spArrayListDestroy(list);
	return true;

}

static bool spArrayListBasicRemoveTest() {

	SPCHESSArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);

	move* elem;
	int from[DIM] = { 0, 0 };
	int to[DIM] = { 5, 0 };
	char piece = 'r';
	char eaten = 'M';
	elem = spCreateMove(from, to, piece, eaten);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 1);

	move* elem1;
	int from1[DIM] = { 7, 7 };
	int to1[DIM] = { 2, 1 };
	char piece1 = 'Q';
	char eaten1 = 'k';
	elem = spCreateMove(from1, to1, piece1, eaten1);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 2);

	move* elem2;
	int from2[DIM] = { 3, 4 };
	int to2[DIM] = { 5, 0 };
	char piece2 = 'b';
	char eaten2 = 'B';
	elem = spCreateMove(from2, to2, piece2, eaten2);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);

	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);

	ASSERT_TRUE(spArrayListGetFirst(list)->from[0] == 3);
	ASSERT_TRUE(spArrayListGetLast(list)->piece == 'r');

	ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListIsEmpty(list));

	ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_INVALID_ARGUMENT);

	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicAddTest() {
	SPCHESSArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);

	move* elem;
	int from[DIM] = { 0, 0 };
	int to[DIM] = { 5, 0 };
	char piece = 'r';
	char eaten = 'M';
	elem = spCreateMove(from, to, piece, eaten);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 1);

	move* elem1;
	int from1[DIM] = { 7, 7 };
	int to1[DIM] = { 2, 1 };
	char piece1 = 'Q';
	char eaten1 = 'k';
	elem = spCreateMove(from1, to1, piece1, eaten1);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 2);

	move* elem2;
	int from2[DIM] = { 3, 4 };
	int to2[DIM] = { 5, 0 };
	char piece2 = 'b';
	char eaten2 = 'B';
	elem = spCreateMove(from2, to2, piece2, eaten2);
	ASSERT_TRUE(spArrayListAddFirst(list, elem) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListSize(list) == 3);

	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	ASSERT_TRUE(spArrayListIsFull(list));
	spArrayListDestroy(list);
	return true;
}
static bool spArrayListCreateTest() {
	SPCHESSArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	spArrayListDestroy(list);
	return true;
}

int main() {
	RUN_TEST(spArrayListCreateTest);
	RUN_TEST(spArrayListBasicAddTest);
	RUN_TEST(spArrayListBasicRemoveTest);
	RUN_TEST(spArrayListBasicGetTest);
	RUN_TEST(spArrayListBasicCopyTest);
	return 0;
}

