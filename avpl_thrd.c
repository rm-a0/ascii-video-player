#include <stdio.h>
#include <ncurses.h>

#include "avpl_thrd.h"

// Unpacks arguments and passes them into another function
void *video_thread(void *args) {
    thrd_args_t *thrd_args = (thrd_args_t*)args;

    char* filename = thrd_args->filename;
    WINDOW *win = thrd_args->win;

    play_video(filename, win);
    return NULL;
}