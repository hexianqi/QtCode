#ifndef HPROTOCOLINFO_H
#define HPROTOCOLINFO_H

#include "IProtocolInfo.h"
#include <QSharedDataPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolInfoPrivate;

class HProtocolInfo : public IProtocolInfo
{
public:
    HProtocolInfo();
    HProtocolInfo(const HProtocolInfo &);
    HProtocolInfo &operator=(const HProtocolInfo &);
    virtual ~HProtocolInfo();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) override;
    virtual void setPortNum(int num = 0) override;
    virtual void setDeviceID(int id) override;
    virtual void addActionParam(HActionType key, QList<uchar> value) override;

public:
    virtual IPort *port() override;
    virtual int portNum() override;
    virtual bool isPortNumScan() override;
    virtual int deviceID() override;
    virtual QList<uchar> actionParam(HActionType key) override;

protected:
    HProtocolInfo(HProtocolInfoPrivate &p);

protected:
    QSharedDataPointer<HProtocolInfoPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLINFO_H
