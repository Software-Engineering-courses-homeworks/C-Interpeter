#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

//The instruction will mean “return from the current function”.
typedef enum {
  OP_RETURN,
  OP_CONSTANT,
  OP_CONSTANT_LONG
} OpCode;

//wrapper around an array of bytes
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

/// @brief 
/// @param chunk 
void initChunk(Chunk* chunk);

/// @brief 
/// @param chunk 
/// @param byte 
/// @param line
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/// @brief 
/// @param chunk 
void freeChunk(Chunk* chunk);

/// adds a constant to the constant pool via discrete function for orderly operation
/// @param chunk
/// @param value
/// @returns the index of the appended constant in the pool
int addConstant(Chunk* chunk, Value value);

/// the function decodes the line from the RLE compression
/// @param chunk the bytecode chunk
/// @param index the index of the offending instruction
/// @return returns the line of the offending instruction
int getLine(Chunk* chunk, int index);
#endif