#ifndef _ASM_H_
#define _ASM_H_
#include <stdint.h>

#define GDT_LEN		47
#define GDT_ADDR	0xc0001000
inline void lgdt(uint16_t gdt_length, uint32_t gdt_address)
{
	struct gdt_48 {
		uint16_t gdt_len;
		uint32_t gdt_addr;
	};
	struct gdt_48 gdt_48_tmp;
	gdt_48_tmp.gdt_len = gdt_length;
	gdt_48_tmp.gdt_addr = gdt_address;

	__asm__ __volatile__ (
			"lgdt %0"
			:
			:
			"m"(gdt_48_tmp)
			);
}

#define IDT_LEN		(256 * 8 - 1)
#define IDT_ADDR	0xc0000000
inline void lidt(uint16_t idt_length, uint32_t idt_address)
{
	struct idt_48 {
		uint16_t idt_len;
		uint32_t idt_addr;
	};
	struct idt_48 idt_48_tmp;
	idt_48_tmp.idt_len = idt_length;
	idt_48_tmp.idt_addr = idt_address;

	__asm__ __volatile__ (
			"lidt %0"
			:
			:
			"m"(idt_48_tmp)
			);
}

inline void cli()
{
	__asm__ __volatile__ (
			"cli"
			);
}

inline void sti()
{
	__asm__ __volatile__ (
			"sti"
			);
}

#endif
