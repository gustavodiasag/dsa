#include "stack.h"

int stack_push(Stack* stack, const void* data)
{
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack* stack, void** data)
{
    return list_rm_next(stack, NULL, data);
}