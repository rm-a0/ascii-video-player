#ifndef MEDIA_PROC_H__
#define MEDIA_PROC_H__

void play_video(const char *vid_title, WINDOW *main_win);
void frame_to_ascii(WINDOW *win, AVFrame *frame);
void display_error(WINDOW *win, const char *msg);

#endif // MEDIA_PROC_H__