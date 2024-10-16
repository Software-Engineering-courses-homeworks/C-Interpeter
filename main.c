#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[])
{
    // //initializes the VM before injecting the code
    // initVM();
    //
    // Chunk chunk;
    // initChunk(&chunk);
    //
    // int constant = addConstant(&chunk,1.2);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk,constant, 123);
    //
    // writeChunk(&chunk, OP_RETURN, 123);
    // disassembleChunk(&chunk, "test_chunk");
    //
    // interpret(&chunk);
    // //frees all allocated memory
    // freeVM();
    // freeChunk(&chunk);

    int num = 14243301;
    uint8_t arr[] = {num, num >> 8, num >> 16};
    uint32_t constant = (uint32_t)arr[0] << 16 | (uint16_t)arr[1] << 8 | arr[2];
    printf("%d\n", constant);
}