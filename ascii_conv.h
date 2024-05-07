/* ascii_conv.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    07.04.2024
*/
#ifndef ASCII_CONV_H__
#define ASCII_CONV_H__

#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers

void frame_to_ascii(WINDOW *win, AVFrame *frame, int w_height, int w_width);

#endif // ASCII_CONV_H__