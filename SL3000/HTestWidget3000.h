#pragma once

#include <QtWidgets/QWidget>

namespace Ui {
class HTestWidget3000;
}

class HTestWidget3000Private;

class HTestWidget3000 : public QWidget
{
    Q_OBJECT

public:
    explicit HTestWidget3000(QWidget *parent = nullptr);
    ~HTestWidget3000();

public:
    void setLedType();

protected:
    void initialize();

private:
    QScopedPointer<HTestWidget3000Private> d_ptr;
    Ui::HTestWidget3000 *ui;
};

