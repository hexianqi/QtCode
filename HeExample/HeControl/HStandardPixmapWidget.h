#pragma once

#include <QtWidgets/QWidget>

class HStandardPixmapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HStandardPixmapWidget(QWidget *parent = nullptr);
    ~HStandardPixmapWidget() override;

protected:
    void init();
};

