#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>                // Lib for terminal operations
#include <libavformat/avformat.h>   // Lib for multimedia containers
#include <libavcodec/avcodec.h>     // Lib for multimedia codecs

#include "video_player.h"

void display_error(WINDOW *win, const char *msg) {
    werase(win);
    mvwprintw(win, 0, 0, "Error: %s", msg); 
    wrefresh(win);
}

// Function that separates video into frames
void play_video(const char *vid_title, WINDOW *main_win, WINDOW *cmd_win) {
    avformat_network_init(); // Initialize network components if needed

    AVFormatContext *format_ctx = NULL;
    AVCodec *codec = NULL;
    AVPacket packet;
    AVFrame *frame = NULL;
    int video_stream_index;

    // Open video file
    if (avformat_open_input(&format_ctx, vid_title, NULL, NULL) != 0) {
        display_error(main_win, "Could not open video file");
        return;
    }

    // Find video stream information
    if (avformat_find_stream_info(format_ctx, NULL) < 0) {
        display_error(main_win, "Could not find stream information");
        avformat_close_input(&format_ctx);
        return;
    }

    // Find video stream
    video_stream_index = av_find_best_stream(format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (video_stream_index < 0) {
        display_error(main_win, "Could not find video stream");
        avformat_close_input(&format_ctx);
        return;
    }

    // Initialize codec context
    AVCodecParameters *codec_params = format_ctx->streams[video_stream_index]->codecpar;
    AVCodecContext *codec_ctx = avcodec_alloc_context3(NULL);
    avcodec_parameters_to_context(codec_ctx, codec_params);

    // Allocate memory for frame
    frame = av_frame_alloc();
    if (!frame) {
        display_error(main_win, "Failed to allocate frame");
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
                display_error(main_win, "Error decoding video packet");
                break;
            }

            // Receive and process the decoded frame
            while (ret >= 0) {
                ret = avcodec_receive_frame(codec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0) {
                    display_error(main_win, "Error recieving frame from codec");
                    break;
                }

                // Process the frame (convert to ASCII and render with ncurses)
                // Example: Convert frame to ASCII and render with ncurses

                // Render the frame using ncurses
                // mvprintw(row, col, "%s", ascii_frame_data);
                // refresh();
            }
        }
        av_packet_unref(&packet);
    }

    // Cleanup
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&format_ctx);
}