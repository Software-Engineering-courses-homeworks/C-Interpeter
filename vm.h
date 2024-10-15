//
// Created by ishay on 15/10/2024.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

typedef struct {
    Chunk* chunk;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();

void freeVM();

/// interpets a given chunk to the VM and returns the interpreted result
/// @param chunk
/// @return
InterpretResult interpret(Chunk* chunk);

#endif //CLOX_VM_H
