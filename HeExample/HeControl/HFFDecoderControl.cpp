#include "HFFDecoderControl_p.h"
#include "HFFCmdUtil.h"
#include "HFFDataControl.h"

HE_BEGIN_NAMESPACE

HFFDecoderControl::HFFDecoderControl(QObject *parent) :
    QObject(parent),
    d_ptr(new HFFDecoderControlPrivate)
{
}

HFFDecoderControl::~HFFDecoderControl()
{
    close();
}

int HFFDecoderControl::pkt_serial()
{
    return d_ptr->pkt_serial;
}

int HFFDecoderControl::finish_serial()
{
    return d_ptr->finish_serial;
}

void HFFDecoderControl::set_start_pts(int64_t pts, AVRational tb)
{
    d_ptr->start_pts = pts;
    d_ptr->start_pts_tb = tb;
}

void HFFDecoderControl::set_finish()
{
    d_ptr->finish_serial = d_ptr->pkt_serial;
}

void HFFDecoderControl::open(AVCodecContext *ctx)
{
    d_ptr->codec_ctx = ctx;
    d_ptr->pkt = av_packet_alloc();
    d_ptr->pkt_serial = -1;
    d_ptr->pkt_pending = false;
    d_ptr->finish_serial = -1;
    d_ptr->start_pts = AV_NOPTS_VALUE;
}

void HFFDecoderControl::close()
{
    av_packet_free(&d_ptr->pkt);
}

int HFFDecoderControl::decode(HFFPacketQueue *packets, AVFrame *frame, AVSubtitle *sub)
{
    int ret = AVERROR(EAGAIN);
    int serial = -1;
    auto pkt = av_packet_alloc();
    while (true)
    {
        serial = *packets->serial();
        if (serial == d_ptr->pkt_serial)
        {
            do
            {
                if (packets->abort_request())
                    return -1;

                if (d_ptr->codec_ctx->codec_type == AVMEDIA_TYPE_VIDEO)
                {
                    ret = avcodec_receive_frame(d_ptr->codec_ctx, frame);
                    if (ret >= 0)
                    {
                        if (d_ptr->reorder_pts == -1)
                            frame->pts = frame->best_effort_timestamp;
                        else if (d_ptr->reorder_pts == 0)
                            frame->pts = frame->pkt_dts;
                    }
                }
                if (d_ptr->codec_ctx->codec_type == AVMEDIA_TYPE_AUDIO)
                {
                    ret = avcodec_receive_frame(d_ptr->codec_ctx, frame);
                    if (ret >= 0)
                    {
                        auto tb = (AVRational){1, frame->sample_rate};
                        if (frame->pts != AV_NOPTS_VALUE)
                            frame->pts = av_rescale_q(frame->pts, d_ptr->codec_ctx->pkt_timebase, tb);
                        else if (d_ptr->next_pts != AV_NOPTS_VALUE)
                            frame->pts = av_rescale_q(d_ptr->next_pts, d_ptr->next_pts_tb, tb);
                        if (frame->pts != AV_NOPTS_VALUE)
                        {
                            d_ptr->next_pts = frame->pts + frame->nb_samples;
                            d_ptr->next_pts_tb = tb;
                        }
                    }
                }
                if (ret == AVERROR_EOF)
                {
                    set_finish();
                    avcodec_flush_buffers(d_ptr->codec_ctx);
                    return 0;
                }
                if (ret >= 0)
                    return 1;
            } while (ret != AVERROR(EAGAIN));
        }

        do
        {
            if (packets->remaining() == 0)
                emit empty_packet_queue();
            if (d_ptr->pkt_pending)
            {
                av_packet_move_ref(pkt, d_ptr->pkt);
                d_ptr->pkt_pending = false;
            }
            else
            {
                if (packets->get(pkt, true, &d_ptr->pkt_serial) < 0)
                    return -1;
            }
            if (serial == d_ptr->pkt_serial)
                break;
            av_packet_unref(pkt);
        } while (true);

        if (pkt->data == flush_pkt.data)
        {
            avcodec_flush_buffers(d_ptr->codec_ctx);
            d_ptr->finish_serial = 0;
            d_ptr->next_pts = d_ptr->start_pts;
            d_ptr->next_pts_tb = d_ptr->start_pts_tb;
            continue;
        }

        if (d_ptr->codec_ctx->codec_type == AVMEDIA_TYPE_SUBTITLE)
        {
            int got = 0;
            ret = avcodec_decode_subtitle2(d_ptr->codec_ctx, sub, &got, pkt);
            if (ret < 0)
            {
                ret = AVERROR(EAGAIN);
            }
            else
            {
                if (got && !pkt->data)
                {
                    d_ptr->pkt_pending = true;
                    av_packet_move_ref(d_ptr->pkt, pkt);
                }
                ret = got ? 0 : (pkt->data ? AVERROR(EAGAIN) : AVERROR_EOF);
            }
        }
        else
        {
            if (avcodec_send_packet(d_ptr->codec_ctx, pkt) == AVERROR(EAGAIN))
            {
                av_log(d_ptr->codec_ctx, AV_LOG_ERROR, "Receive_frame and send_packet both returned EAGAIN, which is an API violation.\n");
                d_ptr->pkt_pending = true;
                av_packet_move_ref(d_ptr->pkt, pkt);
            }
        }
        av_packet_unref(pkt);
    }
    av_packet_free(&pkt);
}

HE_END_NAMESPACE
