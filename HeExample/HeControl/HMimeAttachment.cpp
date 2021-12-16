#include "HMimeAttachment_p.h"

HE_BEGIN_NAMESPACE

HMimeAttachment::HMimeAttachment(const QString &fileName, QObject *parent) :
    HMimeFile(*new HMimeAttachmentPrivate, fileName, parent)
{
}

HMimeAttachment::HMimeAttachment(HMimeAttachmentPrivate &p, const QString &fileName, QObject *parent) :
    HMimeFile(p, fileName, parent)
{
}

void HMimeAttachment::prepare()
{
    Q_D(HMimeAttachment);
    d->header += "Content-disposition: attachment\r\n";
    HMimeFile::prepare();
}

HE_END_NAMESPACE
