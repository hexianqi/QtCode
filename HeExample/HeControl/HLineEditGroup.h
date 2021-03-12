/***************************************************************************************************
**      2019-12-20  HLineEditGroup 行编辑器组(编辑完成自动移动焦点)。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QLineEdit;

HE_CONTROL_BEGIN_NAMESPACE

class HLineEditGroupPrivate;

class HLineEditGroup : public QObject
{
    Q_OBJECT

public:
    explicit HLineEditGroup(QObject *parent = nullptr);
    ~HLineEditGroup() override;

public:
    void addLineEdit(QLineEdit *);
    void removeLineEdit(QLineEdit *);
    QList<QLineEdit *> lineEdits() const;

protected:
    HLineEditGroup(HLineEditGroupPrivate &p, QObject *parent = nullptr);

protected slots:
    void next();

protected:
    QScopedPointer<HLineEditGroupPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
