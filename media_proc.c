/* media_proc.c
 * ----------------------
 * Author:  Michal Repcik
 * Date:    10.05.2024
*/
#define _XOPEN_SOURCE 500           // Solves usleep compilation issues
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "media_proc.h"
#include "ascii_conv.h"
#include "avpl_sem.h"

void display_error(WINDOW *win, const char *msg) {
    werase(win);
    mvwprintw(win, 0, 0, "Error: %s", msg); 
    wrefresh(win);
}

int play_media(char *vid_title, wins_t *wins, sems_t *sems, flags_t* flags) {
    avformat_network_init();    // Init network components

    // Initialize necessary components
    AVCodec *codec = NULL;
    AVPacket packet;
    AVFrame *frame = NULL;
    int video_stream_index;

    if (wins->main_win == NULL) {
        fprintf(stderr, "Null pointer to main win");
        return 1;
    }

    // Open video file
    AVFormatContext *format_ctx = NULL;
    if (avformat_open_input(&format_ctx, vid_title, NULL, NULL) != 0) {
        display_error(wins->main_win, "Could not open video file");
        return 1;
    }

    // Find video stream information
    if (avformat_find_stream_info(format_ctx, NULL) < 0) {
        display_error(wins->main_win, "Could not find stream information");
        avformat_close_input(&format_ctx);
        return 1;
    }

    // Find video stream
    video_stream_index = av_find_best_stream(format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (video_stream_index < 0) {
        display_error(wins->main_win, "Could not find video stream");
        avformat_close_input(&format_ctx);
        return 1;
    }

    // Initialize codec context
    AVCodecParameters *codec_params = format_ctx->streams[video_stream_index]->codecpar;
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, codec_params);

    // Open codec
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        display_error(wins->main_win, "Could not open codec");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&format_ctx);
        return 1;
    }

    // Allocate memory for frame
    frame = av_frame_alloc();
    if (!frame) {
        display_error(wins->main_win, "Failed to allocate frame");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&format_ctx);
        return 1;
    }

    // Read frames from the video
    while (av_read_frame(format_ctx, &packet) >= 0) {
        if (packet.stream_index == video_stream_index) {
            // Decode the video packet
            int ret = avcodec_send_packet(codec_ctx, &packet);
            if (ret < 0) {
                display_error(wins->main_win, "Failed to decode video packet");
                break;
            }

            // Receive and process the decoded frame
            while (ret >= 0) {
                ret = avcodec_receive_frame(codec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0) {
                    display_error(wins->main_win, "Failed to retrieve frame from codec");
                    break;
                }
                
                // Semaphore for pausing the video
                sem_wait(&(sems->video));

                // Display decoded frame
                frame_to_ascii(wins->main_win, frame, getmaxx(wins->main_win), getmaxy(wins->main_win));
                usleep(50000);
                wrefresh(wins->main_win);
                
                // Unlock semaphore
                sem_post(&(sems->video));

                // End video if flag is set
                if (flags->vid_end == true) {
                    flags->vid_end = false;
                    goto cleanup;
                }
            }
        }
        av_packet_unref(&packet);
    }

    // Cleanup
    cleanup:
        // Erase windows
        werase(wins->main_win);
        wrefresh(wins->main_win);
        av_frame_free(&frame);
        // Free allocated memory
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&format_ctx);
    return 0;
}