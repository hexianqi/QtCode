#pragma once

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

#define CONFIG_AVFILTER 1

// no AV sync correction is done if below the minimum AV sync threshold
#define AV_SYNC_THRESHOLD_MIN 0.04
// AV sync correction is done if above the maximum AV sync threshold
#define AV_SYNC_THRESHOLD_MAX 0.1
// If a frame duration is longer than this, it will not be duplicated to compensate AV sync
#define AV_SYNC_FRAMEDUP_THRESHOLD 0.1
// no AV correction is done if too big error
#define AV_SYNC_THRESHOLD_NO 10.0

#define MAX_PACKET_QUEUE_SIZE (15 * 1024 * 1024)
#define MIN_PACKETS 25

#define EXTERNAL_CLOCK_MIN_FRAMES 2
#define EXTERNAL_CLOCK_MAX_FRAMES 10
// external clock speed adjustment constants for realtime sources based on buffer fullness
#define EXTERNAL_CLOCK_SPEED_MIN  0.900
#define EXTERNAL_CLOCK_SPEED_MAX  1.010
#define EXTERNAL_CLOCK_SPEED_STEP 0.001

#define VIDEO_QUEUE_SIZE 3
#define AUDIO_QUEUE_SIZE 9
#define SUBTITLE_QUEUE_SIZE 16

// we use about AUDIO_DIFF_AVG_NB A-V differences to make the average
#define AUDIO_DIFF_AVG_NB   20

// maximum audio speed change to get correct sync
#define SAMPLE_CORRECTION_PERCENT_MAX 10

// NOTE: the size must be big enough to compensate the hardware audio buffersize size
// TODO: We assume that a decoded and resampled frame fits into this buffer
#define SAMPLE_ARRAY_SIZE (8 * 65536)

HE_CONTROL_END_NAMESPACE
