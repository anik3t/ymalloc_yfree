# ymalloc_yfree
Creating own malloc and free functions i.e. ymalloc and yfree respectively

 *Allocating big chunck of memory with yalloc once using malloc
 
 
 *Maintaining separate lists of unallocated and allocated blocks, where unallocated list keeps the output of yalloc
 
 
 *ymalloc requesting for memory block from unallocated list
 
 
 * yfree freeing out the allocated memory block, ordering the unallocated list according to addresses and then merging the blocks with contiguous addresses

