/***************************************************************************************************
**      2019-06-12  HFaltStyle
***************************************************************************************************/

#ifndef HFALTSTYLE_H
#define HFALTSTYLE_H

#include "HAbstractStyle.h"

class QPushButton;
class QLineEdit;
class QProgressBar;
class QSlider;
class QRadioButton;
class QCheckBox;
class QScrollBar;

HE_CONTROL_BEGIN_NAMESPACE

class HFaltStylePrivate;

class HFaltStyle : public HAbstractStyle
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFaltStyle)

public:
    explicit HFaltStyle(QObject *parent = nullptr);
    ~HFaltStyle() override;

public:
    QString typeName() override;

public:
    QString pushButton(QVariantMap param = QVariantMap()) override;
    QString lineEdit(QVariantMap param = QVariantMap()) override;
    QString progressBar(QVariantMap param = QVariantMap()) override;
    QString slider(QVariantMap param = QVariantMap()) override;
    QString radioButton(QVariantMap param = QVariantMap()) override;
    QString checkBox(QVariantMap param = QVariantMap()) override;
    QString scrollBar(QVariantMap param = QVariantMap()) override;

public:
    void setStyle(QPushButton *obj,
                  int padding = 8,                          // 间距
                  int radius = 5,                           // 圆角半径
                  QString normalColor = "#E6F8F5",          // 文字颜色
                  QString normalBackground = "#1ABC9C",     // 背景颜色
                  QString hoverColor = "#FFFFFF",           // 悬停颜色
                  QString hoverBackground = "#2EE1C1",      // 悬停背景颜色
                  QString pressedColor = "#A7EEE6",         // 按下颜色
                  QString pressedBackground = "#16A086");   // 按下背景颜色
    void setStyle(QLineEdit *obj,
                  int padding = 8,                          // 间距
                  int radius = 3,                           // 圆角半径
                  int borderWidth = 2,                      // 边框大小
                  QString normalColor = "#DCE4EC",          // 正常颜色
                  QString focusColor = "#1ABC9C");          // 选中颜色
    void setStyle(QProgressBar *obj,
                  int fontSize = 9,                         // 文字字号
                  int height = 8,                           // 高度
                  int radius = 5,                           // 圆角半径
                  QString normalColor = "#E8EDF2",          // 正常颜色
                  QString chunkColor = "#1ABC9C");          // 进度颜色
    void setStyle(QSlider *obj,
                  int height = 8,                           // 高度
                  QString normalColor = "#E8EDF2",          // 正常颜色
                  QString grooveColor = "#1ABC9C",          // 滑块颜色
                  QString handleColor = "#1ABC9C");         // 指示器颜色
    void setStyle(QRadioButton *obj,
                  int radius = 8,                           // 指示器圆角半径
                  QString uncheckColor = "#D7DBDE",         // 未选中颜色
                  QString checkColor = "#1ABC9C");          // 选中颜色
    void setStyle(QCheckBox *obj,
                  int radius = 3,                           // 指示器圆角半径
                  QString uncheckColor = "#D7DBDE",         // 未选中颜色
                  QString checkColor = "#1ABC9C");          // 选中颜色
    void setStyle(QScrollBar *obj,
                  int radius = 6,                           // 圆角半径
                  int min = 120,                            // 指示器最小长度
                  int max = 12,                             // 滚动条最大长度
                  QString background = "#E8EDF2",           // 背景色
                  QString handleNormalColor = "#1ABC9C",    // 指示器正常颜色
                  QString handleHoverColor = "#3498DB",     // 指示器悬停颜色
                  QString handlePressedColor = "#E74C3C");  // 指示器按下颜色

protected:
    HFaltStyle(HFaltStylePrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HFALTSTYLE_H
