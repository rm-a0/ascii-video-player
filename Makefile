# Makefile
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDPATHS = -L/usr/lib/x86_64-linux-gnu
INCPATHS = -I/usr/include 
LDFLAGS = -lncurses -lavformat -lavcodec -lavutil

TARGETS = video_player

.PHONY: all run clean

all: $(TARGETS)

video_player: video_player.c
	$(CC) $(CFLAGS) $^ -o $@ $(INCPATHS) $(LDPATHS) $(LDFLAGS)

run: 
	./video_player

clean:
	rm -f $(TARGETS)