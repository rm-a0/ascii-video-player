/* avpl_cmd.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "avpl_cmd.h"

int play_vid(char* filename, thrd_args_t** thrd_args,  wins_t* wins, flags_t* flags, sems_t* sems, pthread_t* thread) {
    // End active thread and start a new one
    if (flags->vid_thrd_active == true) {
        end_vid(*thrd_args, sems, wins, flags, thread);
    }

    // Check if filename is valid
    if (filename == NULL) {
        cmd_print(wins->cmd_win, "Path not specified");
        return 1;
    }

    // Allocate memory for thread arguments
    *thrd_args = init_thrd_args(wins, filename, sems, flags);

    // Start video playback in a new thread
    if (pthread_create(thread, NULL, video_thread, (void *)*thrd_args) != 0) {
        fprintf(stderr, "Error: Failed to start video playback thread\n");
        return 1;
    }

    // Set relevant flags
    flags->vid_playing = true;
    flags->vid_thrd_active = true;

    return 0;
}

int end_vid(thrd_args_t* thrd_args, sems_t* sems, wins_t* wins, flags_t* flags, pthread_t* thread) {
    // Check if thread is active
    if (flags->vid_thrd_active == false) {
        return 1;
    }

    // Resume video to prevent semaphore deadlock
    resume_vid(sems, flags);
    flags->vid_end = true;

    if (pthread_join(*thread, NULL) != 0) {
        cmd_print(wins->cmd_win, "Failed to join video thread");
        return 1;
    }

    // Free memory for thread arguments
    destroy_thrd_args(thrd_args);

    // Reset flags
    flags->vid_playing = false;
    flags->vid_thrd_active = false;
    return 0;
}

int pause_vid(sems_t *sems, flags_t *flags) {
    if (flags->vid_playing == true) {
        flags->vid_playing = false;
        sem_wait(&(sems->video));
        return 0;
    }
    return 1;
}

int resume_vid(sems_t *sems, flags_t *flags) {
    if (flags->vid_playing == false) {
        flags->vid_playing = true;
        sem_post(&(sems->video));
        return 0;
    }
    return 1;
}

int change_speed(char* speed, flags_t* flags) {
    if (strcmp(speed, "0") == 0) {
        return 1;
    }
    else if (strcmp(speed, "normal") == 0) {
        flags->vid_speed = 1.0;
    }
    else {
        flags->vid_speed = atof(speed);
    }

    return 0;
}

void display_help(wins_t *wins) {
    // Erase window
    werase(wins->main_win);

    // Display instructions
    wprintw(wins->main_win, "HOW TO USE\n");
    wprintw(wins->main_win, "List of all avaliable commands\n\n");
    wprintw(wins->main_win, "   help                        - displays this info\n");
    wprintw(wins->main_win, "   quit, exit                  - ends program\n");
    wprintw(wins->main_win, "   play [/path/to/file]        - plays chosen media\n");
    wprintw(wins->main_win, "   pause, stop                 - pauses the video\n");
    wprintw(wins->main_win, "   resume                      - resumes the video\n");
    wprintw(wins->main_win, "   end                         - ends video\n");
    wprintw(wins->main_win, "   speed [normal, 1.2, ...]    - adjusts video speed globally\n");

    // Refresh window
    wrefresh(wins->main_win);
}
