/***************************************************************************************************
**      2019-07-31  HClearLineEdit
***************************************************************************************************/

#ifndef HCLEARLINEEDIT_H
#define HCLEARLINEEDIT_H

#include "HButtonLineEdit.h"

HE_CONTROL_BEGIN_NAMESPACE

class HClearLineEditPrivate;

class HClearLineEdit : public HButtonLineEdit
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HClearLineEdit)

public:
    explicit HClearLineEdit(QWidget *parent = nullptr);
    ~HClearLineEdit() override;

public slots:
    void setButtonVisible(bool b) override;

protected:
    HClearLineEdit(HClearLineEditPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HCLEARLINEEDIT_H
