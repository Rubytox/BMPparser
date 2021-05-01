CC=gcc
CFLAGS=-g
LDFLAGS=-g
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
TARGET=BMPparser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

.PHONY:
clean:
	rm -rf *.o
	rm -rf $(TARGET)
