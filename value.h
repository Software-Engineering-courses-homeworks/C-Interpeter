//
// Created by ishay on 09/10/2024.
//

#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

///initializes a wrapper ValueArray for the interpeter
/// @param arr
void initValueArray(ValueArray* arr);

///frees the values in the ValueArray
/// @param arr
void freeValueArray(ValueArray* arr);

/// adds a value to a ValueArray
/// @param arr
/// @param value
void writeValueArray(ValueArray* arr, Value value);

/// @brief prints the value
/// @param value 
void printValue(Value value);

#endif //VALUE_H
