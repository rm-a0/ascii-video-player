#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int main() {
    initscr();  // Initialize the ncurses library
    printw("Hello, ncurses!");  // Print a message on the screen
    refresh();  // Refresh the screen to show the message
    getch();  // Wait for a key press
    endwin();  // End ncurses mode, restoring the original terminal settings
    return 0;
}
