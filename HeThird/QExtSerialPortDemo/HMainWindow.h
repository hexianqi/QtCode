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

private:
    Ui::HMainWindow *ui;
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

