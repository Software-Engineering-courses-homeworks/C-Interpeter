#include <stdlib.h>

#include "memory.h"

/// @brief 
/// @param pointer - a pointer to the block of memory we want to reallocate
/// @param oldSize - the old size of the allocation
/// @param newSize - the new size of the allocation
/// @return 
void* reallocate(void* pointer, size_t oldSize, size_t newSize)
{
    //if the new size is zero, then free the memory
    if(newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    //use the realloc function to change the memory allocated to the block
    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}