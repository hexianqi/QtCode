/***************************************************************************************************
**      2019-06-04  HControlTester 测试类。
***************************************************************************************************/

#ifndef HCONTROLTESTER_H
#define HCONTROLTESTER_H

#include "HControlGlobal.h"
#include <QtCore/QVariant>

class QTableView;
class QTableWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HE_CONTROL_EXPORT HControlTester : public QObject
{
    Q_OBJECT

public:
    explicit HControlTester(QObject *parent = nullptr);
    ~HControlTester() override;

public:
    // 多标题表格
    static QTableView *multHeaderTableView();
    static QTableWidget *multHeaderTableWidget();

public:
    QWidget *createWidget(QString type, QWidget *parent = nullptr);

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLTESTER_H
