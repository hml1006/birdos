init: $(OBJDIR)/head.o $(OBJDIR)/main.o
$(OBJDIR)/head.o: head.s
	$(CC) $(CFLAGS) head.s -o $(OBJDIR)/head.o
$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDE) main.c -o $(OBJDIR)/main.o