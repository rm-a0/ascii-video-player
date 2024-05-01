#define _XOPEN_SOURCE 500           // Solves uslees compilation issues

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers
#include <libavcodec/avcodec.h>     // Lib for multimedia codecs

#include "video_player.h"

#define ASCII_CHARS " .,:;i1tfLCG08@"

// Function that displays error messages to window
void display_error(WINDOW *win, const char *msg) {
    werase(win);
    mvwprintw(win, 0, 0, "Error: %s", msg); 
    wrefresh(win);
}

// Function that converts frame to ascii
void frame_to_ascii(WINDOW *win, AVFrame *frame, int w_height, int w_width) {
    // Get frame dimensions
    int f_width = frame->width;
    int f_height = frame->height;
    
    // Calculate how many pixels should chars cover
    int char_width = f_width/w_width/3; // Char width is usually 3 px
    int char_height = char_width*2;     // Char height is double its width

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

// Function that separates video into frames
void play_video(const char *vid_title, WINDOW *main_win) {
    avformat_network_init();    // Init network components

    // Initialize necessary components
    AVCodec *codec = NULL;
    AVPacket packet;
    AVFrame *frame = NULL;
    int video_stream_index;

    // Open video file
    AVFormatContext *format_ctx = NULL;
    if (avformat_open_input(&format_ctx, vid_title, NULL, NULL) != 0) {
        display_error(stdscr, "Could not open video file");
        return;
    }

    // Find video stream information
    if (avformat_find_stream_info(format_ctx, NULL) < 0) {
        display_error(stdscr, "Could not find stream information");
        avformat_close_input(&format_ctx);
        return;
    }

    // Find video stream
    video_stream_index = av_find_best_stream(format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (video_stream_index < 0) {
        display_error(stdscr, "Could not find video stream");
        avformat_close_input(&format_ctx);
        return;
    }

    // Initialize codec context
    AVCodecParameters *codec_params = format_ctx->streams[video_stream_index]->codecpar;
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, codec_params);

    // Open codec
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        display_error(stdscr, "Could not open codec");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&format_ctx);
        return;
    }

    // Allocate memory for frame
    frame = av_frame_alloc();
    if (!frame) {
        display_error(stdscr, "Failed to allocate frame");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&format_ctx);
        return;
    }

    // Read frames from the video
    while (av_read_frame(format_ctx, &packet) >= 0) {
        if (packet.stream_index == video_stream_index) {
            // Decode the video packet
            int ret = avcodec_send_packet(codec_ctx, &packet);
            if (ret < 0) {
                display_error(main_win, "Failed to decode video packet");
                break;
            }

            // Receive and process the decoded frame
            while (ret >= 0) {
                ret = avcodec_receive_frame(codec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0) {
                    display_error(main_win, "Failed to retrieve freame from codec");
                    break;
                }
                
                // Display decoded frame
                frame_to_ascii(main_win, frame, getmaxx(main_win), getmaxy(main_win));
                usleep(50000);
                wrefresh(main_win);
            }
        }
        av_packet_unref(&packet);
    }

    // Cleanup
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&format_ctx);
}