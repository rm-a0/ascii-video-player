#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers
#include <libavcodec/avcodec.h>     // Lib for multimedia codecs

#include "video_player.h"
#include "media_proc.h"

// Constants
#define CMD_WIN_HEIGHT 3
// Initialize windows
WINDOW *main_win;
WINDOW *cmd_win;

// Function that handles video thread
void *video_thread(void *args) {
    const char *vid_name = (const char *)args;
    play_video(vid_name, main_win, cmd_win);  // Start video playback
    return NULL;
}

// Function for processing arguments in cmd_win
void process_cmd(const char* cmd, WINDOW *main_win, WINDOW *cmd_win) {
    switch (cmd[0]) {
        case 'q':
            if (strcmp(cmd, "quit") == 0) {
                destroy_ui(&main_win, &cmd_win);
                exit(EXIT_SUCCESS);
            }
            break;
        case 'p':
            if (strcmp(cmd, "play") == 0) {
                // Start video playback in a new thread
                pthread_t vid_thread;
                const char *vid_filename = "eva_op.mp4";
                
                if (pthread_create(&vid_thread, NULL, video_thread, (void *)vid_filename) != 0) {
                    fprintf(stderr, "Error: Failed to start video playback thread\n");
                }
            }
            break;
        case 's':
            if (strcmp(cmd, "stop") == 0) {
                //stop
            }
            break;
        default:
            wrefresh(cmd_win);
            break;
    }
}

// Function that creates UI for video player
void init_ui(WINDOW **main_win, WINDOW **cmd_win) {
    initscr();              // Initialize ncurses
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable special keys

    // Calculate dimensions for main and command windows
    int main_win_height = LINES - CMD_WIN_HEIGHT;
    int main_win_width = COLS;

    // Create main window
    *main_win = newwin(main_win_height, main_win_width, 0, 0);
    if (*main_win == NULL) {
        endwin(); 
        fprintf(stderr, "Error: Unable to create main window\n");
        exit(EXIT_FAILURE);
    }

    // Create command window
    *cmd_win = newwin(CMD_WIN_HEIGHT, main_win_width, main_win_height, 0);
    if (*cmd_win == NULL) {
        delwin(*main_win);
        endwin();     
        fprintf(stderr, "Error: Unable to create command window\n");
        exit(EXIT_FAILURE);
    }

    // Display prompt in command window
    mvwprintw(*cmd_win, 1, 1, "> ");
    wrefresh(*main_win);
    wrefresh(*cmd_win);
}

// Function that destroys all created windows
void destroy_ui(WINDOW **main_win, WINDOW **cmd_win) {
    delwin(*main_win);
    delwin(*cmd_win);
    endwin();
}

// Main function
int main() {
    // Create UI
    init_ui(&main_win, &cmd_win);

    // Loop for processing cmd
    char cmd[256];
    while (1) {
        wgetstr(cmd_win, cmd);                  // Get user input
        wclear(cmd_win);                        // Clear command window
        mvwprintw(cmd_win, 1, 1, "> ");         // Redisplay prompt
        wrefresh(cmd_win);                      // Refresh window
        process_cmd(cmd, main_win, cmd_win);    // Process commands
    }

    // Clean up and exit
    destroy_ui(&main_win, &cmd_win);
    return 0;
}