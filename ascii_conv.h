/* ascii_conv.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    07.04.2024
*/
#ifndef ASCII_CONV_H__
#define ASCII_CONV_H__

#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers

/* Function: frame_to_ascii
 * ------------------------
 * Function that converts frame to ascii art
 * 
 * Parameters
 * ----------
 * win - window where the frame is supposed to be displayed
 * frame - video frame that needs to be converted
 * w_height - height of the window (win)
 * w_width - width of the window (win)
 * 
 * Return value
 * ------------
 * void
*/
void frame_to_ascii(WINDOW *win, AVFrame *frame, int w_height, int w_width);

#endif // ASCII_CONV_H__