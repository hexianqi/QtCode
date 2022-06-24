#pragma once

#include "HCanvasItem.h"

class HCanvasItemPrivate
{
public:
    double x = 0;
    double y = 0;
    double z = 0;
    bool animated = true;
    HCanvas* canvas = nullptr;
    HCanvasItemExtra *extra = nullptr;
//    static QtCanvas* current_canvas;
//    double myx,myy,myz;

//    QtCanvasItemExtra& extra();
//    uint ani:1;
//    uint vis:1;
//    uint val:1;
//    uint sel:1;
//    uint ena:1;
//    uint act:1;

};



