#include <stdint.h>

#include "mmu.h"
#include "string.h"
#include "console.h"
#include "kalloc.h"
#include "vm.h"

void
main()
{
    /*
     * Before doing anything else, we need to ensure that all
     * static/global variables start out zero.
     */

    extern char edata[], end[];

    /* TODO: Use `memset` to clear the BSS section of our program. */
    memset(edata, 0, end - edata);    
    /* TODO: Use `cprintf` to print "hello, world\n" */
    console_init();
    alloc_init();
    cprintf("Allocator: Init success.\n");
    check_free_list();
    void *p = kalloc();
    void *pgdir = kalloc();
    cprintf("alloc finish");
    memset(pgdir, 0, PGSIZE);
    map_region(pgdir, (void*)0, (uint64_t)PGSIZE, V2P(p), 0);
    memset(p, 0xFF, PGSIZE);
    asm volatile("msr ttbr0_el1, %[x]": : [x]"r"(pgdir));
    for(uint64_t i = 0;i  < PGSIZE; i++) {
        if((*(int*)i) != 0xFF) cprintf("error in %d\n", i);
    }
    cprintf("testing finish");
    while (1) ;
}
