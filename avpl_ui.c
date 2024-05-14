/* avpl_ui.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    06.04.2024
*/
#include <stdlib.h>

#include "avpl_ui.h"

wins_t* init_ui(int cmd_win_height) {
    // Allocate memory for wins_t struct
    wins_t *wins = malloc(sizeof(wins_t));
    if (wins == NULL) {
        return NULL;
    }
    
    // Calculate window dimensions
    int main_win_height = LINES - cmd_win_height;
    int main_win_width = COLS;

    // Create main window
    wins->main_win = newwin(main_win_height, main_win_width, 0, 0);
    if (wins->main_win == NULL) {
        free(wins);
        return NULL;
    }

    // Create command window
    wins->cmd_win = newwin(cmd_win_height, main_win_width, main_win_height, 0);
    if (wins->cmd_win == NULL) {
        delwin(wins->main_win);
        free(wins);
        return NULL;
    }

    return wins;
}

void destroy_ui(wins_t *wins) {
    if (wins != NULL) {
        // Destroy windows
        delwin(wins->main_win);
        delwin(wins->cmd_win);
        // Free allocated memory for wins_t struct
        free(wins);
    }
}

int resize_ui(wins_t *wins, int cmd_win_height) {
    // Destroy existing windows
    delwin(wins->main_win);
    delwin(wins->cmd_win);

    // End refresh and reinitialize ncurses
    endwin();
    refresh();
    initscr();

    // Reinitialize windows with updated size
    int main_win_height = LINES - cmd_win_height;
    int main_win_width = COLS;

    // Recreate main window
    wins->main_win = newwin(main_win_height, main_win_width, 0, 0);
    if (wins->main_win == NULL) {
        free(wins);
        return 1;
    }

    // Recreate command window
    wins->cmd_win = newwin(cmd_win_height, main_win_width, main_win_height, 0);
    if (wins->cmd_win == NULL) {
        delwin(wins->main_win);
        free(wins);
        return 1;
    }

    return 0;
}