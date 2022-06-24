#pragma once

#include <QtWidgets/QWidget>

class HDemoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HDemoWidget(QWidget *parent = nullptr);

protected:
    void init();
};

