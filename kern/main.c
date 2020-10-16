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
    uint64_t *p = kalloc();
    uint64_t *pgdir = kalloc();
    memset(pgdir, 0, PGSIZE);
    map_region(pgdir,  0, PGSIZE, V2P(p), 0);
    memset(p, 0xFF, PGSIZE);
    asm volatile("adr x9, pgdir");
    asm volatile("msr ttbr0_el1, x9");
    for(int i = 0;i  < PGSIZE; i++) {
        if(*((int*) i) != 0xFF) cprintf("error in %d\n", i);
    }
    while (1) ;
}
