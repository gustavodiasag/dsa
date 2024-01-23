#ifndef FRAMES_H
#define FRAMES_H

#include "list.h"

/**
 * Retrieves the number of a free frame from a list of frames specified by
 * `frames`.
 *
 * Returns the frame number if a free frame is successfully found, or -1
 * otherwise.
 */
int alloc_frame(List* frames);

/**
 * Places the frame number specified by `frame_id` into the list of available
 * frames specified by `frames` once a page is removed from physical memory.
 *
 * Returns 0 if the element is successfully inserted and -1 otherwise.
 */
int free_frame(List* frames, int frame_id);

#endif