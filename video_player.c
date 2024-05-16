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

// Initialize globally
// Structs
flags_t *flags = NULL;
sems_t *sems = NULL;
wins_t* wins = NULL;
thrd_args_t *thrd_args = NULL;
// Thread
pthread_t vid_thread;

void handle_winch() {
    flags->winch_flag = 1;
}

// Function for processing arguments in cmd_win
int process_cmd(const char* cmd) {
    // Split command into parts
    char temp[256];
    strcpy(temp, cmd);

    char *token = strtok(temp, " ");
    if (token == NULL) {
        return 0;
    }

    switch (token[0]) {
        case 'h':
        // HELP
            if (strcmp(token, "help") == 0) {
                pause_vid(sems, flags);
                display_help(wins);
            }
            break;
        case 'e':
        case 'q':
        // QUIT AND EXIT
            if (strcmp(token, "quit") == 0 || strcmp(token, "exit") == 0) {
                end_vid(thrd_args, sems, wins, flags, &vid_thread);
                return 1;
            }
        // END
            else if (strcmp(token, "end") == 0) {
                end_vid(thrd_args, sems, wins, flags, &vid_thread);
            }
            break;
        case 'r':
        // RESUME
            if (strcmp(token, "resume") == 0) {
                resume_vid(sems, flags);
            }
            break;
        case 's':
        case 'p':
        // PLAY
            if (strcmp(token, "play") == 0) {
                play_vid(strtok(NULL, " "), &thrd_args, wins, flags, sems, &vid_thread);
            }
        // PAUSE AND STOP
            else if (strcmp(token, "pause") == 0 || strcmp(token, "stop") == 0) {
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

    // Display command line
    cmd_print(wins->cmd_win, "");

    // Loop for processing commands
    char cmd[256];
    while (1) {
        if (flags->winch_flag != 1) {
            // Get user input
            wgetstr(wins->cmd_win, cmd);
            wclear(wins->cmd_win);                   
            
            // Redisplay command line
            cmd_print(wins->cmd_win, "");

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