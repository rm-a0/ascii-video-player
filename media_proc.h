/* media_proc.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	27.05.2024
*/
#ifndef MEDIA_PROC_H__
#define MEDIA_PROC_H__

#include <ncurses.h>    // Lib for terminal operations

#include "avpl_sem.h"
#include "avpl_flags.h"
#include "avpl_ui.h"
#include <libavcodec/avcodec.h>

/* Function: play_media
 * --------------------
 * Separates video into frames and passes them to ascii_conv function
 * Function runs indefinitely untill flag is set (either by play or end function)
 * 
 * Parameters
 * ----------
 * vid_title - path to the video that should be played
 * wins - pointer to a struct containing windows
 * sems - struct containing semaphores
 * flags - struct containing flags
 * 
 * Return value
 * ------------
 * int - indicates state in which the function ended
*/
int play_media(char *vid_title, wins_t* wins, sems_t *sems, flags_t* flags);

#endif // MEDIA_PROC_H__
