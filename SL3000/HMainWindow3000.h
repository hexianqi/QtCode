#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
class HMainWindow3000;
}

class HMainWindow3000Private;

class HMainWindow3000 : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindow3000(QWidget *parent = nullptr);
    ~HMainWindow3000();

protected:
    void initialize();
//    void initImportExport();
//    void createAction();
//    void createMenu();
//    void createToolBar();
    void createToolBarLogo();
//    void initMenu();
    void initToolBar();
    void initStatusBar();
//    void initBuilder() = 0;
//    void initModel();
    void initCentralWidget();
    void initWindow();
    void initTimer();
    void readSettings();
    void writeSettings();

protected slots:
    void updateTime();

private:
    QScopedPointer<HMainWindow3000Private> d_ptr;
    Ui::HMainWindow3000 *ui;
};
