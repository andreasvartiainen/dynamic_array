// this is a file for writing tests in
// this is added in the cmake file as target
// and as a test
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

int fail(const char* msg) {
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

	// INSERT TEST
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

	return 0;
}
