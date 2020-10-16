#include <stdint.h>

#include "arm.h"
#include "string.h"
#include "console.h"
#include "kalloc.h"
<<<<<<< HEAD
#include "trap.h"
#include "timer.h"
=======
#include "kpgdir.c"
#include "kalloc.h"
#include "vm.h"
>>>>>>> add test code

void
main()
{
    /*
     * Before doing anything else, we need to ensure that all
     * static/global variables start out zero.
     */

    extern char edata[], end[], vectors[];

    /* TODO: Use `memset` to clear the BSS section of our program. */
    memset(edata, 0, end - edata);    
    /* TODO: Use `cprintf` to print "hello, world\n" */
    console_init();
    alloc_init();
    cprintf("Allocator: Init success.\n");
    check_free_list();

    irq_init();

    lvbar(vectors);
    timer_init();

    while (1) ;
}
