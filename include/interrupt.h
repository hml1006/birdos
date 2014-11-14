#ifndef _INTERRUPT_H

#define sti()	__asm__ __volatile("sti\n");	//开中断
#define cli()	__asm__ __valatile("cli\n");	//关中断

#endif
