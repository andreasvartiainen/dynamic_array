// this is a file for writing tests in
// this is added in the cmake file as target
// and as a test
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

int fail(const char* msg, ...) {
	return fprintf(stderr, "TEST FAILED: %s\n", msg);
}

// test macro that returns != 0 if the (CASE) is not true
// so ( true = false ) = 0 => !(CASE) == 1 and the fail triggers
// MSG should be in format "when variable is 1 the output is 1"
#define TEST(CASE, MSG) \
printf("RUNNING: %s\n", MSG);\
if (!(CASE)) { \
	return fail(MSG);\
}

#define push_to_array(array, items)\
	for (int i = 0; i < (items); i++) {\
		da_push(array, i);\
	}\

int main() { // NOLINT
	{
	Integers array = {0};
	TEST(array.capacity == 0, "empty array capacity is 0");
	TEST(array.count == 0, "empty array count is 0");
	TEST(array.items == nullptr, "empty array items is nullptr");

	Doubles d_array = {0};
	TEST(d_array.items == nullptr, "creating a double list works");

	// add 10 items to the linked list
	for (int i = 0; i < 10; i++) {
		da_push(array, i);
	}

	TEST(array.count == 10, "adding 10 elements to array; count is 10");
	TEST(array.capacity == 256, "adding 10 elements to array; capacity is 256");
	
	// add items to the linked list
	for (int i = 0; i < 300; i++) {
		da_push(array, i);
	}

	TEST(array.count == (size_t)(310), "adding 300 elements to array; count is 310");
	TEST(array.capacity == (size_t)(512), "adding 300 elements to array; capacity is 512");
	TEST(array.items[200] == 190, "item at index 200 is 190");

	int item = 0;
	for (int i = 0; i < 300; i++) {
		da_pop(array, item);
	}

	TEST(array.capacity == (size_t)(512), "removing 300 elements to array; capacity is 512");
	TEST(array.count == (size_t)(10), "removing 300 elements to array; count is 10");

	int value = rand();
	da_push(array, value);
	TEST(array.items[array.count - 1] == value, "after da_push() last (item) is (item)");

	// -------- FREE AFTER THIS --------
	
	da_free(array);
	da_free(d_array);

	TEST(array.items == nullptr, "after da_free() array items is nullptr");
	TEST(d_array.items == nullptr, "after da_free() d_array items is nullptr");
	}

	// ---------- INSERT_TEST ----------
	{
	Integers array = {0};
	da_insert(array, 42, 10);

	TEST(array.capacity == 256, "inserting 1 elements to array; capacity is 256");
	TEST(array.count == 1, "inserting to empty array; count is 1");
	TEST(array.items[array.count - 1] == 42, "inserting 42 to empty array; items[count-1] == 42");

	for (int i = 0; i < 300; i++) {
		da_insert(array, 37, 0); // NOLINT
	}

	TEST(array.count == 301, "inserting to 300 items with one item to array; count is 301");
	TEST(array.capacity == 512, "inserting to 300 items with one item to array; capacity is 512");

	da_insert(array, 69, 0);

	TEST(array.count == 302, "inserting to 300 items with one item to array; count is 301");
	TEST(array.capacity == 512, "inserting to 300 items with one item to array; capacity is 512");
	TEST(array.items[0] == 69, "array index 0 is 69 after inserting 69");

	da_free(array);
	}
	// ---------- INSERT_TEST_END ----------

	// ---------- REMOVE_FROM_INDEX_TEST ---
	{
	Integers array = {0};
	int item = 0;

	da_remove(array, item, 5);

	TEST(array.count == 0, "removing from empty doesn't decrement array.count");
	TEST(array.capacity == 0, "removing from empty doesn't capacity array.count");

	for (int i = 0; i < 200; i++) {
		da_push(array, i);
	}

	da_remove(array, item, 1000); // should behave like da_pop
																//
	TEST(array.count == 199, "removing from array decrements array.count");
	TEST(array.capacity == 256, "removing from array doesn't affeect array.capacity");
	TEST(item == 199, "removing from array returns the correct value");

	da_remove(array, item, 15);

	TEST(array.count == 198, "removing from array decrements array.count");
	printf("%d\n", item);
	TEST(item == 15, "removing from array returns the correct value");

	da_remove(array, item, 0); // should behave like da_pop
	TEST(array.count == 197, "removing from array decrements array.count");
	printf("%d\n", item);
	TEST(item == 0, "removing from array returns the correct value");
	
	for (int i = 0; i < 3000; i++) {
		da_remove(array, item, 0);
	}

	TEST(array.count == 0, "emptying the array with da_remove() makes the count 0");
	TEST(item == 0, "emptying the array with da_remove() returns 0");

	da_free(array);
	}
	// ---------- REMOVE_FROM_INDEX_TEST_END --
	
	// ---------- DA_GET_TESTING --------------
	{
	Integers array = {0};
	int item = 0;
	push_to_array(array, 200);

	da_get(array, item, 100);

	TEST(item == 100, "item at index 100 is 100");

	da_get(array, item, 0);

	TEST(item == 0, "item at index 0 is 0");

	da_get(array, item, array.count - 1);

	TEST(item == 199, "item at last index is 199");

	da_get(array, item, 100000);

	TEST(item == 199, "too high index returns item");

	da_free(array);
	}
	// ---------- DA_GET_TESTING_END   ----------
	
	// ---------- DA_CLEAR_TESTING     ----------
	{
	Integers array = {0};
	push_to_array(array, 200);

	da_clear(array);

	int item = 0;
	for (size_t i = 0; i < 200; i++) {
		da_get(array, item, i);
	}

	TEST(item == 0, "all items in the list are 0 after clear");
	TEST(array.count == 0, "array count is 0");
	TEST(array.capacity == 256, "array capacity is 256");

	da_free(array);
	}
	// ---------- DA_CLEAR_TESTING_END ----------
	
	// ---------- DA_SET_TESTING ----------
	{
	Integers array = {0};
	push_to_array(array, 200);

	da_set(array, 0, 15);

	TEST(array.items[0] == 15, "item at index 0 set to 15 is 15");

	da_set(array, 199, 15);

	TEST(array.items[array.count-1] == 15, "item at last index when set to 15 is 15");

	da_set(array, 50, 15);

	TEST(array.items[50] == 15, "item at last index when set to 15 is 15");

	da_free(array);
	}
	// ---------- DA_SET_TESTING_END ----------
	//
	return 0;
}
