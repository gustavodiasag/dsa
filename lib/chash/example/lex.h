#ifndef LEX_H
#define LEX_H

#include "chtbl.h"

/** Token types recognized by the lexical analyzer. */
typedef enum _Token {LEXIT, ERROR, DIGIT, OTHER} Token;

/**
 * Emits the next token that exists in the input stream specified by `istream`,
 * inserting its correspondent symbol structure into the chained hash-table
 * specified by `symtbl`.
 * 
 * 
 */
Token lex(const char *istream, CHTbl* symtbl);

#endif