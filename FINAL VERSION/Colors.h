#pragma once
#include "graphics.h"

//these will be modified by rgb picker
int PARTITION_COLORS[8] = {YELLOW, COLOR(50,50,255), COLOR(255,150,0), COLOR(255,50,50), COLOR(200,0,200), LIGHTBLUE, LIGHTGREEN, COLOR(255,150,150)};
int PIECE_COLORS[3] = {COLOR(36, 36, 36), COLOR(222,222,222),  GREEN};

//the will not be modified
int DEFAULT_PARTITION_COLORS[8] = {YELLOW, COLOR(50,50,255), COLOR(255,150,0), COLOR(255,50,50), COLOR(200,0,200), LIGHTBLUE, LIGHTGREEN, COLOR(255,150,150)};
int DEFAULT_PIECE_COLORS[3] = {COLOR(36, 36, 36), COLOR(222,222,222),  GREEN};

int getBrighterColor(const int color, int brightness = 10)
{
    int r = RED_VALUE(color);
    int g = GREEN_VALUE(color);
    int b = BLUE_VALUE(color);

    r = std::min(255,r+brightness);
    g = std::min(255,g+brightness);
    b = std::min(255,b+brightness);

    return COLOR(r,g,b);
}

int getDarkerColor(const int color, int brightness = 10)
{
    int r = RED_VALUE(color);
    int g = GREEN_VALUE(color);
    int b = BLUE_VALUE(color);

    r = std::max(0,r-brightness);
    g = std::max(0,g-brightness);
    b = std::max(0,b-brightness);

    return COLOR(r,g,b);
}


