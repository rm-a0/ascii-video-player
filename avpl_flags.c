/* avpl_flags.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    05.04.2024
*/
#define _POSIX_C_SOURCE 199309L     // Sigaction
#include <stdio.h>
#include "avpl_flags.h"

void init_sig() {
    // Initialize sigaction structures for SIGWINCH 
    struct sigaction sa_winch;
    sa_winch.sa_handler = handle_winch;
    sa_winch.sa_flags = 0;
    sigemptyset(&sa_winch.sa_mask);

    // Set up signal handlers for SIGWINCH
    sigaction(SIGWINCH, &sa_winch, NULL);
}
