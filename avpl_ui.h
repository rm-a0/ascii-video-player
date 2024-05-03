/* avpl_ui.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.03.2024
*/
#ifndef AVPL_UI_H__
#define AVPL_UI_H__

#include <ncurses.h>

/* Struct: wins_t
 * --------------
 * Structure holding all windows necessary
 * for creating user interface
 * 
 * Variables
 * ---------
 * main-win - pointer to main window where everything will be displayed
 * cmd_win - pointer to command line window where user can type
*/
typedef struct wins {
    WINDOW *main_win;
    WINDOW *cmd_win;
} wins_t;

/* Function: init_ui
 * -----------------
 * Dynamically allocates memory for wins_t struct
 * Initializes all windows within the struct
 * 
 * Parameters
 * ----------
 * void
 * 
 * Return value
 * ------------
 * pointer to a wins_t struct
*/
wins_t* init_ui();

/* Function: destroy_ui
 * --------------------
 * Frees dynamically allocated memory for wins_t struct
 * Destroys all windows within the struct
 * 
 * Parameters
 * ----------
 * wins - pointer to a wins_t struct
 * 
 * Return value
 * ------------
 * void
*/
void destroy_ui(wins_t *wins);

#endif // AVPL_UI_H__