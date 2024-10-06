#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

/// @brief initializes a chunk
/// @param chunk - a pointer to a chunk struct
void initChunk(Chunk* chunk)
{
    //initializes the struct values to be thowse of an empty, uninitialized array
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
}

/// @brief writes a value to a chunk
/// @param chunk 
/// @param byte 
void writeChunk(Chunk* chunk, uint8_t byte)
{

}