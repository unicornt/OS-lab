#include "arm.h"
#include "spinlock.h"
#include "console.h"

void 
acquire(struct spinlock *lk)
{
    while (lk->locked || __atomic_test_and_set(&lk->locked, __ATOMIC_ACQUIRE))
        ;
}

void 
release(struct spinlock *lk)
{
    if (!lk->locked)
        panic("release: not locked\n");
    __atomic_clear(&lk->locked, __ATOMIC_RELEASE);
}

void
mcs_acquire(struct mcslock *lk, struct mcslock *i)
{
    i->next = i->locked = 0;
    volatile struct mcslock *pre = __sync_lock_test_and_set(&lk->next, i);
    if(pre) {
        i->locked = 1;
        pre->next = i;
    }
    while(i->locked);
}

void
mcs_release(struct mcslock *lk, struct mcslock *i)
{
    if(i->next == 0)
        if(__sync_val_compare_and_swap(&lk->next, i, __ATOMIC_RELEASE) == i)
            return;
    while(i->next == 0) ;
    i->next->locked = 0;
}

void
read_lock(struct rwlock *lk)
{
    acquire(&lk->r);
    if(lk->cnt++==0)
        acquire(&lk->w);
    release(&lk->r);
}

void
read_unlock(struct rwlock *lk)
{
    acquire(&lk->r);
    if(--lk->cnt==0)
        release(&lk->w);
    release(&lk->r);
}

void
write_lock(struct rwlock *lk)
{
    acquire(&lk->w);
}

void
write_unlock(struct rwlock *lk)
{
    release(&lk->w);
}
