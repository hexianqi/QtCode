//#include "class1Plugin.h"
#include "class2Plugin.h"
#include "HCollectionInterface.h"

HCollectionInterface::HCollectionInterface(QObject *parent)
    : QObject(parent)
{
  //  m_widgets.append(new class1Plugin(this));
    _widgets.append(new class2Plugin(this));
}

QList<QDesignerCustomWidgetInterface*> HCollectionInterface::customWidgets() const
{
    return _widgets;
}
