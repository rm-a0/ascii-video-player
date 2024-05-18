/* avpl_sem.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
*/
#ifndef AVPL_SEM_H__
#define AVPL_SEM_H__

#include <semaphore.h>

/* Struct: sems_t
 * --------------
 * Structure holding all semaphores
 * 
 * Variables
 * ---------
 * mutex - main semaphore for mutual exclusion
 * pause_sem - semaphore used for pausing a video
*/
typedef struct sems {
    sem_t mutex;
    sem_t video;
} sems_t;

/* Function: init_sems
 * -------------------
 * Initializes all semaphores in sems_t struct
 * 
 * Parameters
 * ----------
 * none
 * 
 * Return value
 * ------------
 * pointer to a struct holding semaphores
*/
sems_t* init_sems();

/* Function: destroy_sems
 * ----------------------
 * Destroys all semaphores in sems_t struct
 * 
 * Parameters
 * ----------
 * sems - pointer to struct holding semaphores
 * 
 * Return value
 * ------------
 * void
*/
void destroy_sems(sems_t *sems);

#endif // AVPL_SEM_H__