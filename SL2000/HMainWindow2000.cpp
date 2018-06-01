#include "HMainWindow2000_p.h"
#include "HModel2000.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/HTestDataFactory.h"
#include "HeController/HTestSpec.h"
#include <QMessageBox>
#include <QTimer>
#include <QSettings>

HE_CONTROLLER_USE_NAMESPACE

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q)
    : HMainWindowPrivate(q)
{
}


HMainWindow2000::HMainWindow2000(QWidget *parent)
    : HMainWindow(*new HMainWindow2000Private(this), parent)
{

}

HMainWindow2000::HMainWindow2000(HMainWindow2000Private &p, QWidget *parent)
    : HMainWindow(p, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
}

