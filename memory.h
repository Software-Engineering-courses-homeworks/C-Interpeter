#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

//a macro to calculate the new desired capacity given an old one, if the current capacity is 0 (i.e. the array isn't initialized, return a capacity of 8)
#define GROW_CAPACITY(capacity) \ ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldcount, newcount) \ 

#endif