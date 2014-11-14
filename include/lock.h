#ifndef _LOCK_H
#define _LOCK_H
#include <stdbool.h>

typedef enum {UNLOCKED = 0, LOCKED = 1}lock_t;

//自旋锁
typedef enum {SPIN_UNLOCKED = 0, SPIN_LOCKED = 1}spin_lock_t;

//lock_t是不能重复加锁或者重复解锁的,不管操作成功或失败都是直接返回操作结果
static inline int lock(lock_t *lock_v)
{
	bool lock_ok = __sync_bool_compare_and_swap(lock_v, UNLOCKED, LOCKED);
	return lock_ok? 0 : -1;
}

static inline int unlock(lock_t *lock_v)
{
	bool unlock_ok = __sync_bool_compare_and_swap(lock_v, LOCKED, UNLOCKED);
	return unlock_ok? 0 : -1;
}

static void spin_lock(spin_lock_t *lock_v)
{
	while (!(__sync_bool_compare_and_swap(lock_v, SPIN_UNLOCKED, SPIN_LOCKED)));
}

static void spin_unlock(spin_lock_t *lock_v)
{
	while (!(__sync_bool_compare_and_swap(lock_v, SPIN_LOCKED, SPIN_UNLOCKED)));
}
#endif
