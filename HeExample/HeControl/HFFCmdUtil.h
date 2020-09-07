#pragma once

#include "HControlGlobal.h"
extern "C" {
#include "libavformat/avformat.h"
}

HE_CONTROL_BEGIN_NAMESPACE

extern AVDictionary *format_opts;
extern AVDictionary *codec_opts;
extern AVDictionary *resample_opts;
extern AVDictionary *sws_opts;
extern AVDictionary *swr_opts;
extern AVPacket flush_pkt;

// Initialize the cmdutils option system, in particular allocate the *_opts contexts.
void init_opts();
// Uninitialize the cmdutils option system, in particular free the *_opts contexts and their contents.
void uninit_opts();
// Filter out options for given codec.
AVDictionary *filter_codec_opts(AVDictionary *opts, AVCodecID codec_id, AVFormatContext *ctx, AVStream *st, AVCodec *codec);
// Setup AVCodecContext options for avformat_find_stream_info().
AVDictionary **setup_find_stream_info_opts(AVFormatContext *ctx, AVDictionary *codec_opts);

bool is_realtime(AVFormatContext *ctx);

double get_rotation(AVStream *st);

int64_t get_valid_channel_layout(int64_t channel_layout, int channels);

bool cmp_audio_fmts(AVSampleFormat fmt1, int64_t channel_count1, AVSampleFormat fmt2, int64_t channel_count2);

int cmp_mod(int a, int b);

HE_CONTROL_END_NAMESPACE
