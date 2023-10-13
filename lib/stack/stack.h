#ifndef STACK_H
#define STACK_H

#include "list.h"

/** Stack data structure implemented as a linked-list. */
typedef List Stack;

/** 
 * Initializes a stack so that it can be used in other operations. Since a
 * stack is a linked-list and requires the same initialization, `stack_init` is
 * defined to `list_init`.
 */
#define stack_init list_init

/** Evaluates the number of elements in a stack specified by `stack`. */
#define stack_size list_size

/** 
 * Evaluates the data stored in the element at the top of a stack specified by
 * `stack`.
 */
#define stack_peek(stack) \
    ((stack)->head ? (stack)->head->data : NULL)

/**
 * Destroys a stack. Sine a stack is a linked-list and requires being destroyed
 * in the same way, `stack_destroy` is defined to `list_destroy`.
*/
#define stack_destroy list_destroy

/**
 * Pushes an element onto the stack specified by `stack`. The new element
 * contains a pointer to `data`, so the memory referenced by `data` should
 * remain valid as long as the element remains in the stack.
 * 
 * Returns 0 if pushing the element is successfull, or -1 otherwise. 
 */
int stack_push(Stack* stack, const void* data);

/**
 * Pops an element off the stack specified by `stack`. Once finished, `data`
 * points to the data stored in the element that was popped.
 * 
 * Returns 0 if popping the element was successfull, or -1 otherwise.
 */
int stack_pop(Stack* stack, void** data);

#endif