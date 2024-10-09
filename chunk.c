#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

/// @brief initializes a chunk
/// @param chunk - a pointer to a chunk struct
void initChunk(Chunk* chunk)
{
    //initializes the struct values to be those of an empty, uninitialized array
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
}

/// @brief writes a value to a chunk
/// @param chunk - a pointer to a chunk struct
/// @param byte  - a byte that gets appended to the end of the chunk
void writeChunk(Chunk* chunk, uint8_t byte)
{
    //checks if the current array already has capacity for the new byte
    //in case there isn't enough capacity, we grow the array to make room
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

/// @brief frees the previous array and reinitializes the chunk
/// @param chunk 
void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->count);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}