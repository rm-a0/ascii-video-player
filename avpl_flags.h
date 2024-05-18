/* avpl_flags.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	18.05.2024
*/
#ifndef AVPL_FLAGS_H__
#define AVPL_FLAGS_H__

#include <signal.h>

/* Struct: flags_t
 * --------------
 * Structure holding all flags
 * Should be initialized globally in main
 * 
 * Variables
 * ---------
 * winch_flag - flag that indicates window change
 * vid_playing - indicates if video is playing or not
 * vid_thrd - indicates if video thread is active or not
*/
typedef struct flags {
    volatile sig_atomic_t winch_flag;
    volatile bool vid_playing;
    volatile bool vid_thrd_active;
    volatile bool vid_end;
    volatile float vid_speed;
} flags_t;

/* Function: init_flags
 * --------------------
 * Allocates memory for flags_t struct
 * Initializes all flags
 * 
 * Parameters
 * ----------
 * none
 * 
 * Return value
 * ------------
 * pointer to a flags_t struct
*/
flags_t* init_flags();

/* Function: destroy_flags
 * -----------------------
 * Frees allocated memory
 * 
 * Parameters
 * ----------
 * pointer to a flags_t struct
 * 
 * Return value
 * ------------
 * void
*/
void destroy_flags(flags_t *flags);

/* Function: init_sig
 * -------------------
 * Initializes all signals for setting up flags
 * 
 * Parameters
 * ----------
 * none
 * 
 * Return value
 * ------------
 * void
*/
void init_sig();

/* Function: handle_winch
 * -------------------
 * Sets winch_flag when window change is detected
 * Must be defined in main
 * 
 * Parameters
 * ----------
 * sig - signal specifier
 * 
 * Return value
 * ------------
 * void
*/
void handle_winch();

#endif // AVPL_FLAGS_H__
