# Makefile
# ---------------------
# Author: Michal Repcik
# Date: 10.05.2024

#TODO
#	Add semaphores for resizing FIX SEGFAULT
#	Center video and adjust resizing (for heigh videos)
#	Add signals for segfaults
#	Reorganize code to headerfiles

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
LDPATHS = -L/usr/lib/x86_64-linux-gnu
INCPATHS = -I/usr/include
LDFLAGS = -lncurses -lavformat -lavcodec -lavutil -lrt -lpthread

SRCS = 				\
    video_player.c 	\
    media_proc.c 	\
    avpl_thrd.c 	\
    avpl_sem.c 		\
    avpl_ui.c 		\
    avpl_flags.c 	\
    ascii_conv.c    \
    avpl_cmd.c

OBJS = $(SRCS:.c=.o)

TARGETS = video_player

.PHONY: all run clean git_upload

all: $(TARGETS)

# Target: video_player executable
video_player: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(INCPATHS) $(LDPATHS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCPATHS)
	
run: 
	./video_player

clean:
	rm -f $(TARGETS) $(OBJS)