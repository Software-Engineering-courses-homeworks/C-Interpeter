#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/// @brief 
/// @param chunk 
/// @param name 
void disassembleChunk(Chunk* chunk, const char* name);

/// @brief 
/// @param chunk 
/// @param offest 
/// @return 
int disassembleInstruction(Chunk* chunk, int offest);

static int simpleInstruction(const char* name, int offset);

static int constantInstruction(const char* name, Chunk* chunk, int offset);

#endif