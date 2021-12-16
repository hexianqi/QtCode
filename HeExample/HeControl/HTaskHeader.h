/***************************************************************************************************
**      2019-08-09  HTaskHeader
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QFrame>

class QToolButton;

HE_BEGIN_NAMESPACE

class HTaskHeaderPrivate;

class HTaskHeader : public QFrame
{
    Q_OBJECT

public:
    explicit HTaskHeader(QWidget *parent = nullptr);
    ~HTaskHeader() override;

public:
    QToolButton *toggleButton() const;

public:
    void setToggleIcon(const QIcon &);
    void setName(const QString &);
    void setIcon(const QIcon &);

protected:
    HTaskHeader(HTaskHeaderPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HTaskHeaderPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
