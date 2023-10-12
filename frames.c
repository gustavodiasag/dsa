#include "frames.h"

int alloc_frame(List* frames)
{
    int frame_id, *data;

    if (list_rm_next(frames, NULL, (void**)&data)) {
        // Frame cannot be used.
        return -1;
    } 
    // Store the number of the available frame.
    frame_id = *data;
    free(data);
    
    return frame_id;
}

int free_frame(List* frames, int frame_id)
{
    int* data;
    // Alocate storage for the frame number.
    if (!(data = (int*)malloc(sizeof(int)))) {
        return -1;
    }
    // Put the frame back in the list of available frames.
    *data = frame_id;

    if (list_ins_next(frames, NULL, data)) {
        return -1;
    }
    return 0;
}