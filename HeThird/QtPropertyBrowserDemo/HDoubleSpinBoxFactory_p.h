#pragma once

#include "HDoubleSpinBoxFactory.h"
#include <QtCore/QMap>

class QDoubleSpinBox;
class QtDoubleSpinBoxFactory;

class HDoubleSpinBoxFactoryPrivate
{
public:
    QtDoubleSpinBoxFactory *factory;
    QMap<QtProperty *, QList<QDoubleSpinBox *>> propertyToEditor;
    QMap<QDoubleSpinBox *, QtProperty *> editorToProperty;
};



