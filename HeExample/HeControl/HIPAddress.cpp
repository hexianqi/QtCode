#include "HIPAddress_p.h"
#include "HRegularExpressionHelper.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QRegularExpressionValidator>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>

HE_CONTROL_BEGIN_NAMESPACE

HIPAddress::HIPAddress(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HIPAddressPrivate)
{
    init();
}

HIPAddress::HIPAddress(HIPAddressPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HIPAddress::~HIPAddress()
{
}

QSize HIPAddress::sizeHint() const
{
    return QSize(250, 20);
}

QSize HIPAddress::minimumSizeHint() const
{
    return QSize(30, 10);
}

QString HIPAddress::ip() const
{
    return d_ptr->ip;
}

QColor HIPAddress::background() const
{
    return d_ptr->background;
}

QColor HIPAddress::borderColor() const
{
    return d_ptr->borderColor;
}

int HIPAddress::borderRadius() const
{
    return d_ptr->borderRadius;
}

void HIPAddress::setIP(const QString &value)
{
    if (d_ptr->ip == value || !HRegularExpressionHelper::isIP(value))
        return;
    d_ptr->ip = value;
    auto list = value.split(".");
    for (int i = 0; i < 4; i++)
        d_ptr->lineEdits[i]->setText(list[i]);
    emit valueChanged(value);
}

void HIPAddress::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    updateStyle();
}

void HIPAddress::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    updateStyle();
}

void HIPAddress::setBorderRadius(int value)
{
    if (d_ptr->borderRadius == value)
        return;
    d_ptr->borderRadius = value;
    updateStyle();
}

void HIPAddress::clear()
{
    d_ptr->ip = "0.0.0.0";
    for (auto v : d_ptr->lineEdits)
        v->clear();
    d_ptr->lineEdits[0]->setFocus();
    emit valueChanged(d_ptr->ip);
}

bool HIPAddress::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto line = qobject_cast<QLineEdit *>(watched);
        auto key = static_cast<QKeyEvent *>(event);
        if (key != nullptr && d_ptr->lineEdits.contains(line))
        {
            if (key->text() == ".")
                focusNextChild();
            if (key->key() == Qt::Key_Backspace && line->text().length() <= 1)
            {
                focusNextPrevChild(false);
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void HIPAddress::handleTextChanged(const QString &text)
{
    auto value = text.toInt();
    if (text.length() == 3 && value >= 100 && value <= 255)
        focusNextChild();

    QStringList list;
    for(auto v : d_ptr->lineEdits)
        list << v->text();
    d_ptr->ip = list.join(".");
    emit valueChanged(d_ptr->ip);
}

void HIPAddress::init()
{
    int i;
    QRegularExpression re("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
    auto validator = new QRegularExpressionValidator(re, this);
    auto frame = new QFrame;
    auto vLayout = new QVBoxLayout(this);
    auto hLayout = new QHBoxLayout(frame);

    frame->setObjectName("frameIP");
    for (i = 0; i < 4; i++)
    {
        auto lineEdit = new QLineEdit;
        lineEdit->setObjectName(QString("txtIP%1").arg(i+1));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        lineEdit->setValidator(validator);
        lineEdit->installEventFilter(this);
        hLayout->addWidget(lineEdit);
        connect(lineEdit, &QLineEdit::textChanged, this, &HIPAddress::handleTextChanged);
        d_ptr->lineEdits << lineEdit;
    }
    for (i = 0; i < 3; i++)
    {
        auto label = new QLabel(".");
        label->setAlignment(Qt::AlignCenter);
        hLayout->insertWidget(2 * i + 1, label);
    }
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    vLayout->addWidget(frame);
    updateStyle();
    setWindowTitle(tr("IP地址输入框"));
}

void HIPAddress::updateStyle()
{
    auto qss = QStringList() << QString("QFrame#frameIP { border:1px solid %1; border-radius:%2px; }").arg(d_ptr->borderColor.name()).arg(d_ptr->borderRadius)
                             << QString("QLabel { min-width:15px; background-color:%1; }").arg(d_ptr->background.name())
                             << QString("QLineEdit { background-color:%1; border:none; }").arg(d_ptr->background.name())
                             << QString("QLineEdit#txtIP1 { border-top-left-radius:%1px; border-bottom-left-radius:%1px; }").arg(d_ptr->borderRadius)
                             << QString("QLineEdit#txtIP4 { border-top-right-radius:%1px; border-bottom-right-radius:%1px; }").arg(d_ptr->borderRadius);
    setStyleSheet(qss.join("\n"));
}
HE_CONTROL_END_NAMESPACE
