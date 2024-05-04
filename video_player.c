/* video_player.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    06.04.2024
*/
#define _POSIX_C_SOURCE 199309L     // Sigaction
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "avpl_sem.h"               // Lib for semaphores
#include "avpl_thrd.h"              // Lib for threads
#include "avpl_flags.h"             // Lib for flags
#include "avpl_ui.h"                // Lib for user interface
#include "media_proc.h"             // Lib for media processing

// Constants
#define CMD_WIN_HEIGHT 3

// Threads
pthread_t vid_thread;
// Flags
flags_t flags;

void handle_sigwinch(int sig) {
    flags.winch_flag = 1;
}   

void init_sig() {
    // Initialize sigaction structures for SIGWINCH 
    struct sigaction sa_winch;
    sa_winch.sa_handler = handle_sigwinch;
    sa_winch.sa_flags = 0;
    sigemptyset(&sa_winch.sa_mask);

    // Set up signal handlers for SIGWINCH
    sigaction(SIGWINCH, &sa_winch, NULL);
}

// Function for processing arguments in cmd_win
int process_cmd(const char* cmd, wins_t* wins) {
    switch (cmd[0]) {
        // EXIT and QUIT
        case 'e':
            if (strcmp(cmd, "exit") == 0) {
                return 1;
            }
            break;
        case 'q':
            if (strcmp(cmd, "quit") == 0) {
                return 1;
            }
            break;
        // PLAY
        case 'p':
            if (strcmp(cmd, "play") == 0) {
                char *vid_filename = "fate.mp4";

                // Allocate memory for threads
                // DO NOT PLAY TWICE ==> SEGFAULT
                // Fix in the future
                // move malloc somewhere else
                // create function for struct malloc
                thrd_args_t *thrd_args = init_thrd_args(wins->main_win, vid_filename);

                // Start video playback in a new thread
                if (pthread_create(&vid_thread, NULL, video_thread, (void *)thrd_args) != 0) {
                    fprintf(stderr, "Error: Failed to start video playback thread\n");
                }
            }
            break;
        // STOP
        case 's':
            if (strcmp(cmd, "stop") == 0) {
                
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
    initscr();              // Initialize the screen
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable keypad for function and arrow keys
    curs_set(0);            // Hide cursor

    sems_t sems;            // Init sems struct
    init_sems(&sems);       // Init semaphores

    init_sig();             // Init signals
    
    // Init windows
    wins_t* wins = init_ui(CMD_WIN_HEIGHT);
    if (wins == NULL) {
        fprintf(stderr, "Failed to allocate memory for wins_t struct\n");
        endwin();
        return 1;
    }

    // Display '>' in cmd_win
    mvwprintw(wins->cmd_win, 1, 1, "> ");
    wrefresh(wins->cmd_win);                  

    // Loop for processing commands
    char cmd[256];
    while (1) {
        if (flags.winch_flag != 1) {
            // Get user input
            wgetstr(wins->cmd_win, cmd);
            wclear(wins->cmd_win);                   
            
            // Redisplay ">"
            mvwprintw(wins->cmd_win, 1, 1, "> ");
            wrefresh(wins->cmd_win);

            // Process commands
            if ((process_cmd(cmd, wins)) == 1) {
                break;
            } 
        }
        else {
            // Resize ui
            wclear(wins->cmd_win);
    
            // Destroy and reinitialize UI
            destroy_ui(wins);
            endwin();
            initscr();
            wins = init_ui(CMD_WIN_HEIGHT);

            // Reset winch_flag
            flags.winch_flag = 0;
        }
    }

    // Clean up and exit
    destroy_sems(&sems);
    destroy_ui(wins);
    endwin();
    return 0;
}