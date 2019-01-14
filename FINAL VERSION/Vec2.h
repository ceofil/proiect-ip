#pragma once

struct Vec2
{
    int x;
    int y;
};

void initVec2(Vec2& v, int x, int y)
{
    v.x = x;
    v.y = y;
}

Vec2 makeVec2(int x, int y)
{
    Vec2 v;
    initVec2(v,x,y);
    return v;
}

