/* avpl_flags.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.04.2024
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
*/
typedef struct flags {
    volatile sig_atomic_t winch_flag;
} flags_t;

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
void handle_winch(int sig);

#endif // AVPL_FLAGS_H__
