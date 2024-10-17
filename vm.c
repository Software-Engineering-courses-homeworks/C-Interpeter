#include "common.h"
#include "vm.h"
#include "debug.h"

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
#define READ_CONSTANT_LONG(arr)  (vm.chunk->constants.values[(uint32_t)arr[2] << 16 | (uint16_t)arr[1] << 8 | arr[0]])
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip-vm.chunk->code));
#endif

    //runs through all the instructions in the chunk and returns the runtime result from the interpretation
    for(;;)
    {
        uint8_t instruction;

        //the switch is used to dispatch the instructions in the most simple way
        switch(instruction = READ_BYTE())
        {
            //case for a runtime result that completed without anyprolem
            case OP_RETURN:
            {
                return INTERPRET_OK;
            }
            //case for a constant value. prints the value
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            //the case handles the long values, creates an array of the bytes and then build it as a value
            case OP_CONSTANT_LONG:
            {
                //uint32_t constant = READ_CONSTANT_LONG();
                uint8_t arr[] = {READ_BYTE(), READ_BYTE(), READ_BYTE()};
                Value constant = READ_CONSTANT_LONG(arr);
                printValue(constant);
                printf("'\n");
                break;
            }
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

