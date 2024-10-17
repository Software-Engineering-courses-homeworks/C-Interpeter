#include <stdio.h>
#include <string.h>
#include "common.h"
#include "scanner.h"

typedef struct {
    const char* start;
    const char* current;
    int line;
}Scanner;

Scanner scanner;

/// the scanner gets a source code file and initializes the scanner to parse through it
/// @param source the source code
void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

/// checks if the current char is an null byte
/// @return True if null byte, false if not
static bool isAtEnd() {
    return *scanner.current == '\0';
}

/// the function receives a token type and returns a new token
/// @param type
/// @return a new token that represents the type that was received
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.current;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

/// the function receives an error message and returns an error token that includes the message
/// @param message
/// @return an errorToken
static Token errorToken(const char* message) {
    Token token;
    token.start = message;
    token.length = (int)(strlen(message));
    token.line = scanner.line;
    return token;
}

/// scans the current token
/// @return returns a token that repesent the state of the current char in the scanner.
Token scanToken() {
    scanner.start = scanner.current;

    if(isAtEnd()) return makeToken(TOKEN_EOF);

    return errorToken("Unexpected character.");
}

