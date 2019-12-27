#include "HMimeInlineFile_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HMimeInlineFile::HMimeInlineFile(QString fileName, QObject *parent) :
    HMimeFile(*new HMimeInlineFilePrivate, fileName, parent)
{
}

HMimeInlineFile::HMimeInlineFile(HMimeInlineFilePrivate &p, QString fileName, QObject *parent) :
    HMimeFile(p, fileName, parent)
{
}

HMimeInlineFile::~HMimeInlineFile()
{
}

void HMimeInlineFile::prepare()
{
    Q_D(HMimeInlineFile);
    d->header += "Content-disposition: inline\r\n";
    HMimeFile::prepare();
}

HE_CONTROL_END_NAMESPACE
