#include <stdint.h>

#include "string.h"
#include "console.h"
#include "kalloc.h"
#include "kpgdir.c"
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
    map_region(kpgdir, 0, 1024, p, 0);
    cprintf("%d %d\n", *pgdir_walk(kpgdir, p, 0), *p);
    vm_free(kpgdir, 0);
    cprintf("%d %d\n", *pgdir_walk(kpgdir, p, 0), *p);
    while (1) ;
}
