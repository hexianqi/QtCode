/***************************************************************************************************
**      2019-08-02  HConfigWidget
***************************************************************************************************/

#ifndef HCONFIGWIDGET_H
#define HCONFIGWIDGET_H

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HConfigWidgetPrivate;

class HConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex STORED true)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(int count READ count)

public:
    explicit HConfigWidget(QWidget *parent = nullptr);
    ~HConfigWidget() override;

signals:
    void currentIndexChanged(int);
    void saving();
    void applying(int);
    void discarding(int);

public:
    int currentIndex() const;
    QSize iconSize() const;
    int count() const;
    QWidget *group(int) const;
    QWidget *currentGroup() const;

public:
    void addGroup(QWidget *, const QIcon &icon = QIcon(), const QString &name = QString());
    void insertGroup(int index, QWidget *, const QIcon &icon = QIcon(), const QString &name = QString());
    void removeGroup(QWidget *);
    void removeGroup(int);

public slots:
    void setCurrentIndex(int value);
    void setIconSize(const QSize &);
    void setCurrentGroup(QWidget *);
    void setGroupIcon(int, const QIcon &);
    void setGroupLabel(int, const QString &);
    void save();
    void apply();
    void discard();

protected:
    HConfigWidget(HConfigWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    QScopedPointer<HConfigWidgetPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HCONFIGWIDGET_H
