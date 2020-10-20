#include <stdint.h>
#include "types.h"
#include "string.h"
#include "mmu.h"
#include "memlayout.h"
#include "console.h"
#include "kalloc.h"

extern char end[];

/* 
 * Free page's list element struct.
 * We store each free page's run structure in the free page itself.
 */
struct run {
    struct run *next;
};

struct {
    struct run *free_list; /* Free list of physical pages */
} kmem;

void
alloc_init()
{
    free_range(end, P2V(PHYSTOP));
}

/* Free the page of physical memory pointed at by v. */
void
kfree(char *v)
{
    struct run *r;
    if ((uint64_t)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
        panic("kfree");
        
    /* Fill with junk to catch dangling refs. */
    memset(v, 1, PGSIZE);
    
    /* TODO: Your code here. */
    for(int i = 0;i < PGSIZE; i++) if((*(char*)(v + i)) != 0x1) panic("kfree memset check");
    r = (struct run*) v;
    r -> next = kmem.free_list;
    kmem.free_list = r;
    /* My code ends. */
}

void
free_range(void *vstart, void *vend)
{
    char *p;
    p = ROUNDUP((char *)vstart, PGSIZE);
    for (; p + PGSIZE <= (char *)vend; p += PGSIZE)
        kfree(p);
}

/* 
 * Allocate one 4096-byte page of physical memory.
 * Returns a pointer that the kernel can use.
 * Returns 0 if the memory cannot be allocated.
 */
char *
kalloc()
{
    /* TODO: Your code here. */
    if(kmem.free_list == NULL) return 0;
    struct run *p = kmem.free_list;
//    memset(p, 2, PGSIZE); // init page for debug. // init like this will overwrite p->next
    kmem.free_list = p -> next;
    memset(p, 2, PGSIZE);
    return (char *)p;
    /* My code ends. */
}

void
check_free_list()
{
    struct run *p;
    if (!kmem.free_list)
        panic("'kmem.free_list' is a null pointer!");

    for (p = kmem.free_list; p; p = p->next) {
        assert((void *)p > (void *)end);
    }
}
