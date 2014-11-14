[BITS 16]
;本代码将会被BIOS加载到内存的0x7c00h处
org 07c00h
mov ax, cs
mov ds, ax

;从软盘加载模块setup到物理内存起始位置252K处
load_setup:
SETUP_ADDR equ 252*1024
mov ax, SETUP_ADDR/16
mov es, ax
mov dx, word 0000h	;dh磁头号,dl驱动器号
mov cx, word 0002h	;ch磁道号的低8位,cl(0-5开始扇区,6-7磁道号的高两位)
mov bx, word 0h		;es:bx: 目的地址。如果出错则CF标志置位
mov ah, byte 02h	;功能号0x02 = 读磁盘数据到内存
mov al, byte 4		;al是需要读取的扇区数量,软盘每磁道有18个扇区
int 13h

;跳到setup处
jmp word SETUP_ADDR/16:0

;字符串信息
times 510-($-$$) db 0
dw 0xaa55
