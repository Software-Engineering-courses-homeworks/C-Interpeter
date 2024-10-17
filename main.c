#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

/// a REPL function for single line arguments
static void repl() {
    char line[1024];

    for(;;) {
        printf("> ");
        //go down a line if we read an entire line
        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

/// 
/// @param path 
/// @return the content of the file
static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");

    if(file == NULL) {
        fprintf(stderr, "Could not open file %s\n", path);
        exit(74);
    }
    //goes to the end of the file
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    //allocates memory for the entire file and if it fails to do so exits
    char* buffer = (char*)malloc(fileSize + 1);
    if(buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
        exit(74);
    }

    //reads the file and checks for successful read
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if(bytesRead < fileSize) {
        fprintf(stderr, "Could not read \"%s\"\n", path);
        exit(74);
    }
    //adds the null byte at the end of the string
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

/// 
/// @param path 
/// @return will returns exit code if there will be errors (65-for compilation error, 70-for runtime error)
static char* runFile(const char* path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if(result == INTERPRET_COMPILE_ERROR)
        exit(65);
    if(result == INTERPRET_RUNTIME_ERROR)
        exit(70);
}

int main(int argc, const char* argv[]) {
    //initializes the VM before injecting the code
    initVM();

    if(argc == 1) {
        repl();
    }
    else if(argc == 2) {
        runFile(argv[1]);
    }
    else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    //frees all allocated memory
    freeVM();
    return 0;
}