/* avpl_cmd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
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
 * thrd_args - pointer reference to unitnitialized struct (will be malloced inside function)
 * wins - pointer to struct containing windows
 * flags - struct containing flags
 * sems - struct containing semaphores
 * thread - pointer to empty thread
 * 
 * Return value
 * ------------
 * if everything run successfully, return 0
*/
int play_vid(char* filename, thrd_args_t** thrd_args,  wins_t* wins, flags_t* flags, sems_t* sems, pthread_t* thread);

/* Function: end_vid
 * ------------------
 * Function that ends video that is currently playing
 * Joins video thread with main thread
 * Frees allocated memory for thrd_args
 * Resets flags that were set in play_vid function
 * 
 * Parameters
 * ----------
 * thrd_args - pointer to initialized struct (will be freed in this function)
 * sems - struct containing semaphores
 * wins - pointer to struct containing windows
 * flags - struct containing flags
 * thread - pointer to a thread
 * 
 * Return value
 * ------------
 * if video ended sucesfully, return 0
*/
int end_vid(thrd_args_t* thrd_args, sems_t* sems, wins_t* wins, flags_t* flags, pthread_t* thread);

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

/* Function: change_speed
 * ----------------------
 * Changes speed multiplier inside the flags_t struct
 * 
 * Parameters
 * ----------
 * speed - pointer to sting containing speed
 * flags - struct containing flags
 * 
 * Return value
 * ------------
 * if speed was sucesfully changed, return 0
*/
int change_speed(char* speed, flags_t* flags);

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