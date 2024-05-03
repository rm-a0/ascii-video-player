/* avpl_sem.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.03.2024
*/

#include <stdio.h>
#include "avpl_sem.h"

void init_sems(sems_t *sems) {
    sem_init(&(sems->mutex), 0, 1);
}

void destroy_sems(sems_t *sems) {
    sem_destroy(&(sems->mutex));
}