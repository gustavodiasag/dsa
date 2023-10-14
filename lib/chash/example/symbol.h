#ifndef SYMBOL_H
#define SYMBOL_H

#include "lex.h"

typedef struct _Symbol {
    Token   _token;
    char*   _lexeme;
} Symbol;

#endif