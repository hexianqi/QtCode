#pragma once

#include "HImageBrowser.h"

class QToolButton;

HE_BEGIN_NAMESPACE

class HImageBrowserPrivate
{
public:
    QColor backgroundStart = QColor(255, 255, 255);
    QColor backgroundEnd = QColor(228, 228, 228);
    int bottomSpace = 10;
    int buttonSpace = 10;
    QSize iconSize = QSize(65, 65);
    bool fill = false;
    bool fade = false;
    bool keyMove = false;

public:
    QStringList imageNames;
    QImage currentImage;
    double opacity = 1.0;
    int totalNum = 0;
    int currentIndex = -1;
    QToolButton *previous;
    QToolButton *next;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
