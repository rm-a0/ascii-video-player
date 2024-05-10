/* avpl_cmd.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#ifndef AVPL_CMD_H__
#define AVPL_CMD_H__

#include "avpl_sem.h"
#include "avpl_flags.h"

/* Function: pause_vid
 * --------------------
 * Pauses the video only if the video is playing
 * 
 * Parameters
 * ----------
 * flags - struct containing flags
 * sems - struct containing semaphores
 * 
 * Return value
 * ------------
 * void
*/
void pause_vid(sems_t *sems, flags_t *flags);

/* Function: resume_vid
 * --------------------
 * Resumes the video only if the video is not playing
 * 
 * Parameters
 * ----------
 * flags - struct containing flags
 * sems - struct containing semaphores
 * 
 * Return value
 * ------------
 * void
*/
void resume_vid(sems_t *sems, flags_t *flags);

#endif // AVPL_CMD_H__