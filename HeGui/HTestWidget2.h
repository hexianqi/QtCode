/***************************************************************************************************
**      2019-04-09  HTestWidget2 测试窗体。
***************************************************************************************************/

#ifndef HTESTWIDGET2_H
#define HTESTWIDGET2_H

#include "HTestWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HTestWidget2Private;

class HE_GUI_EXPORT HTestWidget2 : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2)

public:
    explicit HTestWidget2(QWidget *parent = nullptr);

protected:
    HTestWidget2(HTestWidget2Private &p, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *) override;
    void createAction() override;
    void exportExcel() override;
    void clearResult() override;
    virtual void printPreview();
    virtual void exportDatabase();
    virtual void exportDatabase(int index, int count = -1);
    virtual void exportDatabase2() = 0;
    QVariantMap toRecord();
    void saveRecord(bool append);
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET2_H
