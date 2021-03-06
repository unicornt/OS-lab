#include <stdint.h>

#include "string.h"
#include "console.h"

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
    cprintf("hello, world\n");
    while (1) ;
}
