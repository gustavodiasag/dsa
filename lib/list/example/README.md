#Frame management

An interesting application of linked lists is found in the way some systems
    support *virtual memory
        *.Virtual memory is a mapping of address space that allows a
        process(a running program) to execute without being
    completely in physical memory
        .An advantage of that approach is that a process can use an address
    space much bigger than the one allowed by the system's physical memory. Another advantage is that multiple processes can share the memory of the system while running concurrently.

    A process operating in virtual memory deals with
    virtual adresses.These are addresses that look similar to the physical ones
    in the perspective of the process,
    but that the system must translate before using
        .Each process has its own page table that maps *pages *of its
    virtual address space to *frames *in physical memory
        .Once a process refers to a particular virtual address,
    the appropriate entry in its page table is inspected to determine which
        physical *frame *the page refers to.When a process refers to
        virtual addresses that are not yet in a
        * physical frame *,
    a *page fault *occurs and a frame is properly allocated in memory.

    The purpose of the[example provided](frames.h),
    through the functions `alloc_frame` and `free_frame`,
    is to give an idea of how a linked list data structure would be applied to
    maintain the frames that are available to be allocated
        .A linked list is a good way to manage frames because
    allocation involves frequent insertions and deletions,
    and those operations are performed at the head of the list.The runtime
        complexity of both `alloc_frame` and `free_frame` is **O(1) *
        *because the two functions simply call `list_rm_next`
            and `list_ins_next` from the[list library](../ list.h),
    which are both constant operations.