#include "HNumPad_p.h"
#include <QtWidgets/QToolButton>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HNumPad::HNumPad(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HNumPadPrivate)
{
    init();
}

HNumPad::HNumPad(HNumPadPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HNumPad::~HNumPad() = default;

void HNumPad::animateClick(const QString &button, int msec)
{
    if (button.size() != 1)
        return;

    QString name;
    auto key = button[0].toLatin1();
    if (key == '#')
        name = "bHash";
    else if (key == '*')
        name = "bAster";
    else
        name = QString("b%1").arg(key);

    auto buttonn = findChild<QToolButton *>(name);
    if (buttonn != nullptr)
        return;
    buttonn->animateClick(msec);
}

void HNumPad::init()
{
    auto group = new QButtonGroup(this);
    for (int i = 1; i < 10; i++)
    {
        auto button = new QToolButton;
        button->setObjectName(QString("b%1").arg(i));
        button->setText(QString::number(i));
        group->addButton(button, i);
    }
    auto aster = new QToolButton;
    aster->setObjectName("bAster");
    aster->setText("*");
    group->addButton(aster, 10);
    auto zero = new QToolButton;
    zero->setObjectName("b0");
    zero->setText("0");
    group->addButton(zero, 0);
    auto hash = new QToolButton;
    hash->setText("#");
    hash->setObjectName("bHash");
    group->addButton(hash, 11);

    auto layout = new QGridLayout(this);
    layout->setSpacing(2);
    layout->setMargin(2);

    for (int i = 0; i < group->buttons().count(); i++)
    {
        auto button = group->buttons().at(i);
        button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        layout->addWidget(button, i / 3, i % 3);
    }
    connect(group, SIGNAL(buttonClicked(int)), SLOT(handleClicked(int)));
    setWindowIcon(QIcon(":/Resources/ww/numpad.png"));
}

void HNumPad::handleClicked(int id)
{
    if (id >= 0 && id < 10)
    {
        emit numberClicked(id);
        emit keyClicked(QString::number(id));
        return;
    }
    if (id == 10)
    {
        emit asteriskClicked();
        emit keyClicked("*");
        return;
    }
    if (id == 11)
    {
        emit hashClicked();
        emit keyClicked("#");
        return;
    }
}

HE_END_NAMESPACE
