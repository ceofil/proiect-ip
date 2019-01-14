#pragma once
#include <cmath>
#include "graphics.h"
#include "Rect.h"
void drawFilledCircle(int x, int y, float radius, int color)
{
    setlinestyle(SOLID_LINE,1,1);
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, radius, radius);
}

void drawFilledRect(int left, int top, int right, int bottom, int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(left, top, right, bottom);
}

void drawFilledRect(Rect r, int color)
{
    drawFilledRect(r.left, r.top, r.right, r.bottom ,color);
}

Rect getScreenRect()
{
    return makeRect(0,0,getmaxx()+1,getmaxy()+1);
}

void DrawBackground(int color)
{
    drawFilledRect(getScreenRect(),color);
}

void drawRect_StrokeOnly(Rect r, int stroke, int color)
{
    drawFilledRect(r.left - stroke, r.top - stroke, r.right + stroke, r.top, color);
    drawFilledRect(r.left - stroke, r.bottom, r.right + stroke, r.bottom + stroke, color);

    drawFilledRect(r.left - stroke, r.top, r.left, r.bottom, color);
    drawFilledRect(r.right, r.top, r.right+stroke, r.bottom, color);
}

void drawLine(int x1, int y1, int x2, int y2, int color, int thickness = 1)
{
    setcolor(color);
    setlinestyle(SOLID_LINE,1,thickness);
    line(x1,y1,x2,y2);
}



