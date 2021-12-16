#include "HMimeInlineFile_p.h"

HE_BEGIN_NAMESPACE

HMimeInlineFile::HMimeInlineFile(const QString &fileName, QObject *parent) :
    HMimeFile(*new HMimeInlineFilePrivate, fileName, parent)
{
}

HMimeInlineFile::HMimeInlineFile(HMimeInlineFilePrivate &p, const QString &fileName, QObject *parent) :
    HMimeFile(p, fileName, parent)
{
}

void HMimeInlineFile::prepare()
{
    Q_D(HMimeInlineFile);
    d->header += "Content-disposition: inline\r\n";
    HMimeFile::prepare();
}

HE_END_NAMESPACE
