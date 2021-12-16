/***************************************************************************************************
**      2019-07-31  HColorModel
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtGui/QStandardItemModel>

HE_BEGIN_NAMESPACE

class HColorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit HColorModel(QObject *parent = nullptr);

public:
    QModelIndex contains(const QColor &);
    QModelIndex addColor(const QColor &color, const QString &name = QString());
    QModelIndex insertColor(int index, const QColor &color, const QString &name = QString());
    void setStandardColors();
    void setColors(const QStringList &value);

public:
    QStringList colors() const;
    HColorModel *clone(QObject *parent = nullptr) const;
};

HE_END_NAMESPACE
