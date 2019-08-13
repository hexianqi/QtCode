/***************************************************************************************************
**      2019-08-08  HNumPad
***************************************************************************************************/

#ifndef HNUMPAD_H
#define HNUMPAD_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HNumPadPrivate;

class HNumPad : public QWidget
{
    Q_OBJECT

public:
    explicit HNumPad(QWidget *parent = nullptr);
    ~HNumPad() override;

signals:
    void numberClicked(int);
    void keyClicked(QString);
    void hashClicked();
    void asteriskClicked();

public slots:
    void animateClick(const QString &button, int msec = 100);

protected:
    HNumPad(HNumPadPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HNumPadPrivate> d_ptr;

private:
    void init();

private slots:
    void handleClicked(int);
};

HE_CONTROL_END_NAMESPACE

#endif // HNUMPAD_H
