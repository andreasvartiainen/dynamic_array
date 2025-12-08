#include "dynamic_array.h"
#include "helpers.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { // NOLINT
  char *c_array defer = malloc(sizeof(char) * 50);
  memset(c_array, 'C', sizeof(char) * 50);
  memset(c_array, 'A', sizeof(char) * 10);
  memset((c_array + 10), 'B', sizeof(char) * 10);

  memmove((c_array + 1), (c_array + 20), 10);

  for (int i = 0; i < 50; ++i) {
    printf("%c", c_array[i]);
  }

  Integers array = {0};

	size_t index = 0;
	int item = 69;

  if ((index) >= array.count) {
    da_push(array, (item));
  } else {
		if (array.count + 1 >= array.capacity) {
			array.items = realloc(&array, array.capacity * 2 * sizeof(item));
			array.capacity *= 2;
		}
		memmove((array.items + index + 1), (array.items + index), array.count - index);
		array.items[index] = item;
		array.count++;
  }

  return 0;
}
