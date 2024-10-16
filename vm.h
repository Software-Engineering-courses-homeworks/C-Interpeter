#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

/// initializes the VM
void initVM();

/// frees the VM
void freeVM();

/// interprets a given chunk to the VM and returns the interpreted result
/// @param chunk
/// @return the interpreted result of the given chunk
InterpretResult interpret(Chunk* chunk);

#endif //CLOX_VM_H
