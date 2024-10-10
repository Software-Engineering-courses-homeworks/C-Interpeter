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
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

/// @brief writes a value to a chunk
/// @param chunk - a pointer to a chunk struct
/// @param byte  - a byte that gets appended to the end of the chunk
void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    //checks if the current array already has capacity for the new byte
    //in case there isn't enough capacity, we grow the array to make room
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    //check if the previous instruction has the same line, if so increment the saved line by 1
    //else, if the array size needs to be increased, increase it then add the new line
    if(line == chunk->lines[chunk->lineCount]/100)
    {
        chunk->lines[chunk->lineCount]++;
    }
    else
    {
        //increases the array size using the same memory macros we use for the chunk array
        if(chunk->lineCapacity < chunk->lineCount + 1)
        {
            int oldLineCapacity = chunk->lineCapacity;
            chunk->lineCapacity = GROW_CAPACITY(oldLineCapacity);
            chunk->lines = GROW_ARRAY(int, chunk->lines, oldLineCapacity, chunk->lineCapacity);
        }

        //adds the new line to the end of the array
        chunk->lines[chunk->lineCount] = line * 100;
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
    chunk->lineCount++;
}

/// @brief frees the previous array and reinitialize the chunk
/// @param chunk 
void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->count);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

/// adds a constant to the constant pool via discrete function for orderly operation
/// @param chunk
/// @param value
/// @returns the index of the appended constant in the pool
int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}