#include <stdio.h>
#include <string.h>
#include "helpers.h"

void test() {
  char *c_array defer = malloc(sizeof(char) * 50);
  memset(c_array, 'C', sizeof(char) * 50);
  memset(c_array, 'A', sizeof(char) * 10);
  memset((c_array + 10), 'B', sizeof(char) * 10);

  memmove((c_array + 1), (c_array + 20), 10);

  for (int i = 0; i < 50; ++i) {
    printf("%c", c_array[i]);
  }
	printf("\n");
}

