#include "HPropManager_p.h"
#include "HProp.h"
#include "HResourceManager.h"
#include <QtCore/QRandomGenerator>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

HPropManagerPrivate::HPropManagerPrivate()
{
    colors.insert("speed",          QVector3D(0.5f, 0.5f, 1.0f));
    colors.insert("sticky",         QVector3D(1.0f, 0.5f, 1.0f));
    colors.insert("passthrough",    QVector3D(0.5f, 1.0f, 0.5f));
    colors.insert("increase",       QVector3D(1.0f, 0.6f, 0.4f));
    colors.insert("confuse",        QVector3D(1.0f, 0.3f, 0.3f));
    durations.insert("speed",       0.0f);
    durations.insert("sticky",      20.0f);
    durations.insert("passthrough", 10.0f);
    durations.insert("increase",    0.0f);
    durations.insert("confuse",     15.0f);
    durations.insert("chaos",       15.0f);
    textures.insert("speed",        "powerup_speed");
    textures.insert("sticky",       "powerup_sticky");
    textures.insert("passthrough",  "powerup_passthrough");
    textures.insert("increase",     "powerup_increase");
    textures.insert("confuse",      "powerup_confuse");
    textures.insert("chaos",        "powerup_chaos");
}

HPropManager::HPropManager(QObject *parent) :
    QObject(parent),
    d_ptr(new HPropManagerPrivate)
{
}

HPropManager::~HPropManager()
{
}

void HPropManager::spawn(QVector2D position)
{
    QString type;
    auto i = QRandomGenerator::global()->bounded(75);
    if (i < 5)
        type = "chaos";
    if (i >= 70)
        type = "confuse";
    if (i == 5)
        type = "speed";
    if (i == 6)
        type = "increase";
    if (i == 7)
        type = "sticky";
    if (i == 8)
        type = "passthrough";
    if (type.isEmpty())
        return;
    d_ptr->props << createProp(type, position);
}

void HPropManager::update(float dt)
{
    for (auto p : d_ptr->props)
        p->update(dt);
    // Remove all props from vector that are destroyed AND !activated (thus either off the map or finished)
    // Note we use a lambda expression to remove each props which is destroyed and not activated
    d_ptr->props.erase(std::remove_if(d_ptr->props.begin(), d_ptr->props.end(), [](HProp *p) { return !p->isActivated() && p->isDestroyed(); }), d_ptr->props.end());
}

void HPropManager::draw(HSpriteRenderer *p)
{
    for (auto i : d_ptr->props)
        if (!i->isDestroyed())
            i->draw(p);
}

void HPropManager::collision(HGameObject *obj, int height)
{
    for (auto i : d_ptr->props)
    {
        if (i->isDestroyed())
            continue;
        if (i->position().y() >= height)
            i->setDestroyed(true);
        if (i->checkCollision(obj))
        {
            i->setDestroyed(true);
            i->setActivated(true);
            HResourceManager::play(":/audio/powerup.wav");
        }
    }
}

void HPropManager::reset()
{
    for (auto i : d_ptr->props)
        i->disconnect(this);
    qDeleteAll(d_ptr->props);
    d_ptr->props.clear();
}

HProp *HPropManager::createProp(const QString &type, QVector2D position)
{
    auto p = new HProp(this);
    p->setPosition(position);
    p->setSize(QVector2D(60.0f, 20.0f));
    p->setVelocity(QVector2D(0.0f, 150.0f));
    p->setType(type);
    p->setColor(d_ptr->colors.value(type, QVector3D(1.0f, 1.0f, 1.0f)));
    p->setTexture(HResourceManager::texture(d_ptr->textures.value(type)));
    p->setDuration(d_ptr->durations.value(type, 0.0f));
    connect(p, &HProp::activateChanged, this, &HPropManager::handleActivate);
    return p;
}

void HPropManager::handleActivate(bool b)
{
    auto p = qobject_cast<HProp *>(sender());
    if (p == nullptr)
        return;
    if (!isOtherActivate(p))
    {
        emit propStateChanged(p->type(), b);
        return;
    }
    if (p->isPermanent())
        p->setActivated(false);
}

bool HPropManager::isOtherActivate(HProp *p)
{
    for (auto prop : d_ptr->props)
    {
        if (prop == p)
            continue;
        if (prop->type() == p->type() && prop->isActivated())
            return true;
    }
    return false;
}

HE_REFERENCE_END_NAMESPACE
