#include "HAbout.h"
#include <QMessageBox>
#include <QApplication>
#include "HeCore/HAppContext.h"

HE_GUI_BEGIN_NAMESPACE

void HAbout::initialize(QVariantMap /*param*/)
{
}

QString HAbout::typeName()
{
    return "HAbout";
}

void HAbout::execute(QObject *sender, QVariantMap param)
{
    auto parent = HAppContext::getContextPointer<QWidget>("MainWindow");
    auto abbreviation = QApplication::applicationName().split(" ").first();
    auto text = tr("<h2>%1</h2><p>").arg(abbreviation)
            + tr("<p>版本 %1<p>").arg(QApplication::applicationVersion())
            + tr("<p>%1<p>").arg(QApplication::applicationName())
            + tr("<p>版权 2010-2019 %1. 保留所有权利. <p>").arg(QApplication::organizationName())
            + tr("<p>%1<p>").arg(param.value("data").toString());
    QMessageBox::about(parent, tr("关于 %1").arg(abbreviation), text);
}

HE_GUI_END_NAMESPACE
