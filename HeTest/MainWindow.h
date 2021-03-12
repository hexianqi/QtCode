#pragma once

#include <QtWidgets/QMainWindow>

class QProgressDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void paintEvent(QPaintEvent *);

public slots:
    void on_pushButton_clicked();
    void test();

private:
    Ui::MainWindow *ui;
    QProgressDialog *_progressDialog;
    QTimer *_timer;
    int _testValue;
    QVector<int> _testVector;
};
