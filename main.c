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

        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

/// 
/// @param path 
/// @return 
static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

/// 
/// @param path 
/// @return 
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