/* avpl_thrd.c
 * ----------------------
 * Author:  Michal Repcik
 * Date: 	16.05.2024
*/
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "avpl_thrd.h"
#include "media_proc.h"

void *video_thread(void *args) {
    // Unpack arguments
    thrd_args_t *thrd_args = (thrd_args_t*)args;
    if (thrd_args == NULL) {
        fprintf(stderr, "Error: Invalid thread arguments\n");
        return NULL;
    }
    char* filename = thrd_args->filename;
    wins_t *wins = thrd_args->wins;
    sems_t *sems = thrd_args->sems;
    flags_t *flags = thrd_args->flags;

    // Call play media function
    if (play_media(filename, wins, sems, flags) != 0) {
        flags->vid_playing = false;
        flags->vid_thrd_active = false;
    }

    return NULL;
}

thrd_args_t* init_thrd_args(wins_t* wins, char* filename, sems_t *sems, flags_t* flags) {
    // Allocate memory for the struct
    thrd_args_t *thrd_args = malloc(sizeof(thrd_args_t));
    if (thrd_args == NULL) {
        return NULL;
    }
    // Allocate memory for filename string
    thrd_args->filename = malloc(strlen(filename) + 1);
    if (thrd_args->filename == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for filename\n");
        free(thrd_args);
        return NULL;
    }
    
    // Initialize varaibles within the struct
    strcpy(thrd_args->filename, filename);
    thrd_args->wins = wins;
    thrd_args->sems = sems;
    thrd_args->flags = flags;

    return thrd_args;
}

void destroy_thrd_args(thrd_args_t* thrd_args) {
    if (thrd_args != NULL) {
        free(thrd_args->filename);
        free(thrd_args);
    }
}