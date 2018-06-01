#ifndef HMAINWINDOW2100_H
#define HMAINWINDOW2100_H

#include "HeGui/HMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindow2000Private;

class HMainWindow2000 : public HMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000)

public:
    explicit HMainWindow2000(QWidget *parent = 0);
    ~HMainWindow2000();

protected:
    HMainWindow2000(HMainWindow2000Private &p, QWidget *parent = nullptr);
};

#endif // HMAINWINDOW2100_H
