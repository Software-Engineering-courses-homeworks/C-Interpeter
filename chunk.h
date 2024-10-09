#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

//The instruction will mean “return from the current function”.
typedef enum {
  OP_RETURN,
} OpCode;

//wrapper around an array of bytes
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  ValueArray constants;
} Chunk;

/// @brief 
/// @param chunk 
void initChunk(Chunk* chunk);

/// @brief 
/// @param chunk 
/// @param byte 
void writeChunk(Chunk* chunk, uint8_t byte);

/// @brief 
/// @param chunk 
void freeChunk(Chunk* chunk);

/// adds a constant to the constant pool via discrete function for orderly operation
/// @param chunk
/// @param value
/// @returns the index of the appended constant in the pool
int addConstant(Chunk* chunk, Value value);
#endif