#include "HFFDataControl_p.h"
#include "HFFConfig.h"
#include "HFFCmdUtil.h"
#include "HFFTypes.h"

using namespace std;

HE_CONTROL_BEGIN_NAMESPACE

HFFClock::HFFClock(QObject *parent) :
    QObject(parent),
    d_ptr(new HFFClockPrivate)
{
}

HFFClock::~HFFClock()
{
}

double HFFClock::pts()
{
    return d_ptr->pts;
}

double HFFClock::speed()
{
    return d_ptr->speed;
}

double HFFClock::last_updated()
{
    return d_ptr->last_updated;
}

void HFFClock::init(int *queue_serial)
{
    d_ptr->speed = 1.0;
    d_ptr->paused = false;
    d_ptr->queue_serial = queue_serial;
    set_clock(NAN, -1);
}

void HFFClock::set_paused(bool b)
{
    d_ptr->paused = b;
}

void HFFClock::set_clock(double pts, int serial)
{
    set_clock(pts, serial, av_gettime_relative() / 1000000.0);
}

void HFFClock::set_clock(double pts, int serial, double time)
{
    d_ptr->pts = pts;
    d_ptr->last_updated = time;
    d_ptr->pts_drift = pts - time;
    d_ptr->serial = serial;
}

void HFFClock::set_clock_speed(double speed)
{
    sync_clock();
    d_ptr->speed = speed;
}

void HFFClock::sync_clock()
{
    set_clock(get_clock(), d_ptr->serial);
}

void HFFClock::sync_clock(HFFClock *slave)
{
    double clock1 = get_clock();
    double clock2 = slave->get_clock();
    if (!isnan(clock2) && (isnan(clock1) || fabs(clock1 - clock2) > AV_SYNC_THRESHOLD_NO))
        set_clock(clock2, slave->d_ptr->serial);
}

double HFFClock::get_clock()
{
    if (d_ptr->queue_serial != nullptr && *d_ptr->queue_serial != d_ptr->serial)
        return NAN;
    if (d_ptr->paused)
        return d_ptr->pts;
    auto time = av_gettime_relative() / 1000000.0;
    return d_ptr->pts_drift + time - (time - d_ptr->last_updated) * (1.0 - d_ptr->speed);
}

HFFPacketQueue::HFFPacketQueue(QObject *parent) :
    QObject(parent),
    d_ptr(new HFFPacketQueuePrivate)
{
}

HFFPacketQueue::~HFFPacketQueue()
{
    flush();
}

bool HFFPacketQueue::abort_request()
{
    return d_ptr->abort_request;
}

int HFFPacketQueue::remaining()
{
    return d_ptr->cache.size();
}

int *HFFPacketQueue::serial()
{
    return &d_ptr->serial;
}

int HFFPacketQueue::size()
{
    return d_ptr->size;
}

bool HFFPacketQueue::has_enough_packets(double tb)
{
    if (d_ptr->abort_request)
        return true;
    return  d_ptr->cache.size() > MIN_PACKETS && (!d_ptr->duration || tb * d_ptr->duration > 1.0);
}

//int64_t HFFPacketQueue::duration()
//{
//    return d_ptr->duration;
//}

void HFFPacketQueue::start()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->abort_request = false;
    put_in(&flush_pkt);
}

void HFFPacketQueue::abort()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->abort_request = true;
    d_ptr->cond.wakeOne();
}

void HFFPacketQueue::flush()
{
    QMutexLocker locker(&d_ptr->mutex);
    for (auto v : d_ptr->cache)
        av_packet_unref(&v->pkt);
    qDeleteAll(d_ptr->cache);
    d_ptr->cache.clear();
    d_ptr->size = 0;
    d_ptr->duration = 0;
}

bool HFFPacketQueue::put(AVPacket *pkt)
{
    QMutexLocker locker(&d_ptr->mutex);
    if (put_in(pkt))
        return true;
    if(pkt != &flush_pkt)
        av_packet_unref(pkt);
    return false;
}
// return -1(aborted), 0(no packet), 1(packet)
int HFFPacketQueue::get(AVPacket *pkt, bool block, int *serial)
{
    QMutexLocker locker(&d_ptr->mutex);
    while (true)
    {
        if (d_ptr->abort_request)
            return -1;
        if (!d_ptr->cache.isEmpty())
        {
            auto v = d_ptr->cache.dequeue();
            *pkt = v->pkt;
            if (serial)
                *serial = v->serial;
            d_ptr->size -= pkt->size;
            d_ptr->duration -= pkt->duration;
            delete v;
            return 1;
        }
        if (!block)
            return 0;
        d_ptr->cond.wait(&d_ptr->mutex);
    }
}

bool HFFPacketQueue::put_in(AVPacket *pkt)
{
    if (d_ptr->abort_request)
        return false;

    if (pkt == &flush_pkt)
        d_ptr->serial++;

    auto pkt1 = new HFFPacket;
    pkt1->pkt = *pkt;
    pkt1->serial = d_ptr->serial;
    d_ptr->cache.enqueue(pkt1);

    d_ptr->size += pkt->size;
    d_ptr->duration += pkt->duration;
    d_ptr->cond.wakeOne();
    return true;
}

HFFFrameQueue::HFFFrameQueue(QObject *parent) :
    QObject(parent),
    d_ptr(new HFFFrameQueuePrivate)
{
}

HFFFrameQueue::~HFFFrameQueue()
{
    flush();
}

// return the number of undisplayed frames in the queue
int HFFFrameQueue::remaining()
{
    return d_ptr->size - d_ptr->rindex_shown;
}

int HFFFrameQueue::rindex_shown()
{
    return d_ptr->rindex_shown;
}

HFFFrame *HFFFrameQueue::peek()
{
    return peek(d_ptr->rindex + d_ptr->rindex_shown);
}

HFFFrame *HFFFrameQueue::peek_next()
{
    return peek(d_ptr->rindex + d_ptr->rindex_shown + 1);
}

HFFFrame *HFFFrameQueue::peek_last()
{
    return peek(d_ptr->rindex);
}

HFFFrame *HFFFrameQueue::peek_writeable()
{
    QMutexLocker locker(&d_ptr->mutex);
    // wait until we have space to put a new frame
    while (!d_ptr->abort_request && d_ptr->size >= d_ptr->cache.size())
        d_ptr->cond.wait(&d_ptr->mutex);
    if (d_ptr->abort_request)
        return nullptr;
    return peek(d_ptr->windex);
}

HFFFrame *HFFFrameQueue::peek_readable()
{
    QMutexLocker locker(&d_ptr->mutex);
    // wait until we have a readable a new frame
    while (!d_ptr->abort_request && d_ptr->size - d_ptr->rindex_shown <= 0)
        d_ptr->cond.wait(&d_ptr->mutex);
    if (d_ptr->abort_request)
        return nullptr;
    return peek(d_ptr->rindex + d_ptr->rindex_shown);
}

void HFFFrameQueue::init(int max_size, bool keep_last)
{
    flush();
    for (int i = 0; i < max_size; i++)
    {
        auto frame = new HFFFrame;
        frame->frame = av_frame_alloc();
        d_ptr->cache.append(frame);
    }
    d_ptr->keep_last = keep_last;
}

void HFFFrameQueue::start()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->abort_request = false;
}

void HFFFrameQueue::abort()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->abort_request = true;
    d_ptr->cond.wakeOne();
}

void HFFFrameQueue::flush()
{
    for (auto v : d_ptr->cache)
    {
        unref_item(v);
        av_frame_free(&v->frame);
    }
    qDeleteAll(d_ptr->cache);
    d_ptr->cache.clear();
    d_ptr->rindex = 0;
    d_ptr->rindex_shown = 0;
    d_ptr->windex = 0;
    d_ptr->size = 0;
    d_ptr->abort_request = true;
}

void HFFFrameQueue::push()
{
    if (++d_ptr->windex == d_ptr->cache.size())
        d_ptr->windex = 0;
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->size++;
    d_ptr->cond.wakeOne();
}

void HFFFrameQueue::next()
{
    if (d_ptr->keep_last && !d_ptr->rindex_shown)
    {
        d_ptr->rindex_shown = 1;
        return;
    }
    unref_item(peek(d_ptr->rindex));
    if (++d_ptr->rindex == d_ptr->cache.size())
        d_ptr->rindex = 0;
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->size--;
    d_ptr->cond.wakeOne();
}

void HFFFrameQueue::wake()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->cond.wakeAll();
}

HFFFrame *HFFFrameQueue::peek(int i)
{
    return d_ptr->cache.at(i % d_ptr->cache.size());
}

void HFFFrameQueue::unref_item(HFFFrame *p)
{
    av_frame_unref(p->frame);
 //   avsubtitle_free(&p->sub);
}

HE_CONTROL_END_NAMESPACE
