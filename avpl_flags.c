/* avpl_flags.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
*/
#define _POSIX_C_SOURCE 199309L     // Sigaction
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "avpl_flags.h"

extern flags_t *flags;

flags_t* init_flags() {
    // Alocate memory for flags struct
    flags_t *flags = malloc(sizeof(flags_t));
    if (flags == NULL) {
        return NULL;
    }

    // Initialize all flags
    flags->winch_flag = 0;
    flags->vid_thrd_active = false;
    flags->vid_playing = false;
    flags->vid_end = false;
    flags->vid_speed = 1;

    return flags;
}

void destroy_flags(flags_t *flags) {
    // Free allocated memory
    free(flags);
}

void init_sig() {
    // Initialize sigaction structures for SIGWINCH 
    struct sigaction sa_winch;
    sa_winch.sa_handler = handle_winch;
    sa_winch.sa_flags = 0;
    sigemptyset(&sa_winch.sa_mask);

    // Set up signal handlers for SIGWINCH
    sigaction(SIGWINCH, &sa_winch, NULL);
}

void handle_winch() {
    flags->winch_flag = 1;
}