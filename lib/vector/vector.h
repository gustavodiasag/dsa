#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

/** Dynamic Array/Vector data structure. */
typedef struct _Vec {
    void*       _data;
    size_t      _dsize;
    size_t      _size;
    size_t      _capacity;
    void        (*_destroy)(void* data);
} Vec;

#define vec_dsize(v) ((v)->_dsize)

#define vec_size(v) ((v)->_size)

#define vec_capacity(v) ((v)->_capacity)

#define vec_start(v) ((v)->_data)

#define vec_end(v) ((v)->_data + ((v)->_capacity * (v)->_dsize))

#define vec_at(v, n) ((v)->_data + n)

#define vec_next(v, elt) ((elt + v->_dsize))

Vec* vec_new(size_t dsize, void (*destroy)(void*));

void vec_free(Vec* vec);

bool vec_push(Vec* vec, const void* data);

bool vec_pop(Vec* vec, void** data);

#endif 
