

.text
.globl start
start:

movl $(0xc0009000), %esp
pushl $over
pushl $main
ret
over:
jmp .
