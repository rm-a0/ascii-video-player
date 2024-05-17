/* ascii_conv.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:	17.05.2024
*/
#include "ascii_conv.h"

#define ASCII_CHARS     " .,:;i1tfLCG08@"
#define PIXEL_WIDTH     3
#define PIXEL_HEIGHT    2

void frame_to_ascii(WINDOW *win, AVFrame *frame, int w_height, int w_width) {
    // Get frame dimensions
    int f_width = frame->width;
    int f_height = frame->height;
    
    // Calculate how many pixels should character cover
    int char_width = f_width/w_width/PIXEL_WIDTH; // Char width is usually 3 px
    int char_height = char_width*PIXEL_HEIGHT;     // Char height is double its width

    // Draw ASCII art based on pixel luminance
    for (int y = 0; y < f_height; y += char_height) {
        for (int x = 0; x < f_width; x += char_width) {
            // Calculate average luminance for the block of pixels
            int total_luminance = 0;
            int num_pixels = 0;

            for (int dy = 0; dy < char_height && (y + dy) < f_height; dy++) {
                for (int dx = 0; dx < char_width && (x + dx) < f_width; dx++) {
                    int luminance = frame->data[0][(y + dy) * frame->linesize[0] + (x + dx)];
                    total_luminance += luminance;
                    num_pixels++;
                }
            }

            // Calculate average luminance value for the block
            int average_luminance = total_luminance / num_pixels;

            // Map luminance value to ASCII character index
            int ascii_index = (average_luminance * strlen(ASCII_CHARS)) / 256;
            char ascii_char = ASCII_CHARS[ascii_index];

            // Draw ASCII character on the window
            mvwaddch(win, y / char_height, x / char_width, ascii_char);
        }
    }
}