/***************************************************************************************************
**      2019-03-25  HProgressBar 带颜色的进度条类。
***************************************************************************************************/

#ifndef HPROGRESSBAR_H
#define HPROGRESSBAR_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QProgressBar>

class HProgressBarPrivate;

class QDESIGNER_WIDGET_EXPORT HProgressBar : public QProgressBar
{
    Q_OBJECT
     Q_PROPERTY(QColor colorProgress READ colorProgress WRITE setColorProgress)

public:
    explicit HProgressBar(QWidget *parent = nullptr);
    ~HProgressBar() override;

public:
    void setOrientation(Qt::Orientation);
    void setColorProgress(const QColor &);

public:
     QColor colorProgress() const;

protected:
    HProgressBar(HProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HProgressBarPrivate> d_ptr;

protected:
     void updateStyleSheet();

private:
    void init();
};

#endif // HPROGRESSBAR_H
