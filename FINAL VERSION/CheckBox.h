#pragma once
#include "Geometrie.h"
#include "Rect.h"
#include "MouseState.h"
#include <string>

#define CHECKBOX_STROKE 3
#define CHECKBOX_TEXT_SPACING 10

struct CheckBox
{
    bool isChecked;
    Rect chenar;
    int color;
    int textColor;
    std::string text;
};

void initCheckBox(CheckBox& box, int x, int y, int box_size, int textColor, int color, std::string text, bool isChecked = false)
{
    box.isChecked = isChecked;
    box.chenar = makeRectFromCenter(x,y,box_size,box_size);
    box.color = color;
    box.text = text;
}

CheckBox makeCheckBox(int x, int y, int box_size, int textColor, int color, std::string text, bool isChecked = false)
{
    CheckBox box;
    initCheckBox(box,x,y,box_size,textColor,color,text,isChecked);
    return box;
}

void _DrawEmptyCheckBox(CheckBox& box,int bgColor)
{
    drawFilledRect(box.chenar,bgColor);
    drawRect_StrokeOnly(getExpanded(box.chenar,-CHECKBOX_STROKE), CHECKBOX_STROKE, box.color);
}

void _DrawFilledCheckBox(CheckBox& box, int bgColor)
{
    drawFilledRect(box.chenar,box.color);

    int x1 = box.chenar.left + box.chenar.width * 0.25;
    int y3 = box.chenar.top + box.chenar.height * 0.25;
    int x2 = box.chenar.left + box.chenar.width * 0.45;
    int y1 = box.chenar.top + box.chenar.height * 0.5;
    int x3 = box.chenar.left + box.chenar.width * 0.8;
    int y2 = box.chenar.top + box.chenar.height * 0.65;

    drawLine(x1,y1,x2,y2,bgColor,CHECKBOX_STROKE);
    drawLine(x3,y3,x2,y2,bgColor,CHECKBOX_STROKE);
}

void drawCheckBox(CheckBox& box,int bgColor)
{
    if(box.isChecked)
    {
        _DrawFilledCheckBox(box,bgColor);
    }
    else
    {
        _DrawEmptyCheckBox(box,bgColor);
    }
    drawText(box.text, box.chenar.right + CHECKBOX_TEXT_SPACING, box.chenar.ycenter, box.textColor, bgColor, RIGHT_ALIGNMENT);
}

bool UpdateCheckBox(CheckBox& box, int bgColor, bool dontRedraw = false)
{
    if(mouse.lefthasBeenClicked)
    {
        if(isPointInsideRect(mouse.cursor,box.chenar))
        {
            box.isChecked = !box.isChecked;
            if(dontRedraw == false)
            {
                drawCheckBox(box,bgColor);
            }
            return true;
        }
    }
    return false;
}
