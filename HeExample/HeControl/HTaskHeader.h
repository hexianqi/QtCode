/***************************************************************************************************
**      2019-08-09  HTaskHeader
***************************************************************************************************/

#ifndef HTASKHEADER_H
#define HTASKHEADER_H

#include "HControlGlobal.h"
#include <QtWidgets/QFrame>

class QToolButton;

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HTASKHEADER_H
