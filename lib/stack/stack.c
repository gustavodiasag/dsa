#include "stack.h"

int stack_push(Stack* s, const void* data)
{
    return list_ins_next(s, NULL, data);
}

int stack_pop(Stack* s, void** data)
{
    return list_rm_next(s, NULL, data);
}