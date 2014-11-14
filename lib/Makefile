lib: $(OBJDIR)/printk.o $(OBJDIR)/string.o
$(OBJDIR)/printk.o: $(PWD)/include/screen.h $(PWD)/include/printk.h $(PWD)/lib/printk.c
	$(CC) $(CFLAGS) $(INCLUDE) printk.c -o $(OBJDIR)/printk.o
$(OBJDIR)/string.o: $(PWD)/include/string.h $(PWD)/lib/string.c
	$(CC) $(CFLAGS) $(INCLUDE) string.c -o $(OBJDIR)/string.o
