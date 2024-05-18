/* avpl_thrd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
*/
#ifndef AVPL_THRD_H__
#define AVPL_THRD_H__

#include <pthread.h>
#include <ncurses.h>

#include "avpl_sem.h"
#include "avpl_ui.h"
#include "avpl_flags.h"

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
    wins_t* wins;
    sems_t* sems;
    flags_t* flags;
} thrd_args_t;

/* Function: video_thread
 * ----------------------
 * This function is repsonsible for media playback in antoher thread
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
 * sems - struct containing semaphores
 * flags - struct containing flags
 * 
 * Return value
 * ------------
 * pointer to a thrd_args_t struct
*/
thrd_args_t* init_thrd_args(wins_t* wins, char *filename, sems_t *sems, flags_t* flags);

/* Function: destroy_thrd_args
 * ---------------------------
 * Frees dynamically allocated memory for thrd_args_t struct
 * 
 * Parameters
 * ----------
 * thrd_args - pointer to a struct
 * 
 * Return value
 * ------------
 * void
*/
void destroy_thrd_args(thrd_args_t* thrd_args);

#endif // AVPL_THRD_H__