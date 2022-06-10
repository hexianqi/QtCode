#include "HControlDemoWidget_p.h"
#include "HButtonLineEdit.h"
#include "HClearLineEdit.h"
#include "HResetLineEdit.h"
#include "HFileChooser.h"
#include "HLongSpinBox.h"
#include "HTextSpinBox.h"
#include "HRichTextButton.h"
#include "HRichTextEdit.h"
#include "HColorButton.h"
#include "HColorComboBox.h"
#include "HHueSatPicker.h"
#include "HHueSatRadialPicker.h"
#include "HConfigPanel.h"
#include "HNavigationPanel.h"
#include "HTaskPanel.h"
#include "HNavigationSlider.h"
#include "HTipWidget.h"
#include "HLedWidget.h"
#include "HNumPad.h"
#include "HTwoColorIndicator.h"
#include <QtWidgets/QListWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addWw()
{
    addWwExtend();
    addWwPicker();
    addWwConfigPanel();
    addWwNavigationPanel();
    addWwTaskPanel();
    addWwTipWidget();
    addWwNavigator();
    addWwElse();
}

void HControlDemoWidget::addWwExtend()
{
    auto layout = new QFormLayout;
    auto textSpinBox = new HTextSpinBox;
    textSpinBox->setItems(QStringList() << "a" << "b" << "c" << "d");
    auto richTextButton = new HRichTextButton;
    richTextButton->setHtml(R"(<p align="center"><span style=" font-weight:600; color:#ff0000;">富文本按钮</span></p>)");
    layout->setLabelAlignment(Qt::AlignRight);
    layout->addRow(new QLabel(tr("按钮行编辑：")), new HButtonLineEdit);
    layout->addRow(new QLabel(tr("清除行编辑：")), new HClearLineEdit);
    layout->addRow(new QLabel(tr("重置行编辑：")), new HResetLineEdit);
    layout->addRow(new QLabel(tr("文件行编辑：")), new HFileChooser);
    layout->addRow(new QLabel(tr("长整型调节框：")), new HLongSpinBox);
    layout->addRow(new QLabel(tr("文本调节框：")), textSpinBox);
    layout->addRow(new QLabel(tr("颜色组合框：")), new HColorComboBox);
    layout->addRow(new QLabel(tr("颜色按钮：")), new HColorButton);
    layout->addRow(new QLabel(tr("富文本按钮：")), richTextButton);
    layout->addRow(new QLabel(tr("富文本编辑：")), new HRichTextEdit);
    addTab(tr("ww"), tr("控件扩展"), layout);
}

void HControlDemoWidget::addWwPicker()
{
    auto layout = new QVBoxLayout;
    auto colorButton = new HColorButton;
    auto picker1 = new HHueSatPicker;
    auto picker2 = new HHueSatRadialPicker;
    auto splitter = new QSplitter;
    splitter->addWidget(picker1);
    splitter->addWidget(picker2);
    connect(colorButton, &HColorButton::colorPicked, picker1, &HHueSatPicker::setColor);
    connect(colorButton, &HColorButton::colorPicked, picker2, &HHueSatRadialPicker::setColor);
    layout->addWidget(colorButton);
    layout->addWidget(splitter);
    addTab(tr("ww"), tr("颜色拾取器"), layout);
}

void HControlDemoWidget::addWwConfigPanel()
{
    auto panel = new HConfigPanel;
    panel->addWidget(new HButtonLineEdit, tr("行编辑器1"));
    panel->addWidget(new HClearLineEdit, tr("行编辑器2"));
    panel->addWidget(new HColorButton, tr("颜色按钮"));
    addTab(tr("ww"), tr("配置面板"), panel);
}

void HControlDemoWidget::addWwNavigationPanel()
{
    auto panel = new HNavigationPanel;
    panel->addWidget(new HButtonLineEdit, tr("行编辑器1"));
    panel->addWidget(new HClearLineEdit, tr("行编辑器2"));
    panel->addWidget(new HColorButton, tr("颜色按钮"));
    addTab(tr("ww"), tr("导航面板"), panel);
}

void HControlDemoWidget::addWwTaskPanel()
{
    auto panel = new HTaskPanel;
    panel->addWidget(new HHueSatPicker, tr("颜色拾取器"));
    panel->addWidget(new HHueSatRadialPicker, tr("颜色拾取器2"));
    panel->addWidget(new HRichTextEdit, tr("富文本编辑器"));
    addTab(tr("ww"), tr("任务面板"), panel);
}

void HControlDemoWidget::addWwNavigator()
{
    auto layout = new QVBoxLayout;
    auto widget = new QListWidget;
    for (int i = 0; i < 10; i++)
        widget->addItem(QString("Item %1").arg(i+1));
    auto nav = new HNavigationSlider;
    nav->setListWidget(widget);
    layout->addWidget(widget);
    layout->addWidget(nav);
    addTab(tr("ww"), tr("导航滑块"), layout);
}

void HControlDemoWidget::addWwTipWidget()
{
    addTab(tr("ww"), tr("提示框"), new HTipWidget);
}

void HControlDemoWidget::addWwElse()
{
    auto layout = new QGridLayout;
    layout->addWidget(new HLedWidget, 0, 0);
    layout->addWidget(new HTwoColorIndicator, 0, 1);
    layout->addWidget(new HNumPad, 1, 0, 1, 2);
    addTab(tr("ww"), tr("其他"), layout);
}

HE_END_NAMESPACE
