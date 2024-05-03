/* avpl_thrd.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.03.2024
*/
#include <stdio.h>
#include <ncurses.h>

#include "avpl_thrd.h"

void *video_thread(void *args) {
    // Unpack arguments
    thrd_args_t *thrd_args = (thrd_args_t*)args;
    char* filename = thrd_args->filename;
    WINDOW *win = thrd_args->win;

    // Call play video function
    play_video(filename, win);
    return NULL;
}