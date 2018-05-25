#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeController/HControllerGlobal.h"
#include <QMainWindow>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HMainWindowPrivate;

class HE_GUI_EXPORT HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow();

signals:

public slots:

public:
    virtual void init();
    virtual void setModel(IModel *model);

protected:
    HMainWindow(HMainWindowPrivate &p, QWidget *parent = nullptr);

protected slots:
    void showDeviceFailed(QString text);
    void showActionFailed(HActionType action, QString text);
    void updateStatusBar(QStringList list);
    void updateLabel(QString name, int state);

protected:
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_H
