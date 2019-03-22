/***************************************************************************************************
**      2019-03-22  HHexSpinBox 16进制调节框类。
***************************************************************************************************/

#ifndef HHEXSPINBOX_H
#define HHEXSPINBOX_H

#include <QSpinBox>
#include <QtUiPlugin/QDesignerExportWidget>

class HHexSpinBoxPrivate;

class QDESIGNER_WIDGET_EXPORT HHexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit HHexSpinBox(QWidget *parent = nullptr);
    ~HHexSpinBox();

protected:
    HHexSpinBox(HHexSpinBoxPrivate &p, QWidget *parent = nullptr);

protected:
    QValidator::State validate(QString &text, int &pos) const override;
    int valueFromText(const QString &text) const override;
    QString textFromValue(int value) const override;

private:
    void init();

protected:
    QScopedPointer<HHexSpinBoxPrivate> d_ptr;
};

#endif // HHEXSPINBOX_H
