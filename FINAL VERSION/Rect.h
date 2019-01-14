#pragma once
#include <cassert>
#include "Vec2.h"

struct Rect
{
    int left;
    int top;
    int right;
    int bottom;

    int width;
    int height;
    int xcenter;
    int ycenter;
};

void initRect(Rect& r, int left, int top, int right, int bottom)
{
    assert(right >= left && bottom >= top);
    r.left = left;
    r.top = top;
    r.right = right;
    r.bottom = bottom;
    r.width = right - left;
    r.height = bottom - top;
    r.xcenter = r.left + r.width / 2;
    r.ycenter = r.top + r.height / 2;
}

Rect makeRect(int left, int top, int right, int bottom)
{
    Rect r;
    initRect(r,left,top,right,bottom);
    return r;
}

Rect makeRectFromCenter(int x, int y, int width, int height)
{
    return makeRect(x-width/2,y-height/2,x+width/2,y+height/2);
}

Rect makeRectFromCenter(Vec2 center, int width, int height)
{
    return makeRectFromCenter(center.x,center.y,width,height);
}

bool isPointInsideRect(int x, int y, Rect r)
{
    return x > r.left && x < r.right && y > r.top && y < r.bottom;
}

bool isPointInsideRect(Vec2 point, Rect r)
{
    return isPointInsideRect(point.x,point.y, r);
}

Vec2 getCenter(const Rect& r)
{
    return makeVec2(r.xcenter,r.ycenter);
}

//returneaza true daca b incus in a
bool contains(Rect a, Rect b)
{
    return b.top >= a.top && b.bottom <= a.bottom && b.left >= a.left && b.right <= a.right;
}

Rect getSlided(Rect r, int xOffset, int yOffset)
{
    return makeRectFromCenter(r.xcenter+xOffset,r.ycenter+yOffset,r.width,r.height);
}

Rect getExpanded(Rect r, int delta)
{
    return makeRectFromCenter(r.xcenter,r.ycenter,r.width+2*delta,r.height+2*delta);
}
