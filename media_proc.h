#ifndef MEDIA_PROC_H__
#define MEDIA_PROC_H__

#include <libavformat/avformat.h>   // Lib for multimedia containers
#include <libavcodec/avcodec.h>     // Lib for multimedia codecs

void play_video(char *vid_title, WINDOW *main_win);
void frame_to_ascii(WINDOW *win, AVFrame *frame, int w_height, int w_width);
void display_error(WINDOW *win, const char *msg);

#endif // MEDIA_PROC_H__