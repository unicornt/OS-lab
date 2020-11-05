#include <stdint.h>

#include "arm.h"
#include "string.h"
#include "console.h"
#include "kalloc.h"
#include "trap.h"
#include "timer.h"
#include "spinlock.h"

static int ex = -1;
static struct spinlock lk = {0};
void
main()
{
    /*
     * Before doing anything else, we need to ensure that all
     * static/global variables start out zero.
     */

    extern char edata[], end[], vectors[];
    /*
     * Determine which functions in main can only be
     * called once, and use lock to guarantee this.
     */
    /* TODO: Your code here. */

    /* TODO: Use `memset` to clear the BSS section of our program. */
    acquire(&lk);
    if(ex == -1){    
        ex = cpuid();
    }
    release(&lk);
    if(ex == cpuid()){
        memset(edata, 0, end - edata);
    /* TODO: Use `cprintf` to print "hello, world\n" */
        console_init(); // operation on memory, only need to excute once
        alloc_init(); // same as above
        cprintf("Allocator: Init success.\n");
        check_free_list(); // same as above
        irq_init(); // the same
    }
    lvbar(vectors); // operation about system register, each cpu has to excute
    timer_init();  // operation about system register and different parts of memory 

    cprintf("CPU %d: Init success.\n", cpuid());

    while (1) ;
}
