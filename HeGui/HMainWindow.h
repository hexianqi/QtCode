#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "HGuiGlobal.h"
#include <QMainWindow>

HE_GUI_BEGIN_NAMESPACE

class HMainWindowPrivate;

class HE_GUI_EXPORT HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow();

public:
    virtual void init();

signals:

public slots:

protected:
    HMainWindow(HMainWindowPrivate &p, QWidget *parent = nullptr);

//protected:
//    void setModel(IModel *model);


protected:


protected:
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_H
