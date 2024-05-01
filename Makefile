# Makefile
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

#TODO
#	Center video and adjust resizing (for heigh videos)
#	Add semaphores for resizing
#	Add signals for segfaults
#	Add pause
#	Reorganize code to headerfiles

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
LDPATHS = -L/usr/lib/x86_64-linux-gnu
INCPATHS = -I/usr/include
LDFLAGS = -lncurses -lavformat -lavcodec -lavutil -lrt

TARGETS = video_player

.PHONY: all run clean

all: $(TARGETS)

video_player: video_player.c media_proc.c
	$(CC) $(CFLAGS) $^ -o $@ $(INCPATHS) $(LDPATHS) $(LDFLAGS)

run: 
	./video_player

clean:
	rm -f $(TARGETS)