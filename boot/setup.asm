

[BITS 16]
;setup模块放到252K位置
SETUP_ADDR equ 252*1024
mov ax, cs
mov ds, ax
mov ss, ax
mov sp, 0x400

;设置显卡显示模式为字符模式80*25
mov ax, 0x4f02
mov bx, 0x108
int 10h

;加载内核代码到16K处, 即第5页内存
load_kernel:
KERNEL_ADDR equ 16*1024
mov ax, KERNEL_ADDR/16
mov es, ax
mov dx, word 0000h
mov cx, word 0006h	;从第6扇区开始加载,共加载13个扇区
mov bx, word 0h
mov ah, byte 02h
mov al, byte 13
int 13h
mov ax, (KERNEL_ADDR+13*512)/16
mov es, ax
mov dx, word 0001h
mov cx, word 0001h	;第一磁道第一扇区开始
mov bx, word 0h
mov ah, byte 02h
mov al, byte 18
int 13h

;关中断,清标志位
cli
cld

;第3K是页表,地址是2*4096 ,  第4K是页目录， 地址是3*4096

;物理地址初始地址为0, 但是加上末尾的权限位为7, 
PAGE_TABLE_ADDR equ 2*4096
mov ax, 0
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ecx, 1024
mov eax, 7
mov esi, PAGE_TABLE_ADDR
set_page_table:
mov [esi], eax
add eax, 4096
add esi, 4
dec ecx
jnz set_page_table

;页目录的第 1 项和 768 项映射到同一张页表，768项为虚拟地址3G 的开始处
PAGE_DIR_ADDR equ 3*4096
mov eax, 0
mov esi, PAGE_DIR_ADDR+4*768
add eax, PAGE_TABLE_ADDR+7
mov [esi], eax
mov esi, PAGE_DIR_ADDR
mov [esi], eax
mov ebx, PAGE_DIR_ADDR
mov cr3, ebx

;中断重新编程,重新设置irq信号线
mov al, 0x11
out 0x20, al
jmp $+2		;延时作用
out 0xa0, al
jmp $+2
mov al, 0x20
out 0x21, al
jmp $+2
mov al, 0x28
out 0xa1, al
jmp $+2
mov al, 0x4
out 0x21, al
jmp $+2
mov al, 0x2
out 0xa1, al
jmp $+2
mov al, 0x1
out 0x21, al
jmp $+2
out 0xa1, al
jmp $+2
mov al, 0xff
out 0x21, al
jmp $+2
out 0xa1, al

;进入保护模式
;保护模式开启前,搬移gdt到物理内存2K
;3G-4G映射到内核空间
;内核第二页放gdt
mov ax, cs
mov ds, ax
mov ax, 4096/16
mov es, ax
mov cx, 24
xor di, di
mov si, gdt_addr
rep movsw

lgdt [gdt_48]

;加载idtr
lidt [idt_48]
;使能A20地址线
enable_a20:
in al, 92h
or al, 0x02
out 92h, al


;开启分页并打开保护模式
mov ebx, cr0
or  ebx, 0x80000001
mov cr0, ebx

;设置段选择子
mov ax, 16
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

;真正跳入保护模式
jmp dword 8:0xc0004000

;gdt begin
gdt_addr:
	dq 0x0000000000000000	;dummy
	dq 0x00cf9a000000ffff	;kernel 4GB code at 0x00000000
	dq 0x00cf92000000ffff	;kernel 4GB data at 0x00000000
	dq 0x00cffa000000ffff	;user 4GB code at 0x00000000
	dq 0x00cff2000000ffff	;user 4GB data at 0x00000000
	dq 0x0000000000000000	;reserved for further use
gdt_48:
	dw $-gdt_addr-1	;gdt表长度
	dd 0xc0001000		;gdt表基地址是4096
idt_48:
	dw 256*8-1	;idt表长度
	dd 0xc0000000		;基地址 0
