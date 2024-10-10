#include "debug.h"
#include "value.h"
#include <stdio.h>

/// @brief disassembles the chunk of instructions one instruction at a time
/// @param chunk - the instruction chunk
/// @param name - the name of the chunk
void disassembleChunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

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

    if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        printf("    | ");
    else
        printf("%4d ", chunk->lines[offset]);


    uint8_t instruction = chunk->code[offset];
    switch(instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

/// the function decodes the line from the RLE compression
/// @param chunk the bytecode chunk
/// @param offset the index of the offending instruction
/// @return returns the line of the offending instruction
int getLine(Chunk* chunk, int offset)
{
    int currentLine = 0;
    int tempLine = chunk->lines[currentLine];

    //iterates through the lines and decreases the saved line value until we pass all the instructions in a line
    //then passes on to the next line and repeats the process up to the offending instruction
    for(int i = 0; i < offset; i++)
    {
        //checks if arrived at the last instruction (i.e. the first instruction added to the line)
        //and if so, moves on to the next line
        if(tempLine % 100 == 0)
        {
            currentLine++;
            tempLine = chunk->lines[currentLine];
        }
        //else, decrements the encoded instruction count in the line value
        else
            tempLine--;
    }
    return chunk->lines[currentLine] / 100;
}

/// @brief outputs the simple instruction for debugging
/// @param name 
/// @param offset 
/// @return 
static int simpleInstruction(const char* name, int offset)
{
    printf("%s\n",name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}