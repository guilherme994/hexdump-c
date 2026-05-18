CC := gcc
CFLAGS := -Wall -Wextra -std=c11
TARGET := hexdump
SRCDIR := src
OBJS := $(SRCDIR)/main.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
