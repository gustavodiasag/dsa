#ifndef STACK_H
#define STACK_H

#include "list.h"

/** Stack data structure implemented as a linked-list. */
typedef List Stack;

/** 
 * Initializes a stack.
 * 
 * Since stacks are linked-lists, `stack_init` is defined as `list_init`.
 */
#define stack_init list_init

/** Evaluates the elements count of a stack specified by `s`. */
#define stack_size list_size

/** Evaluates the data at the top of a stack specified by `s`. */
#define stack_peek(s) ((s)->head ? (s)->head->data : NULL)

/**
 * Destroys a stack.
 * 
 * Since stacks are linked-lists, `stack_destroy` is defined as `list_destroy`.
*/
#define stack_destroy list_destroy

/**
 * Pushes an element containing `data` onto a stack specified by `s`.
 * 
 * Returns 0 if pushing the element is successfull, or -1 otherwise. 
 */
int stack_push(Stack* s, const void* data);

/**
 * Pops an element off a stack specified by `s`. Once finished, `data` points
 * to the data stored in the element that was popped.
 * 
 * Returns 0 if popping the element was successfull, or -1 otherwise.
 */
int stack_pop(Stack* s, void** data);

#endif