/* video_player.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "avpl_sem.h"               // Lib for semaphores
#include "avpl_thrd.h"              // Lib for threads
#include "avpl_flags.h"             // Lib for flags
#include "avpl_ui.h"                // Lib for user interface
#include "avpl_cmd.h"               // Lib for commands
#include "media_proc.h"             // Lib for media processing

// Constants
#define CMD_WIN_HEIGHT 3

// Threads
pthread_t vid_thread;

// Initialize globally
flags_t *flags = NULL;
sems_t *sems = NULL;
wins_t* wins = NULL;

void handle_winch() {
    flags->winch_flag = 1;
}

// Function for processing arguments in cmd_win
int process_cmd(const char* cmd) {
    switch (cmd[0]) {
        case 'e':
        case 'q':
        // QUIT AND EXIT
            if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0) {
                return 1;
            }
        // END
            else if (strcmp(cmd, "end") == 0) {
                mvwprintw(wins->cmd_win, 1, 1, "> TODO");
                wrefresh(wins->cmd_win);
            }
            break;
        case 'r':
        // RESUME
            if (strcmp(cmd, "resume") == 0) {
                resume_vid(sems, flags);
            }
            break;
        case 's':
        case 'p':
        // PLAY
            if (strcmp(cmd, "play") == 0) {
                char *vid_filename = "fate.mp4";

                if (flags->vid_thrd_active == true) {
                    mvwprintw(wins->cmd_win, 1, 1, "> Video is already playing");
                    wrefresh(wins->cmd_win);
                    break;
                }
                // Allocate memory for threads
                // DO NOT PLAY TWICE ==> SEGFAULT
                thrd_args_t *thrd_args = init_thrd_args(wins, vid_filename, sems);

                // Start video playback in a new thread
                if (pthread_create(&vid_thread, NULL, video_thread, (void *)thrd_args) != 0) {
                    fprintf(stderr, "Error: Failed to start video playback thread\n");
                }

                flags->vid_playing = true;
                flags->vid_thrd_active = true;
            }
        // PAUSE AND STOP
            else if (strcmp(cmd, "pause") == 0 || strcmp(cmd, "stop") == 0) {
                pause_vid(sems, flags);
            }
            break;
        default:
            wrefresh(wins->cmd_win);
            break;
    }
    return 0;
}

// Main function
int main() {
    /*      Ncurses settings      */
    /******************************/
    initscr();              // Initialize the screen
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable keypad for function and arrow keys
    curs_set(0);            // Hide cursor
    /******************************/

    init_sig();                     // Init signals
    sems = init_sems();             // Init semaphores
    flags = init_flags();           // Init flags
    wins = init_ui(CMD_WIN_HEIGHT); // Init windows

    // Display '>' in cmd_win
    mvwprintw(wins->cmd_win, 1, 1, "> ");
    wrefresh(wins->cmd_win);

    // Loop for processing commands
    char cmd[256];
    while (1) {
        if (flags->winch_flag != 1) {
            // Get user input
            wgetstr(wins->cmd_win, cmd);
            wclear(wins->cmd_win);                   
            
            // Redisplay ">"
            mvwprintw(wins->cmd_win, 1, 1, "> ");
            wrefresh(wins->cmd_win);

            // Process commands
            if ((process_cmd(cmd)) == 1) {
                break;
            } 
        }
        else {
            // Check if video is playing
            int p_check = pause_vid(sems, flags);

            // Resize ui
            resize_ui(wins, CMD_WIN_HEIGHT);
            
            // Resume video if it was playing
            if (p_check == 0) {
                resume_vid(sems, flags);
            }
            // Reset flag for window change
            flags->winch_flag = 0;
        }
    }

    // Clean up and exit
    destroy_sems(sems);
    destroy_flags(flags);
    destroy_ui(wins);
    endwin();
    return 0;
}