/* avpl_ui.h
 * ----------------------
 * Author:  Michal Repcik
 * Date:	17.05.2024
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
 * cmd_win_height - height of command line window
 * 
 * Return value
 * ------------
 * pointer to a wins_t struct
*/
wins_t* init_ui(int cmd_win_height);

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

/* Function: resize_ui
 * -------------------
 * Destroys previously created windows inside wins_t struct
 * Refres ncurses to get new window
 * Reinitialize new windows with updated terminal size
 * 
 * Parameters
 * ----------
 * wins - pointer to a wins_t struct
 * cmd_win_height - height of a command window
 * 
 * Return value
 * ------------
 * state in which function ended
*/
int resize_ui(wins_t *wins, int cmd_win_height);

/* Function: win_print
 * -------------------
 * Function that prints msg to a window
 * 
 * Parameters
 * ----------
 * win - pointer to a window
 * msg - message you want to print
 * ... - other arguments
 * 
 * Return value
 * ------------
 * void
*/
void win_print(WINDOW* win, const char* msg, ...);

/* Function: cmd_print
 * -------------------
 * Function that prints msg to command window
 * 
 * Parameters
 * ----------
 * cmd_win - pointer to a command window
 * msg - message you want to print
 * ... - other arguments
 * 
 * Return value
 * ------------
 * void
*/
void cmd_print(WINDOW* cmd_win, const char* msg, ...);

#endif // AVPL_UI_H__