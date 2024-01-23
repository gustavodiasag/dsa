#include "queue.h"

int queue_enqueue(Queue* q, const void* data)
{
    return list_ins_next(q, list_tail(q), data);
}

int queue_dequeue(Queue* q, void** data)
{
    return list_rm_next(q, NULL, data);
}