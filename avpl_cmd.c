/* avpl_cmd.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#include <stdio.h>
#include <stdbool.h>

#include "avpl_cmd.h"

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

    // Refresh window
    wrefresh(wins->main_win);
}
