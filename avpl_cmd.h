/* avpl_cmd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#ifndef AVPL_CMD_H__
#define AVPL_CMD_H__

#include "avpl_sem.h"
#include "avpl_flags.h"
#include "avpl_thrd.h"
#include "avpl_ui.h"

/* Function: play_vid
 * ------------------
 * Function that plays specified media
 * Allocates memory for thrd_args_t
 * Creates new thread and passes arguments to it
 * Sets flags
 * 
 * Parameters
 * ----------
 * filename - path to the media
 * thrd_args - pointer to unitnitialized struct (will be malloced inside function)
 * wins - pointer to struct containing windows
 * flags - struct containing flags
 * sems - struct containing semaphores
 * thread - pointer to empty thread
 * 
 * Return value
 * ------------
 * if everything run successfully, return 0
*/
int play_vid(char* filename, thrd_args_t* thrd_args,  wins_t* wins, flags_t* flags, sems_t* sems, pthread_t* thread);

/* Function: pause_vid
 * --------------------
 * Pauses the video only if the video is playing
 * 
 * Parameters
 * ----------
 * sems - struct containing semaphores
 * flags - struct containing flags
 * 
 * Return value
 * ------------
 * if video was sucesfully paused, return 0
*/
int pause_vid(sems_t *sems, flags_t *flags);

/* Function: resume_vid
 * --------------------
 * Resumes the video only if the video is not playing
 * 
 * Parameters
 * ----------
 * sems - struct containing semaphores
 * flags - struct containing flags
 * 
 * Return value
 * ------------
 * if video was sucesfully resumed, return 0
*/
int resume_vid(sems_t *sems, flags_t *flags);

/* Function: display_help
 * ----------------------
 * Displays instructions and informations about all avaliable commands
 * 
 * Parameters
 * ----------
 * wins - struct containing windows
 * 
 * Return value
 * ------------
 * void
*/
void display_help(wins_t *wins);

#endif // AVPL_CMD_H__