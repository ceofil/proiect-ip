#pragma once
#include <string>
#include "Rect.h"
#include "Geometrie.h"
#include "MouseState.h"
#include "UtilityFunctions.h"


int buttonWidth = 250;
int buttonHeight = 50;
int buttonColor = COLOR(36, 36, 100);

struct Button
{
    std::string text;
    Rect chenar;
    int color;

    bool lastMouseOver = false;
};

void initButton(Button& b, Rect chenar, std::string text, int color)
{
    b.chenar = chenar;
    b.text = text;
    b.color = color;
}

Button makeButton(Rect chenar, std::string text, int color = BLACK)
{
    Button b;
    initButton(b,chenar,text,color);
    return b;
}

void drawButton(const Button& b)
{
    drawFilledRect(b.chenar, b.color);
    drawText(b.text, b.chenar.xcenter,b.chenar.ycenter, WHITE, b.color, CENTER_ALIGNMENT);
}

void drawButton(const Button& b, int color)
{
    drawFilledRect(b.chenar, color);
    drawText(b.text, b.chenar.xcenter,b.chenar.ycenter, WHITE, color, CENTER_ALIGNMENT);
}

void hideButton(const Button& b, int bgColor)
{
    drawFilledRect(b.chenar, bgColor);
}

bool cursorInsideButton(Vec2 cursor, Button b)
{
    return isPointInsideRect(cursor.x, cursor.y, b.chenar);
}

void updateLastMouseOver(Button& b)
{
    bool MouseOver = cursorInsideButton(mouse.cursor, b);
    if(b.lastMouseOver != MouseOver)
    {
        if(MouseOver)
        {
            drawButton(b, getBrighterColor(b.color, 25));
        }
        else
        {
            drawButton(b);
        }

        b.lastMouseOver = MouseOver;
    }
}

bool buttonHasBeenClicked(Button& b)
{
    updateLastMouseOver(b);
    return mouse.lefthasBeenClicked && isPointInsideRect(mouse.cursor.x, mouse.cursor.y, b.chenar);
}
