#pragma once
#include "graphics.h"
#include "Rect.h"
#include "Vec2.h"
#include <string>

#define LEFT_ALIGNMENT 0
#define CENTER_ALIGNMENT 1
#define RIGHT_ALIGNMENT 2

void drawText(std::string text, int x, int y, int color, int bgColor, int _alignment, int font, int textSize)
{
    setcolor(color);
    setbkcolor(bgColor);
    settextstyle(font,HORIZ_DIR,textSize);

    int width = textwidth((char*)text.c_str());  //textwidth ia ca parametru char* iar c_str returneaza const*
    int height = textheight((char*)text.c_str());

    switch(_alignment)
    {
    case LEFT_ALIGNMENT:
        outtextxy(x - width,        y - height / 2, (char*)text.c_str());
        break;
    case CENTER_ALIGNMENT:
        outtextxy(x - width / 2,    y - height / 2, (char*)text.c_str());
        break;
    case RIGHT_ALIGNMENT:
        outtextxy(x,        y - height / 2, (char*)text.c_str());
        break;
    }
}

void drawText(std::string text, int x, int y, int color, int bgColor, int _alignment)
{
    drawText(text,x,y,color,bgColor,_alignment,4,2);
}

//to_string deja exista dar necesita c++11
std::string int_to_string(int n)
{
    char buffer[32];
    sprintf (buffer, "%d", n);
    return buffer; //se face conversia implicita
}
