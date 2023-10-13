# Second-Chance Page Replacement

The singly linked-list example explained how such data structure might be used to manage frame allocation in a virtual memory system. One issue not addressed, however, was how a system allocates new frames when the list of available frames is empty. To deal with this, a system could free a frame by moving a page from *physical memory* to a disk called *swap disk*. With that approach, the system uses a [page-replacement algorithm](https://www.cs.cornell.edu/courses/cs4410/2018su/lectures/lec15-thrashing.html) to determine which frame is best to free at a given moment. One example of a page-replacement algorithm is the *second-chance algorithm*, also called the [clock algorithm](https://www.cs.cornell.edu/courses/cs4410/2018sp/schedule/slides/08-vm.pdf).

Ideally, it would be great if all pages of a process resided in physical memory at once, but usually this is not possible. Typically, many processes may be running on a system simultaneously, all competing for its physical memory. Sometimes even a single process may have such a large address space that it cannot fit itself into physical memory. Faced with having to replace a page at some point, a number of algorithms could be used for such task:

- **Random**: Pick any page to eject at random.

- **FIFO**: The page brought in earliest is evicted.

- **MRU**: Evict the most recently used page.

- **LFU**: Evict least frequently used page.

- **LRU**: Evict page that hasn't been used for the longest.

By looking at the problem through the perspective of the *LRU* algorithm, it seems reasonable that the best page for a system to replace is the one that it will not access for the longest time to come. However, since it can't predict the future, a system sometimes uses an assumption that the past will be an indication of the future and replaces the page that has been accessed least recently.

The *second-chance algorithm* is one approach to implementing an LRU page-replacement scheme. It works by maintaining a circular list of pages that are currently in physical memory. Consider  each element in the list to store only a page number and a reference value, which is set to either 1 or 0. In practice, each element contains other information as well. All pages initially habe a reference value of 0. Whenever the page is accessed by the system, its reference value is set to 1.

Whene a frame is needed, the system uses the circular list and the reference values it maintains to determine which page should give up its frame. To determine this, it moves through the list until it finds a reference value of 0. As it traverses each page, the system resets the page's reference value from 1 to 0. Once it encounters a 0, it has found a page that has not been accessed by the system since the last cycle through the list; thus, it is the page least recently used. This page is then replaced in physical memory with the new page, and the new page is inserted in place of the old one in the list. If all pages have been accessed since the algorithm was last run, the system endsd up making a complete cycle through the list and replaces the page at which it started. 