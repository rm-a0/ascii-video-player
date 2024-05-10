#include <stdio.h>
#include <stdbool.h>

#include "avpl_cmd.h"
#include "avpl_sem.h"
#include "avpl_flags.h"

void pause_vid(sems_t *sems, flags_t *flags) {
    if (flags->vid_playing == true) {
        flags->vid_playing = false;
        sem_wait(&(sems->video));
    }
}

void resume_vid(sems_t *sems, flags_t *flags) {
    if (flags->vid_playing == false) {
        flags->vid_playing = true;
        sem_post(&(sems->video));
    }
}

