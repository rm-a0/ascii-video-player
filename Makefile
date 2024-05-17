# Makefile
# ---------------------
# Author: Michal Repcik
# Date:	16.05.24

#TODO
#   Add color to video
#	Center video and adjust resizing (for heigh videos)

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