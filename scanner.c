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

/// checks if the current char is a null byte
/// @return True if null byte, false if not
static bool isAtEnd() {
    return *scanner.current == '\0';
}

/// the function returns the next character
/// @return the next character
static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

/// the function recives a char and checks if the current char matches it
/// @param expected
/// @return true if there is a match with expected, false if not
static bool match(char expected) {
    //checks if we reached the end of the string
    if (isAtEnd()) return false;
    //checks if they not the same
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
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
/// @return returns a token that represent the state of the current char in the scanner.
Token scanToken() {
    scanner.start = scanner.current;

    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    switch(c) {
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);
        case ',': return makeToken(TOKEN_COMMA);
        case '!': return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=': return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<': return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>': return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    }

    return errorToken("Unexpected character.");
}