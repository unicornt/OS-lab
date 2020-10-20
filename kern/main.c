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
    memset(pgdir, 0, PGSIZE);
    map_region(pgdir, (void*)0, (uint64_t)PGSIZE, V2P(p), 0);
    cprintf("pgdir %x  p %x\n", pgdir, p);
    memset(p, 0xFF, PGSIZE);
    asm volatile("msr ttbr0_el1, %[x]": : [x]"r"(V2P(pgdir))); 
    cprintf("start testing map_region\n");
    for(uint64_t i = 0;i  < PGSIZE; i++) {
        if((*((char*)i)) != 0xFF){
            cprintf("error in %d : %x\n", i, *((char*)i));
        }
    }
    asm volatile("mrs x9, ttbr1_el1"); 
    asm volatile("msr ttbr0_el1, x9"); 
    cprintf("finish testing map_region\n");
    cprintf("start testing vm_free\n");
    vm_free(pgdir, 0);
    cprintf("p %x\n", p);
    for(int i = 8;i < PGSIZE; i++) { // first 8 bytes are next free list information
        if((*((char*)((uint64_t)p + i))) != 0x1) {
            cprintf("error in %d : %x\n", i, *(char*)((uint64_t)p +i ));
        }
    }
    cprintf("finish testing vm_free\n");
    while (1) ;
}
