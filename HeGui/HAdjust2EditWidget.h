#pragma once

#include "IDataEditer.h"
#include "HeCore/HActionType.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HAdjust2EditWidget;
}

HE_BEGIN_NAMESPACE

class IAdjust2;
class HAdjust2EditWidgetPrivate;

class HAdjust2EditWidget : public QWidget, public IDataEditer<IAdjust2>
{
    Q_OBJECT

public:
    explicit HAdjust2EditWidget(QWidget *parent = nullptr);
    ~HAdjust2EditWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QWidget *widget() override;
    IAdjust2 *createData() override;
    void setData(IAdjust2 *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

protected:
    void handleAction(HActionType action);
    void handleStateChanged(bool b);
    void handleResultChanged();
    void setCurrentIndex(QModelIndex index);
    void setListModel(const QStringList &names, const QString &name);
    void showItem();
    void saveItem();
    void clearItem();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    void init();
    void initSelected();

private:
    QScopedPointer<HAdjust2EditWidgetPrivate> d_ptr;
    Ui::HAdjust2EditWidget *ui;
};

HE_END_NAMESPACE
