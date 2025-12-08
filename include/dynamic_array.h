#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t da_initial_size = 256;

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Integers;

typedef struct {
  double *items;
  size_t count;
  size_t capacity;
} Doubles;

// item is the value to be pushed to the array
#define da_push(array, item)                                                   \
  do {                                                                         \
    if ((array).count >= (array).capacity) {                                   \
      if ((array).capacity == 0) {                                             \
        (array).capacity = da_initial_size;                                    \
      } else {                                                                 \
        (array).capacity *= 2;                                                 \
      }                                                                        \
      void *ptr =                                                              \
          realloc((array).items, (array).capacity * sizeof(*(array).items));   \
      assert(ptr);                                                             \
      (array).items = ptr;                                                     \
    }                                                                          \
    (array).items[(array).count++] = item;                                     \
  } while (0)

#define da_insert(array, item, index)                                          \
  do {                                                                         \
    if ((index) >= (array).count) {                                            \
      da_push(array, (item));                                                  \
    } else {                                                                   \
      if ((array).count + 1 >= (array).capacity) {                             \
        void *ptr = realloc((array).items,                                     \
                            (array).capacity * 2 * sizeof(*(array).items));    \
        assert(ptr);                                                           \
        (array).items = ptr;                                                   \
        (array).capacity *= 2;                                                 \
      }                                                                        \
      memmove(((array).items + (index) + 1), ((array).items + (index)),        \
              (array).count - (index));                                        \
      (array).items[index] = item;                                             \
      (array).count++;                                                         \
    }                                                                          \
  } while (0)

// item is the destination where we store the value
#define da_pop(array, item)                                                    \
  do {                                                                         \
    if ((array).count > 0) {                                                   \
      (item) = (array).items[--(array).count];                                 \
      (array).items[(array).count] = 0;                                        \
    }                                                                          \
  } while (0)

#define da_free(array)                                                         \
  do {                                                                         \
    free((array).items);                                                       \
    (array).items = nullptr;                                                   \
  } while (0)

#endif
