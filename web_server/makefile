CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

