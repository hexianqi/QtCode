/***************************************************************************************************
**      2019-08-01  HColorComboBox
***************************************************************************************************/

#ifndef HCOLORCOMBOBOX_H
#define HCOLORCOMBOBOX_H

#include "HControlGlobal.h"
#include <QtWidgets/QComboBox>

HE_CONTROL_BEGIN_NAMESPACE

class HColorComboBoxPrivate;

class HColorComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(bool colorDialogEnabled READ isColorDialogEnabled WRITE setColorDialogEnabled)
    Q_PROPERTY(int colorCount READ colorCount)
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor)
    Q_PROPERTY(QStringList colors READ colors WRITE setColors)

public:
    explicit HColorComboBox(QWidget *parent = nullptr);
    ~HColorComboBox() override;

signals:
    void activated(const QColor &);

public:
    QColor color(int index) const;
    bool isColorDialogEnabled() const;
    int colorCount() const;
    QColor currentColor() const;
    QStringList colors() const;

public slots:
    void setStandardColors();
    void addColor(const QColor &color, const QString &name);
    void insertColor(int index, const QColor &color, const QString &name);
    void setColorDialogEnabled(bool b = true);
    void setCurrentColor(const QColor &);
    void setColors(const QStringList &);

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

#endif // HCOLORCOMBOBOX_H
