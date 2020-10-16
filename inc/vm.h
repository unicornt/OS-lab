#ifndef KERN_VM_H
#define KERN_VM_H

#include "memlayout.h"

void vm_free(uint64_t *, int);
static uint64_t * pgdir_walk(uint64_t *, const void *, int64_t );

#endif /* !KERN_VM_H */