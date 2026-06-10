CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c11 -Iinclude
SRCS    = src/produto.c main/main.c
TARGET  = programa

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
