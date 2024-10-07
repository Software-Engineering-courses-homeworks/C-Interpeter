#include "debug.h"
#include <stdio.h>

/// @brief disassembles the chunk of instructions one instruction at a time
/// @param chunk - the instruction chunk
/// @param name - the name of the chunk
void disassembleChunk(Chunk* chunk, const char* name)
{
    printf("== %s ==", name);

    for(int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

/// @brief 
/// @param chunk 
/// @param offset 
/// @return 
int disassembleInstruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];
    switch(instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

/// @brief outputs the simple instruction for debugging
/// @param name 
/// @param offset 
/// @return 
int simpleInstruction(const char* name, int offset)
{
    printf("%s\n",name);
    return offset + 1;
}