/* avpl_sem.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.03.2024
*/
#ifndef AVPL_SEM_H__
#define AVPL_SEM_H__

#include <semaphore.h>

/* Struct: sems_t
 * --------------
 * Structure holding all semaphores
 * 
 * Variables:
 * mutex     - main semaphore for mutual exclusion
 * pause_sem - semaphore used for pausing a video
*/
typedef struct sems {
    sem_t mutex;
} sems_t;

/* Function: init_sems
 * -------------------
 * Initializes all semaphores in sems_t struct
 * 
 * Parameters:
 * sems - pointer to struct holding semaphores
 * 
 * Return value:
 * void
*/
void init_sems(sems_t *sems);

/* Function: destroy_sems
 * ----------------------
 * Destroys all semaphores in sems_t struct
 * 
 * Parameters:
 * sems - pointer to struct holding semaphores
 * 
 * Return value:
 * void
*/
void destroy_sems(sems_t *sems);

#endif // AVPL_SEM_H__