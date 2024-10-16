#include "common.h"
#include "vm.h"

VM vm;

/// initializes the VM
void initVM()
{

}

/// frees the VM
void freeVM()
{

}

/// a helper function that executes the bytecode by iterating through the chunk one bytecode at a time
/// @return returns an interpreted result
static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    //runs through all the instructions in the chunk and returns the runtime result from the interpretation
    for(;;)
    {
        uint8_t instruction;

        //the switch is used to dispatch the instructions in the most simple way
        switch(instruction = READ_BYTE())
        {
            case OP_RETURN:
            {
                return INTERPRET_OK;
            }
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            //todo: complete implementing the long constant with the accompanying macro and assmbly
            // case OP_CONSTANT_LONG:
            // {
            //     uint32_t constant = (uint32_t)READ_CONSTANT() << 16 | (uint16_t)READ_CONSTANT() << 8 | READ_CONSTANT();
            // }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

/// interprets a given chunk to the VM and returns the interpreted result
/// @param chunk
/// @return the interpreted result of the given chunk
InterpretResult interpret(Chunk* chunk)
{
    //gives the VM the chunk we want to execute
    vm.chunk = chunk;
    //stores the latest instruction in the chunk that needs to be processed
    vm.ip = vm.chunk->code;

    //returns the interpreted result of running the chunk
    return run();
}

