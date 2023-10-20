#include <assert.h>
#include <string.h>

#ifdef MEMORY_LOG
#include <stdio.h>
#endif

#include "vector.h"

#define _base_size 8

Vec* vec_new(size_t dsize, void (*destroy)(void*))
{
    assert(dsize > 0);

    Vec* v = (Vec*)malloc(sizeof(Vec));
    v->_data = NULL;
    v->_dsize = dsize;
    v->_size = 0;
    v->_capacity = 0;
    v->_destroy = destroy;

    return v;
}

void vec_free(Vec* v)
{
    void* data;
    while (vec_capacity(v) > 0) {
        if (vec_pop(v, (void**)&data) && v->_destroy) {
            v->_destroy(data);
        }
    }
    // Free dynamic array.
    free(v->_data);
    // Clear struture memory.
    memset(v, 0, sizeof(Vec));
}

static void _vec_resize(Vec* v)
{   
    if (vec_size(v) < _base_size) {
        v->_size = _base_size;
    } else {
        v->_size <<= 1;
    }
    v->_data = (void*)realloc(v->_data, v->_size * v->_dsize);
}

bool vec_push(Vec* v, const void* data)
{
    if (vec_capacity(v) >= vec_size(v)) {   
#ifdef MEMORY_LOG
        size_t prev = v->_size * sizeof(v->_data);
#endif
        _vec_resize(v);
#ifdef MEMORY_LOG
        size_t new = v->_size * sizeof(v->_data);
        printf("'vec_push' at %p (%zu bytes).\n", v->_data, (new - prev));
#endif
    }

    if (!vec_start(v)) {
        return false;
    }
    void* pos = vec_start(v) + (vec_capacity(v) * vec_dsize(v));
    
    memcpy(pos, data, vec_dsize(v));
    v->_capacity++;

    return true;
}

bool vec_pop(Vec* v, void** data)
{
    if (v->_capacity <= 0) {
        return false;
    }
    void* pos = vec_start(v) + ((vec_capacity(v) - 1) * vec_dsize(v));
    
    if (!pos) {
        return false;
    }
    *data = pos;

    v->_capacity--;

    return true;
}