/***************************************************************************************************
**      2019-09-03  HStateProgressBar 状态进度条控件
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HStateProgressBarPrivate;

class HStateProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString tip READ tip WRITE setTip)
    Q_PROPERTY(StateStyle stateStyle READ stateStyle WRITE setStateStyle)
    Q_PROPERTY(QColor barColor READ barColor WRITE setBarColor)
    Q_PROPERTY(QColor barBackground READ barBackground WRITE setBarBackground)
    Q_PROPERTY(QColor noteColor READ noteColor WRITE setNoteColor)
    Q_PROPERTY(QColor stateColor READ stateColor WRITE setStateColor)
    Q_PROPERTY(QColor tipColor READ tipColor WRITE setTipColor)
    Q_PROPERTY(QColor tipBackground READ tipBackground WRITE setTipBackground)

public:
    enum StateStyle
    {
        StateStyle_NACK,
        StateStyle_ACK
    };
    Q_ENUM(StateStyle)

public:
    explicit HStateProgressBar(QWidget *parent = nullptr);
    ~HStateProgressBar() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QString tip() const;
    StateStyle stateStyle() const;
    QColor barColor() const;
    QColor barBackground() const;
    QColor noteColor() const;
    QColor stateColor() const;
    QColor tipColor() const;
    QColor tipBackground() const;

public slots:
    void setTip(const QString &value);
    void setNotes(const QStringList &value);
    void setStates(const QStringList &value);
    void setStateStyle(StateStyle value);
    void setBarColor(const QColor &value);
    void setBarBackground(const QColor &value);
    void setNoteColor(const QColor &value);
    void setStateColor(const QColor &value);
    void setTipColor(const QColor &value);
    void setTipBackground(const QColor &value);
    void setValue(int value);
    void setMaximum(int value);

protected:
    HStateProgressBar(HStateProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawBackground(QPainter *);
    void drawBarBackground(QPainter *);
    void drawBar(QPainter *);
    void drawBarNumber(QPainter *);
    void drawNote(QPainter *, int index, const QColor &color);
    void drawState(QPainter *, int index, const QColor &color);
    void drawTip(QPainter *, int index);

protected:
    QScopedPointer<HStateProgressBarPrivate> d_ptr;
};

HE_END_NAMESPACE
