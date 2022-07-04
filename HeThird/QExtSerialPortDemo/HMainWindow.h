#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
class HMainWindow;
}

class HMainWindowPrivate;

class HMainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow)

public:
    explicit HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow() override;

protected:
    void readSettings();
    void writeSettings();
    void init();
    void updateUI(bool b);

protected slots:
    void readData();
    void writeData(QString data);
    void sendData();
    void saveData();
    void append(int type, const QString &data);
    void clear();

protected slots:
    void on_btnOpen_clicked();
    void on_btnSendCount_clicked();
    void on_btnReceiveCount_clicked();
    void on_btnStopShow_clicked();
    void on_btnData_clicked();
    void on_ckAutoSend_stateChanged(int);
    void on_ckAutoSave_stateChanged(int);

private:
    Ui::HMainWindow *ui;
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

