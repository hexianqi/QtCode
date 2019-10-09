/***************************************************************************************************
**      2016-10-16  HImageBrowser 图片浏览器
**                  http://www.qtcn.org/bbs/read-htm-tid-86001-ds-1.html#tpc
**                  1:增加鼠标右键清空
**                  2:增加设置背景色
**                  3:增加设置间距和翻页图标大小
**                  4:增加设置是否拉伸填充显示
**                  5:增加设置是否渐变显示图像
**                  6:增加设置键盘翻页
**                  7:增加移动到第一张/末一张/上一张/下一张
**                  8:修正内存泄露BUG及其他BUG
***************************************************************************************************/

#ifndef HIMAGEBROWSER_H
#define HIMAGEBROWSER_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HImageBrowserPrivate;

class HImageBrowser : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundStart READ backgroundStart WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd READ backgroundEnd WRITE setBackground)
    Q_PROPERTY(int bottomSpace READ bottomSpace WRITE setBottomSpace)
    Q_PROPERTY(int buttonSpace READ buttonSpace WRITE setButtonSpace)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(bool fill READ isFill WRITE setFill)
    Q_PROPERTY(bool fade READ isFade WRITE setFade)
    Q_PROPERTY(bool keyMove READ isKeyMove WRITE setKeyMove)

public:
    explicit HImageBrowser(QWidget *parent = nullptr);
    ~HImageBrowser() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    int bottomSpace() const;
    int buttonSpace() const;
    QSize iconSize() const;
    bool isFill() const;
    bool isFade() const;
    bool isKeyMove() const;

public slots:
    void load();
    void load(const QString &folder);
    void clear();
    void setBackgroundStart(const QColor &value);
    void setBackground(const QColor &value);
    void setBottomSpace(int value);
    void setButtonSpace(int value);
    void setIconSize(QSize value);
    void setFill(bool b);
    void setFade(bool b);
    void setKeyMove(bool b);

protected:
    HImageBrowser(HImageBrowserPrivate &p, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void showEvent(QShowEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawImage(QPainter *);

protected slots:
    void moveFirst();
    void movePrevious();
    void moveNext();
    void moveLast();
    void moveTo(int index);
    void doFading();
    void calcGeo();

protected:
    QScopedPointer<HImageBrowserPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HIMAGEBROWSER_H
