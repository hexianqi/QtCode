/***************************************************************************************************
**      2022-07-14  HStationWidget
***************************************************************************************************/

#pragma once

#include <QtWidgets/QWidget>

class HStationWidgetPrivate;

class HStationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HStationWidget(int index, QWidget *parent = nullptr);
    ~HStationWidget() override;

signals:
    void workStateChanged(int, bool);
    void specStateChanged(int, bool);
    void elecStateChanged(int, bool);

protected slots:
    void setStackedCurrentIndex(int);


protected:
    void initialize(int index);
    void createAction();
    void createToolBar();
    void createWidget();
    void createThread();
    void initWidget();
    void clearResult();
//    virtual void saveResult();
//    virtual void exportExcel() = 0;
//    virtual void readSettings();
//    virtual void writeSettings();


protected:
    QScopedPointer<HStationWidgetPrivate> d_ptr;
};



