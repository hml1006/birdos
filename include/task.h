#ifndef _TASK_H
#define _TASK_H

#include <stdint.h>

//task state
#define TASK_RUNNING 0
#define TASK_RUNABLE 1
#define TASK_STOPPED 2

struct tss_struct {
	uint32_t prev_task_link;
	uint32_t esp0, ss0;
	uint32_t esp1, ss1;
	uint32_t esp2, ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax, ecx, edx, ebx;
	uint32_t esp, ebp;
	uint32_t esi, edi;
	uint32_t es, cs, ss, ds, fs, gs;
	uint32_t ldt;
	uint32_t io_bitmap;
};

struct task_struct {
	struct tss_struct tss;
	uint32_t tss_entry;
	uint32_t task_state;
	int32_t priority;
	struct task_struct *next;
};

#endif
