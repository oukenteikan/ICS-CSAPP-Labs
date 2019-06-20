/*
Name: Charlie
Student ID: 
Course: ICS
Lab: Malloc
Approach: Segregated list && First hit
Detail: Define LISTSIZE as the number of block lists.
        Define PREV, SUCC and other Macro for pointer operations.
        Shrink CHUNKSIZE for higher utility.
        Use which_list, append_list and delete_list for neat operations on block lists.
Comment: Good code style.
         Use check_heap for checking heap in debug mode.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

#define DEBUGx

/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ 
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<6)  /* Extend heap by this amount (bytes) */  
#define LISTSIZE    16

#define MAX(x, y) ((x) > (y)? (x) : (y))  
#define MIN(x, y) ((x) < (y)? (x) : (y))
/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc)) 

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))            
#define PUT(p, val)  (*(unsigned int *)(p) = (val))    

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)                   
#define GET_ALLOC(p) (GET(p) & 0x1)                    

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)                      
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) 

/* Given block ptr bp, compute address of its prev and succ*/
#define PREV(bp)       ((char *)(bp))                      
#define SUCC(bp)       ((char *)(bp) + WSIZE)
#define PREV_REL(bp)   GET(PREV(bp))
#define SUCC_REL(bp)   GET(SUCC(bp))
#define PREV_FREE(bp)  (free_p + GET(PREV(bp)))
#define SUCC_FREE(bp)  (free_p + GET(SUCC(bp)))

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(HDRP(bp))) 
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) 

/* Global variables */
static char *heap_listp = 0;  /* Pointer to first block */
static char *free_p = 0;

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static unsigned int which_list(size_t size);
static void append_list(char *bp, size_t size);
static void delete_list(char *bp, size_t size);

/* 
 * mm_init - Initialize the memory manager 
 */
int mm_init(void) 
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk((4+LISTSIZE)*WSIZE)) == (void *)-1) 
        return -1;
    PUT(heap_listp, 0);                          /* Alignment padding */
    for (int i = 1 ; i <= LISTSIZE ; i ++)
        PUT(heap_listp + (i * WSIZE), 0);
    PUT(heap_listp + ((1+LISTSIZE)*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
    PUT(heap_listp + ((2+LISTSIZE)*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 
    PUT(heap_listp + ((3+LISTSIZE)*WSIZE), PACK(0, 1));     /* Epilogue header */
    free_p = heap_listp;
    heap_listp += (2+LISTSIZE)*WSIZE;      
    
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(2*DSIZE/WSIZE) == NULL) 
        return -1;

#ifdef DEBUG
    check_heap();
#endif

    return 0;
}

/* 
 * malloc - Allocate a block with at least size bytes of payload 
 */
void *malloc(size_t size) 
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;      

    if (heap_listp == 0){
        mm_init();
    }
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE)                                          
        asize = 2*DSIZE;                                        
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); 

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {  
        place(bp, asize);              
#ifdef DEBUG
    check_heap();
#endif
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);                 
    //extendsize = asize;
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)  
        return NULL;                                  
    place(bp, asize);
#ifdef DEBUG
    check_heap();
#endif
    return bp;
} 

/* 
 * free - Free a block 
 */
void free(void *bp)
{
    if (bp == 0) 
        return;

    size_t size = GET_SIZE(HDRP(bp));
    if (heap_listp == 0){
        mm_init();
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
#ifdef DEBUG
    check_heap();
#endif
}

/*
 * realloc - Naive implementation of realloc
 */
void *realloc(void *ptr, size_t size)
{
    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    size_t asize;
    if (size <= DSIZE) asize = 2*DSIZE;
    else asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    size_t oldsize = GET_SIZE(HDRP(ptr));
    int sizediff = (int)(oldsize) - (int)(asize);
    void* nextptr = NEXT_BLKP(ptr);
    if (sizediff >= 2*DSIZE)
    {
        PUT(HDRP(ptr), PACK(asize, 1));
        PUT(FTRP(ptr), PACK(asize, 1)); 
        nextptr = NEXT_BLKP(ptr);
        PUT(HDRP(nextptr), PACK(oldsize - asize, 0));
        PUT(FTRP(nextptr), PACK(oldsize - asize, 0));
        coalesce(nextptr);
        return ptr;
    }
    if (sizediff >= 0 && sizediff < 2*DSIZE)
        return ptr;
#ifdef DEBUG
    check_heap();
#endif

    void *newptr = mm_malloc(size);
    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return 0;}
    /* Copy the old data. */
    memcpy(newptr, ptr, oldsize);
    /* Free the old block. */
    mm_free(ptr);

#ifdef DEBUG
    check_heap();
#endif
    return newptr;
}

void *calloc (size_t nmemb, size_t size)
{
    size_t bytes = nmemb * size;
    void *newptr;

    newptr = malloc(bytes);
    memset(newptr, 0, bytes);
#ifdef DEBUG
    check_heap();
#endif

    return newptr;
}

/* 
 * mm_checkheap - Check the heap for correctness. Helpful hint: You
 *                can call this function using mm_checkheap(__LINE__);
 *                to identify the line number of the call site.
 */
void mm_checkheap(int lineno)
{
    lineno = lineno;
}

void check_heap()
{
	char* rover = heap_listp;
	while (GET_SIZE(HDRP(rover)))
	{
		if (GET_SIZE(HDRP(rover)) % 8 != 0)
                {
                	printf("Wrong alignment!");
                        exit(1);
                }
                if (GET_SIZE(HDRP(rover)) != GET_SIZE(FTRP(rover)))
                {
                        printf("unmatched size!");
                        exit(1);
                }
                if (rover - free_p >= ((long)1)<<32)
                {
                        printf("Out of range!");
                        exit(1);
                }
        	rover = NEXT_BLKP(rover);
	}
	for (int i = 1 ; i <= LISTSIZE ; i ++)
	{
		rover = free_p + i*WSIZE;
		while (*rover)
		{
			rover = SUCC_FREE(rover);
			if (SUCC_FREE(rover) != free_p)
                        if (PREV_FREE(SUCC_FREE(rover)) != rover)
                	{
                        	printf("Unmatched pointer!");
                        	exit(1);
                	}
		}
	}
}

/* 
 * The remaining routines are internal helper routines 
 */

/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
static void *extend_heap(size_t words) 
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; 
    if ((long)(bp = mem_sbrk(size)) == -1)  
        return NULL;                                        

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ 

    /* Coalesce if the previous block was free */
    return coalesce(bp);                                          
}

/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
static void *coalesce(void *bp) 
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
        append_list(bp, size);
#ifdef DEBUG
    check_heap();
#endif
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        delete_list(NEXT_BLKP(bp), GET_SIZE(HDRP(NEXT_BLKP(bp))));
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size,0));
        PUT(FTRP(bp), PACK(size,0));
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        delete_list(PREV_BLKP(bp), GET_SIZE(FTRP(PREV_BLKP(bp))));
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
        delete_list(NEXT_BLKP(bp), GET_SIZE(HDRP(NEXT_BLKP(bp))));
        delete_list(PREV_BLKP(bp), GET_SIZE(FTRP(PREV_BLKP(bp))));
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp); 
    }
#ifdef DEBUG
    check_heap();
#endif

    append_list(bp, size);
    return bp;
}

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) {
        delete_list(bp, csize); 
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
        append_list(bp, csize-asize);
    }
    else {
        delete_list(bp, csize); 
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
static void *find_fit(size_t asize)
{
	unsigned int index = which_list(asize);
	for (unsigned i = index ; i <= LISTSIZE ; i ++)
	{
		unsigned int tmp = GET(free_p + (i*WSIZE));
		while (tmp)
		{	
                        if (asize <= GET_SIZE(HDRP(free_p + tmp))) return free_p + tmp;
			tmp = SUCC_REL(free_p + tmp);
		}
	}
	return 0;
}
static unsigned int which_list(size_t size)
{
        unsigned int asize = size>>5;
	unsigned int res = 1;
	while (asize)
	{
		asize = asize>>1;
		res += 1;
	}
	return MIN(res, LISTSIZE);
}
static void append_list(char* bp, size_t size)
{
	unsigned int index = which_list(size);
	unsigned int first = GET(free_p + (index*WSIZE));
	PUT(free_p + (index*WSIZE), bp - free_p);
	PUT(PREV(bp), index*WSIZE);
	PUT(SUCC(bp), first);
	if (first)
		PUT(PREV(first+free_p), bp-free_p);
}
static void delete_list(char* bp, size_t size)
{
	unsigned int index = which_list(size);
        unsigned int prev_rel = PREV_REL(bp);
        unsigned int succ_rel = SUCC_REL(bp);
        char* prev = free_p + prev_rel;
        char* succ = free_p + succ_rel;
	if (prev_rel == index*WSIZE)
		PUT(free_p + (index*WSIZE), succ_rel);
	else
		PUT(SUCC(prev), succ_rel);
	if (succ_rel)
		PUT(PREV(succ), prev_rel);
}
