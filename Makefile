ASM=nasm
CC=gcc
LD=ld
PWD:=$(shell pwd)
OBJDIR:=$(PWD)/obj
CFLAGS+=-c -m32 -fno-builtin -fno-stack-protector
INCLUDE+=-I $(PWD)/include
LDFLAGS+=-e start -melf_i386 --oformat binary -Ttext 0xc0004000
export

all: birdos image

birdos: $(OBJDIR)
	$(MAKE) -C boot
	$(MAKE) -C init
	$(MAKE) -C driver
	$(MAKE) -C lib
	$(LD) $(LDFLAGS) -o $(OBJDIR)/head.bin $(OBJDIR)/head.o $(OBJDIR)/main.o $(OBJDIR)/screen.o $(OBJDIR)/printk.o $(OBJDIR)/string.o

$(OBJDIR):
	mkdir $(OBJDIR)
image: $(OBJDIR)/boot.bin $(OBJDIR)/setup.bin $(OBJDIR)/head.bin
	dd if=$(OBJDIR)/boot.bin of=birdos.img seek=0 bs=512 count=1
	dd if=$(OBJDIR)/setup.bin of=birdos.img seek=1 bs=512 count=4
	dd if=$(OBJDIR)/head.bin of=birdos.img seek=5 bs=512 count=31
	dd if=/dev/zero of=birdos.img seek=36 bs=512 count=2844

clean:
	-rm -rf $(OBJDIR)/
	-rm -f $(PWD)/birdos.img
