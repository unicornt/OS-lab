#ifndef INC_SPINLOCK_H
#define INC_SPINLOCK_H

struct spinlock {
    volatile int locked;
};
void acquire(struct spinlock *);
void release(struct spinlock *);

struct mcslock {
    volatile struct mcslock *next;
    volatile int locked;
};
void mcs_acquire(struct mcslock *, struct mcslock *);
void mcs_release(struct mcslock *, struct mcslock *);

struct rwlock {
    volatile struct spinlock r, w;
    volatile int cnt;
};
void read_lock(struct rwlock *);
void read_unlock(struct rwlock *);
void write_lock(struct rwlock *);
void write_unlock(struct rwlock *);

#endif

