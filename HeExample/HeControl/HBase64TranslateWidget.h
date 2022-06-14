#pragma once

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace Ui {
class HBase64TranslateWidget;
}

class HBase64TranslateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HBase64TranslateWidget(QWidget *parent = nullptr);
    ~HBase64TranslateWidget();

private:
    Ui::HBase64TranslateWidget *ui;
};

