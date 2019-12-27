#include "HMimeAttachment_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HMimeAttachment::HMimeAttachment(QString fileName, QObject *parent) :
    HMimeFile(*new HMimeAttachmentPrivate, fileName, parent)
{
}

HMimeAttachment::HMimeAttachment(HMimeAttachmentPrivate &p, QString fileName, QObject *parent) :
    HMimeFile(p, fileName, parent)
{
}

HMimeAttachment::~HMimeAttachment()
{
}

void HMimeAttachment::prepare()
{
    Q_D(HMimeAttachment);
    d->header += "Content-disposition: attachment\r\n";
    HMimeFile::prepare();
}

HE_CONTROL_END_NAMESPACE
