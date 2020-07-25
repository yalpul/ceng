CC = gcc
CFLAGS = -O3 -c -pedantic -Wall -Wno-unused-result
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)
OUT = server


all: $(OBJECTS) $(OUT)
    

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $(OBJECTS)
	strip $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OUT) $(OBJECTS)
