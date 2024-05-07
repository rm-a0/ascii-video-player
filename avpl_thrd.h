/* avpl_thrd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    06.04.2024
*/
#ifndef AVPL_THRD_H__
#define AVPL_THRD_H__

#include <pthread.h>
#include <ncurses.h>

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
    sems_t* sems;
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

/* Function: init_thrd_args
 * ------------------------
 * Dynammically allocates memory for thrd_args_t struct
 * Assigns parameters to variables within the struct
 * 
 * Parameters
 * ----------
 * win - pointer to a window
 * filename - name of the media file
 * 
 * Return value
 * ------------
 * pointer to a thrd_args_t struct
*/
thrd_args_t* init_thrd_args(WINDOW* win, char *filename, sems_t *sems);

#endif // AVPL_THRD_H__