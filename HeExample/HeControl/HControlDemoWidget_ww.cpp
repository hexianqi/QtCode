#include "HControlDemoWidget_p.h"
#include "HButtonLineEdit.h"
#include "HClearLineEdit.h"
#include "HResetLineEdit.h"
#include "HFileChooser.h"
#include "HRichTextButton.h"
#include "HColorButton.h"
#include "HColorComboBox.h"
#include "HLongSpinBox.h"
#include "HTextSpinBox.h"
#include "HRichTextEdit.h"
#include "HHueSatPicker.h"
#include "HHueSatRadialPicker.h"
#include "HNavigationSlider.h"
#include "HConfigPanel.h"
#include "HNavigationPanel.h"
#include "HTaskPanel.h"
#include "HTipWidget.h"
#include "HLedWidget.h"
#include "HNumPad.h"
#include "HTwoColorIndicator.h"
#include <QtWidgets/QSplitter>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

void HControlDemoWidget::addWw()
{
    addWwExtend();
    addWwPicker();
    addWwNavigator();
    addWwConfigPanel();
    addWwNavigationPanel();
    addWwTaskPanel();
    addWwTipWidget();
    addWwElse();
}

void HControlDemoWidget::addWwExtend()
{
    auto layout = new QVBoxLayout;
    auto buttonLineEdit = new HButtonLineEdit;
    auto fileChooser = new HFileChooser;
    auto clearLineEdit = new HClearLineEdit;
    auto resetLineEdit = new HResetLineEdit;
    auto richTextButton = new HRichTextButton;
    auto colorButton = new HColorButton;
    auto colorComboBox = new HColorComboBox;
    auto longSpinBox = new HLongSpinBox;
    auto textSpinBox = new HTextSpinBox;
    auto richTextEdit = new HRichTextEdit;
    textSpinBox->setStringList(QStringList() << "a" << "b" << "c" << "d");
    richTextButton->setHtml(R"(<p align="center"><span style=" font-weight:600; color:#ff0000;">富文本按钮</span></p>)");
    layout->addWidget(buttonLineEdit);
    layout->addWidget(fileChooser);
    layout->addWidget(clearLineEdit);
    layout->addWidget(resetLineEdit);
    layout->addWidget(richTextButton);
    layout->addWidget(colorButton);
    layout->addWidget(colorComboBox);
    layout->addWidget(longSpinBox);
    layout->addWidget(textSpinBox);
    layout->addWidget(richTextEdit);
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
    addTab(tr("ww"), tr("导航"), layout);
}

void HControlDemoWidget::addWwConfigPanel()
{
    auto w = new HConfigPanel;
    w->addWidget(new HButtonLineEdit, tr("行编辑器1"));
    w->addWidget(new HClearLineEdit, tr("行编辑器2"));
    w->addWidget(new HColorButton, tr("颜色按钮"));
    addTab(tr("ww"), tr("配置窗体"), w);
}

void HControlDemoWidget::addWwNavigationPanel()
{
    auto w = new HNavigationPanel;
    w->addWidget(new HButtonLineEdit, tr("行编辑器1"));
    w->addWidget(new HClearLineEdit, tr("行编辑器2"));
    w->addWidget(new HColorButton, tr("颜色按钮"));
    addTab(tr("ww"), tr("导航面板"), w);
}

void HControlDemoWidget::addWwTaskPanel()
{
    auto w = new HTaskPanel;
    w->addWidget(new HHueSatPicker, tr("颜色拾取器"));
    w->addWidget(new HHueSatRadialPicker, tr("颜色拾取器2"));
    w->addWidget(new HRichTextEdit, tr("富文本编辑器"));
    addTab(tr("ww"), tr("任务面板"), w);
}

void HControlDemoWidget::addWwTipWidget()
{
    addTab(tr("ww"), tr("提示框"), new HTipWidget);
}

void HControlDemoWidget::addWwElse()
{
    auto layout = new QGridLayout;
    auto led = new HLedWidget;
    auto indicator = new HTwoColorIndicator;
    auto num = new HNumPad;
    layout->addWidget(led, 0, 0);
    layout->addWidget(indicator, 0, 1);
    layout->addWidget(num, 1, 0, 1, 2);
    addTab(tr("ww"), tr("其他"), layout);
}

HE_CONTROL_END_NAMESPACE
