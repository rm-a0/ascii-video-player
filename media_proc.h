/* media_proc.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    06.04.2024
*/
#ifndef MEDIA_PROC_H__
#define MEDIA_PROC_H__

#include <ncurses.h>                // Lib for terminal operations

void play_video(char *vid_title, WINDOW *main_win);
void display_error(WINDOW *win, const char *msg);

#endif // MEDIA_PROC_H__