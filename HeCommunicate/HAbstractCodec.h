/***************************************************************************************************
**      2019-04-08  HAbstractCodec 抽象编码类。
***************************************************************************************************/

#ifndef HABSTRACTCODEC_H
#define HABSTRACTCODEC_H

#include "ICodec.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractCodecPrivate;

class HAbstractCodec : public ICodec
{
public:
    explicit HAbstractCodec();
    virtual ~HAbstractCodec() = default;

protected:
    HAbstractCodec(HAbstractCodecPrivate &);

protected:
    QScopedPointer<HAbstractCodecPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE


#endif // HABSTRACTCODEC_H
