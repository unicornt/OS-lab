#ifndef KERN_VM_H
#define KERN_VM_H

#include "memlayout.h"

void vm_free(uint64_t *, int);
int map_region(uint64_t *, void *, uint64_t , uint64_t , int64_t );

#endif /* !KERN_VM_H */