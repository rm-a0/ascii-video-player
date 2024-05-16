/* avpl_sem.c
 * ----------------------
 * Author:  Michal Repcik
 * Date: 	16.05.2024
*/
#include <stdio.h>
#include <stdlib.h>

#include "avpl_sem.h"

sems_t* init_sems() {
    // Allocate memory for sems_t struct
    sems_t* sems = malloc(sizeof(sems_t));
    if (sems == NULL) {
        return NULL;
    }

    // Initialize semaphores
    sem_init(&(sems->mutex), 0, 1);
    sem_init(&(sems->video), 0, 1);

    return sems;
}

void destroy_sems(sems_t *sems) {
    // Destroy semaphores
    sem_destroy(&(sems->mutex));
    sem_destroy(&(sems->video));

    // Free allocated memory
    free(sems);
}