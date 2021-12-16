#include "HGameLevel_p.h"
#include "HBrick.h"
#include "HSpriteRenderer.h"
#include "HResourceManager.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_BEGIN_NAMESPACE

HGameLevel::HGameLevel(QObject *parent) :
    QObject(parent),
    d_ptr(new HGameLevelPrivate)
{
}

HGameLevel::HGameLevel(HGameLevelPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HGameLevel::~HGameLevel()
{
}

QVector<HBrick *> HGameLevel::bricks()
{
    return d_ptr->bricks;
}

bool HGameLevel::isCompleted()
{
    for (auto i : d_ptr->bricks)
        if (!i->isSolid() && !i->isDestroyed())
            return false;
    return true;
}

bool HGameLevel::load(const QString &fileName, int width, int height)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream s(&file);
    QString line;
    QVector<QVector<uint>> data;
    while (s.readLineInto(&line))
    {
        QVector<uint> row;
        auto text = line.simplified().split(' ', QString::SkipEmptyParts);
        for (auto c : text)
            row << c.toUInt();
        data << row;
    }
    file.close();
    return load(data, width, height);
}

bool HGameLevel::load(QVector<QVector<uint>> data, int width, int height)
{
    if (data.size() < 1 || data.at(0).size() < 1)
        return false;

    auto maxSize = 0;
    for (auto i : data)
        maxSize = qMax(maxSize, i.size());
    auto unitWidth = 1.0f * width / maxSize;
    auto unitHeight = 1.0f * height / data.size();

    qDeleteAll(d_ptr->bricks);
    d_ptr->bricks.clear();
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            auto v = data[i][j];
            if (v == 0)
                continue;

            auto brick = new HBrick(this);
            brick->setPosition(QVector2D(unitWidth * j, unitHeight * i));
            brick->setSize(QVector2D(unitWidth, unitHeight));

            if (v == 1)
            {
                brick->setColor(QVector3D(0.8f, 0.8f, 0.7f));
                brick->setTexture(HResourceManager::texture("block_solid"));
                brick->setSolid(true);
            }
            else
            {
                auto color = QVector3D(1.0f, 1.0f, 1.0f);
                if (v == 2)
                    color = QVector3D(0.2f, 0.6f, 1.0f);
                else if (v == 3)
                    color = QVector3D(0.0f, 0.7f, 0.0f);
                else if (v == 4)
                    color = QVector3D(0.8f, 0.8f, 0.4f);
                else if (v == 5)
                    color = QVector3D(1.0f, 0.5f, 0.0f);
                brick->setColor(color);
                brick->setTexture(HResourceManager::texture("block"));
            }
            d_ptr->bricks << brick;
        }
    }
    return !d_ptr->bricks.isEmpty();
}

void HGameLevel::draw(HSpriteRenderer *p)
{
    for (auto i : d_ptr->bricks)
        if (!i->isDestroyed())
            i->draw(p);
}

void HGameLevel::reset()
{
    for (auto i : d_ptr->bricks)
        i->setDestroyed(false);
}

HE_END_NAMESPACE
