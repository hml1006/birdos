boot: $(OBJDIR)/boot.bin $(OBJDIR)/setup.bin
$(OBJDIR)/boot.bin: boot.asm
	$(ASM) boot.asm -o $(OBJDIR)/boot.bin
$(OBJDIR)/setup.bin: setup.asm
	$(ASM) setup.asm -o $(OBJDIR)/setup.bin