/***************************************************************************************************
**      2019-08-01  HColorComboBox
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QComboBox>

HE_CONTROL_BEGIN_NAMESPACE

class HColorComboBoxPrivate;

class HColorComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QStringList colors READ colors WRITE setColors)
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor)
    Q_PROPERTY(bool colorDialogEnabled READ isColorDialogEnabled WRITE setColorDialogEnabled)
    Q_PROPERTY(int colorCount READ colorCount)

public:
    explicit HColorComboBox(QWidget *parent = nullptr);
    ~HColorComboBox() override;

signals:
    void colorPicked(const QColor &);

public:
    QStringList colors() const;
    QColor currentColor() const;
    QColor color(int index) const;
    bool isColorDialogEnabled() const;
    int colorCount() const;

public slots:
    void setColors(const QStringList &);
    void setCurrentColor(const QColor &);
    void setColorDialogEnabled(bool b = true);
    void setStandardColors();
    void addColor(const QColor &color, const QString &name);
    void insertColor(int index, const QColor &color, const QString &name);

protected:
    HColorComboBox(HColorComboBoxPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void dragEnterEvent(QDragEnterEvent *) override;
    void dropEvent(QDropEvent *) override;

protected slots:
    void handleActivated(int index);
    void popupDialog();

protected:
    QScopedPointer<HColorComboBoxPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
