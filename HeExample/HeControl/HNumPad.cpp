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
    auto g = new QButtonGroup(this);
    for (int i = 0; i < 9; i++)
    {
        auto b = new QToolButton;
        b->setObjectName(QString("b%1").arg(i+1));
        b->setText(QString::number(i + 1));
        g->addButton(b, i + 1);
    }
    auto a = new QToolButton;
    a->setObjectName("bAster");
    a->setText("*");
    g->addButton(a, 10);
    auto z = new QToolButton;
    z->setObjectName("b0");
    z->setText("0");
    g->addButton(z, 0);
    auto h = new QToolButton;
    h->setText("#");
    h->setObjectName("bHash");
    g->addButton(h, 11);

    auto l = new QGridLayout(this);
    l->setSpacing(2);
    l->setMargin(2);

    for (int i = 0; i < g->buttons().count(); i++)
    {
        auto b = g->buttons().at(i);
        b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        l->addWidget(b, i / 3, i % 3);
    }
    connect(g, SIGNAL(buttonClicked(int)), SLOT(handleClicked(int)));
    setWindowIcon(QIcon(":/image/ww/numpad.png"));
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
