# Makefile
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDFLAGS = -lncurses

TARGETS = video_player

.PHONY: all clean

all: $(TARGETS)

video_player: video_player.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGETS)