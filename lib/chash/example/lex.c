#include "lex.h"
#include "symbol.h"

#include <string.h>

Token lex(const char* istream, CHTbl* symtbl)
{
    Token token;
    Symbol* symbol;
    int len;
    int retval;

    if (!(symbol = (Symbol*)malloc(sizeof(Symbol)))) {
        return ERROR;
    }
    /* Process the next token. */
    if (!(symbol->_lexeme = next_token(istream))) {
        /* No more input. */
        free(symbol);
        return LEXIT;
    }
    symbol->_token = DIGIT;
    len = strlen(symbol->_lexeme);

    for (int i = 0; i < len; i++) {
        if (!isdigit(symbol->_lexeme[i])) {
            symbol->_token = OTHER;
            break;
        }
    }
    memcpy(&token, &symbol->_token, sizeof(Token));
    /* Insert symbol into the symbol table. */
    if ((retval = chtbl_insert(symtbl, symbol)) == -1) {
        free(symbol);
        return ERROR;
    } else if (retval == 1) {
        /* Symbol is already in the symbol table. */
        free(symbol);
    }
    /* Return token for the parser. */
    return token;
}