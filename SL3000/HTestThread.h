/***************************************************************************************************
**      2022-07-27  HTestThread
***************************************************************************************************/

#pragma once

#include <QtCore/QThread>

class HTestThreadPrivate;

class HTestThread : public QThread
{
    Q_OBJECT

public:
    explicit HTestThread(int index, QObject *parent = nullptr);
    ~HTestThread() override;

public:
    void stop();

protected:
    void run() override;

protected:
    QScopedPointer<HTestThreadPrivate> d_ptr;
};



