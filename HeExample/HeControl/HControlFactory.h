/***************************************************************************************************
**      2019-06-04  HControlTester 测试类。
***************************************************************************************************/

#ifndef HCONTROLFACTORY_H
#define HCONTROLFACTORY_H

#include "IControlFactory.h"

class QTableView;
class QTableWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HControlFactoryPrivate;

class HE_CONTROL_EXPORT HControlFactory : public QObject, public IControlFactory
{
    Q_OBJECT

public:
    explicit HControlFactory(QObject *parent = nullptr);
    ~HControlFactory() override;

public:
    // 多标题表格
    static QTableView *multHeaderTableView();
    static QTableWidget *multHeaderTableWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList keys() override;
    QWidget *createWidget(QString type, QWidget *parent = nullptr) override;

protected:
    QScopedPointer<HControlFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLFACTORY_H
