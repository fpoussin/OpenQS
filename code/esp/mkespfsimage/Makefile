CC=gcc
CFLAGS=-I../../lib/heatshrink -I/usr/include -I/mingw/x86_64-w64-mingw32/include -std=gnu99
LDFLAGS= -lmman
OBJS=main.o heatshrink_encoder.o
TARGET=mkespfsimage

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)