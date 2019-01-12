CC = clang
CFLAGS=-Wall -Werror -Wno-pragma-pack
LDFLAGS=-lSDL2 -L.
BINARY=graphics

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
endif

all: graphics

graphics: main.o aiv_math.o aiv_rasterizer.o 
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c aiv_rasterizer.h
	$(CC) -c -o $@ $(CFLAGS) $<

aiv_math.o: aiv_math.c aiv_math.h
	$(CC) -c -o $@ $(CFLAGS) $<

aiv_rasterizer.o: aiv_rasterizer.c aiv_rasterizer.h aiv_math.h
	$(CC) -c -o $@ $(CFLAGS) $<
