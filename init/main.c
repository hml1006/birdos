#include <screen.h>
#include <printk.h>
#include <asm.h>

int main()
{
	cli();
	lgdt(GDT_LEN, GDT_ADDR);
	lidt(IDT_LEN, IDT_ADDR);
	uint32_t *pg_table = (uint32_t *)(4096*3+0xc0000000);
	int i;
	for (i = 0; i < 20; i++) {
		printk("page %d : %u \n", i, *pg_table);
		pg_table++;
	}
	return 0;
}
