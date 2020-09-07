#pragma once

#include "HPropertyBrowser.h"
#include <QtCore/QMap>

class QtTreePropertyBrowser;
class QtVariantProperty;
class QtVariantPropertyManager;

HE_CONTROL_BEGIN_NAMESPACE

class HPropertyBrowserPrivate
{
public:
    void addClassProperties(const QMetaObject *);
    void updateClassProperties(const QMetaObject *, bool recursive);

public:
    bool showParent = true;
    QObject *object = nullptr;
    QList<QtProperty *> topLevelProperties;
    QMap<const QMetaObject *, QtProperty *> classToProperty;
    QMap<QtProperty *, const QMetaObject *> propertyToClass;
    QMap<QtProperty *, int> propertyToIndex;
    QMap<const QMetaObject *, QMap<int, QtVariantProperty *>> classToIndexToProperty;
    QtTreePropertyBrowser *browser = nullptr;
    QtVariantPropertyManager *manager = nullptr;
    QtVariantPropertyManager *readOnlyManager = nullptr;
};

HE_CONTROL_END_NAMESPACE
