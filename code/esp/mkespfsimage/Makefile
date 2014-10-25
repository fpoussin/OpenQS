
CFLAGS=-I../lib/heatshrink -I/usr/include -I/mingw/x86_64-w64-mingw32/include -std=gnu99
OBJS=main.o heatshrink_encoder.o
TARGET=mkespfsimage

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)