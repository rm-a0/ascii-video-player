/* media_proc.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#ifndef MEDIA_PROC_H__
#define MEDIA_PROC_H__

#include <ncurses.h>    // Lib for terminal operations

#include "avpl_sem.h"
#include "avpl_ui.h"

/* Function: play_media
 * --------------------
 * Separates video into frames and passes them to ascii_conv function
 * 
 * Parameters
 * ----------
 * vid_title - path to the video that should be played
 * wins - pointer to a struct containing windows
 * sems - struct containing semaphores
 * 
 * Return value
 * ------------
 * int - indicates state in which the function ended
*/
int play_media(char *vid_title, wins_t* wins, sems_t *sems);

/* Function: display_error
 * -----------------------
 * Displays error message on specified window
 * 
 * Parameters
 * ----------
 * win - pointer to a window where the message should be displayed
 * msg - message that should be displayed
 * 
 * Return value
 * ------------
 * void
*/
void display_error(WINDOW *win, const char *msg);

#endif // MEDIA_PROC_H__