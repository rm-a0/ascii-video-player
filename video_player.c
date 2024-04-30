#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers
#include <libavcodec/avcodec.h>     // Lib for multimedia codecs


int main() {
    AVFormatContext *ptr_format_ctx;
    AVCodecContext *ptr_codec_ctx;
    AVFrame *ptr_frame;

    initscr();                  // Init ncurses
    av_register_all();          // Init FFmpeg
    avformat_network_init();    // Init FFmpeg
    
    printw("Hello, ncurses!");  // Print a message on the screen
    refresh();  // Refresh the screen to show the message
    getch();  // Wait for a key press
    endwin();  // End ncurses mode, restoring the original terminal settings
    return 0;
}
