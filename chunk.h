#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

//The instruction will mean “return from the current function”.
typedef enum {
  OP_RETURN,
} OpCode;

//wrapper around an array of bytes
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
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
#endif