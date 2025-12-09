#include "dynamic_array.h"
#include "helpers.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(Integers *array) {
	for (size_t i = 0; i < array->count; i++) {
		int item = 0;
		da_get(*array, item, i);
		printf("%2d ", item);
	}
	printf("\n");
}

int main() { // NOLINT
  Integers array = {0};
	for (int i = 0; i < 25; i++) {
		da_push(array, i);
	}

	int item = 10;

	print_array(&array);
	printf("\n");

	for (int i = 0; i < 5; i++) {
		da_remove(array, item, 0);
	}
	da_remove(array, item, 5);
	da_remove(array, item, 5);
	da_remove(array, item, 5);
	da_remove(array, item, 5);
	print_array(&array);
	da_remove(array, item, 1000);
	da_clear(array);
	da_push(array, 15);

	print_array(&array);
	printf("\n");

	printf("%d\n", item);
	printf("%zu\n", array.count);
	printf("%zu\n", array.capacity);

	return 0;
}
