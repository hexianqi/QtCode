#pragma once

#include "IDataEditWidget.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HAdjust2EditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IAdjust2;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjust2EditWidgetPrivate;

class HAdjust2EditWidget : public IDataEditWidget<IAdjust2>
{
    Q_OBJECT

public:
    explicit HAdjust2EditWidget(QWidget *parent = nullptr);
    ~HAdjust2EditWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
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

HE_GUI_END_NAMESPACE
