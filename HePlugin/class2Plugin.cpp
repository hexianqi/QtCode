#include "class2.h"
#include "class2Plugin.h"
#include <QtPlugin>

class2Plugin::class2Plugin(QObject *parent)
    : QObject(parent)
{
    _initialized = false;
}

void class2Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (_initialized)
        return;

    // Add extension registrations, etc. here

    _initialized = true;
}

bool class2Plugin::isInitialized() const
{
    return _initialized;
}

QWidget *class2Plugin::createWidget(QWidget *parent)
{
    return new class2(parent);
}

QString class2Plugin::name() const
{
    return QLatin1String("class2");
}

QString class2Plugin::group() const
{
    return QLatin1String("");
}

QIcon class2Plugin::icon() const
{
    return QIcon();
}

QString class2Plugin::toolTip() const
{
    return QLatin1String("");
}

QString class2Plugin::whatsThis() const
{
    return QLatin1String("");
}

bool class2Plugin::isContainer() const
{
    return false;
}

QString class2Plugin::domXml() const
{
    return QLatin1String("<widget class=\"class2\" name=\"class2\">\n</widget>\n");
}

QString class2Plugin::includeFile() const
{
    return QLatin1String("class2.h");
}

