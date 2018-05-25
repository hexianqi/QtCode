#include "HMainWindow_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HAction.h"
#include "HAbout.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HMainWindowPrivate::HMainWindowPrivate(HMainWindow *p)
    : q_ptr(p)
{
}

HMainWindow::HMainWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new HMainWindowPrivate(this))
{
    init();
}

HMainWindow::HMainWindow(HMainWindowPrivate &p, QWidget *parent)
    : QMainWindow(parent), d_ptr(&p)
{
    init();
}

HMainWindow::~HMainWindow()
{
    qDebug() << "HMainWindow Destroy";
}

void HMainWindow::init()
{
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    setAttribute(Qt::WA_DeleteOnClose, true);

    auto action = new HAction(this);
    action->setText("关于");
    action->setHandler(new HAbout);
    menuBar()->addAction(action);
}

void HMainWindow::setModel(IModel *model)
{
    d_ptr->model = model;
    d_ptr->model->setParent(this);
    connect(d_ptr->model, &IModel::deviceFailed, this, &HMainWindow::showDeviceFailed);
    connect(d_ptr->model, &IModel::actionFailed, this, &HMainWindow::showActionFailed);
    connect(d_ptr->model, &IModel::initThreadFinished, this, &HMainWindow::updateStatusBar);
    connect(d_ptr->model, &IModel::threadStateChanged, this, &HMainWindow::updateLabel);
    //    connect(d->model, &IModel::actionFinished, this, [=](HActionType action) { QMessageBox::information(this, "", toComment(action)); });
    d_ptr->model->initConfig();
}

void HMainWindow::showDeviceFailed(QString text)
{
    QMessageBox::critical(this, "", text);
#ifndef QT_DEBUG
    close();
#endif
}

void HMainWindow::showActionFailed(HActionType action, QString text)
{
    Q_UNUSED(action);
    QMessageBox::warning(this, "", text);
}

void HMainWindow::updateStatusBar(QStringList list)
{
    for (auto w : d_ptr->labels)
        statusBar()->removeWidget(w);
    d_ptr->labels.clear();
    for (auto s : list)
    {
        auto l = new QLabel;
        l->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(s));
        d_ptr->labels.insert(s, l);
        statusBar()->addWidget(l);
    }
}

void HMainWindow::updateLabel(QString name, int state)
{
    if (!d_ptr->labels.contains(name))
        return;
    if (state == 1)
        d_ptr->labels.value(name)->setText(tr("%1:<font color=#00FF00>开启</font>").arg(name));
    else
        d_ptr->labels.value(name)->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(name));
}

HE_GUI_END_NAMESPACE
