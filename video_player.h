#ifndef VIDEO_PLAYER_H__
#define VIDEO_PLAYER_H__

void init_ui(WINDOW **main_win, WINDOW **cmd_win);
void destroy_ui(WINDOW **main_win, WINDOW **cmd_win);
void process_cmd(const char* cmd, WINDOW *main_win, WINDOW *cmd_win);

#endif // VIDEO_PLAYER_H__
