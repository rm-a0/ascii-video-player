/* avpl_thrd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.03.2024
*/
#ifndef AVPL_THRD_H__
#define AVPL_THRD_H__

#include <pthread.h>    // threads
#include <ncurses.h>    // WINDOW

#include "avpl_sem.h"

/* Struct: thrd_args
 * -----------------
 * Structure holding all arguments necessary
 * for creating video thread
 * 
 * Variables
 * ---------
 * filename - path to a video that should be played
 * win - pointer to a window where the media should be played
 * sems - struct containing semaphores
*/
typedef struct thrd_args {
    char *filename;
    WINDOW *win;
    // sems_t sems;
} thrd_args_t;

/* Function: video_thread
 * ----------------------
 * This function is repsonsible for video playback in antoher thread
 * 
 * Parameters
 * ----------
 * args - generic pointer to necessary arguments (thrd_args_t)
 * 
 * Return value
 * ------------
 * generic void pointer
*/
void *video_thread(void *args);

#endif // AVPL_THRD_H__