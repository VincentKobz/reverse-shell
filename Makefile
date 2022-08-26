CC=gcc
CFLAGS= -std=gnu99 -Wall -Wextra -Werror -pedantic
OBJS=reverse.o
TARGET=reverse

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

.PHONY:
	clean

clean:
	$(RM) $(TARGET) $(OBJS)

