/* vectors.S send all traps here. */
.global alltraps
alltraps:
    /*
     * Build your trap frame.
     * Hint:
     * 1. Use stp/ldp in favor of str/ldr to maintain stack alignment
          For example, `stp x1, x2, [sp, #-16]!` is equivalent to 
          first `push x2` and then `push x1`. Be careful about the order.
     * 2. Use mrs/msr to move from/to system registers such as
     *    ELR_EL1, SPSR_EL1, and SP_EL0.
     */

    /* TODO: Your code here. */
    stp x30, x0, [sp, #-16]!
    stp x18, x17, [sp, #-16]!
    stp x16, x15, [sp, #-16]!
    stp x14, x13, [sp, #-16]!
    stp x12, x11, [sp, #-16]!
    stp x10, x9, [sp, #-16]!
    stp x8, x7, [sp, #-16]!
    stp x6, x5, [sp, #-16]!
    stp x4, x3, [sp, #-16]!
    stp x2, x1, [sp, #-16]!
    mrs x10, SP_EL0
    mrs x11, ELR_EL1
    stp x11, x10, [sp, #-16]!
    mrs x10, SPSR_EL1
    stp x11, x10, [sp, #-16]!
    /* My code ends here. */
    /*
     * Call trap(struct *trapframe).
     * Hint: The first argument is a stack pointer.
     */

    /* TODO: Your code here. */
    mov x0, sp
    bl trap
    /* My code ends here */

/* Return falls through to trapret. */
.global trapret
trapret:
    /*
     * Restore registers.
     * Hint: `ldp x1, x2, [sp], #16` is equivalent to first `pop x1`
     * and then `pop x2`.
     */

    /* TODO: Your code here. */
    ldp x11, x10, [sp], #16
    msr SPSR_EL1, x10
    ldp x11, x10, [sp], #16
    msr ELR_EL1, x11
    msr SP_EL0, x10
    ldp x2, x1, [sp], #16
    ldp x4, x3, [sp], #16
    ldp x6, x5, [sp], #16
    ldp x8, x7, [sp], #16
    ldp x10, x9, [sp], #16
    ldp x12, x11, [sp], #16
    ldp x14, x13, [sp], #16
    ldp x16, x15, [sp], #16
    ldp x18, x17, [sp], #16
    ldp x30, x0, [sp], #16
    /* My code ends here */
    eret
