#ifndef LEX_H
#define LEX_H

#include "chtbl.h"

/** Token types recognized by the lexical analyzer. */
typedef enum
{
    LEXIT,
    ERROR,
    DIGIT,
    OTHER
} Token;

/**
 * Emits the next token in a stream specified by `istream`, inserting it into a
 * hash-table specified by `symtbl`.
 *
 * Returns the token found.
 */
Token lex(const char* istream, CHTbl* symtbl);

#endif