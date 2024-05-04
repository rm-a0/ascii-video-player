/* avpl_thrd.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    06.03.2024
*/
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#include "avpl_thrd.h"
#include "media_proc.h"

void *video_thread(void *args) {
    // Unpack arguments
    thrd_args_t *thrd_args = (thrd_args_t*)args;
    char* filename = thrd_args->filename;
    WINDOW *win = thrd_args->win;

    // Call play video function
    play_video(filename, win);
    return NULL;
}

thrd_args_t* init_thrd_args(WINDOW* win, char* filename) {
    // Allocate memory for the struct
    thrd_args_t *thrd_args = malloc(sizeof(thrd_args_t));
    // Check memory allocation
    if (thrd_args == NULL) {
        return NULL;
    }
    // Initialize varaibles within the struct
    thrd_args->filename = filename;
    thrd_args->win = win;

    return thrd_args;
}