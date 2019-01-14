#pragma once
#include <cmath>
#include "graphics.h"
#include "Rect.h"

struct MouseState
{
    bool leftIsPressed = false;
    bool rightIsPressed = false;

    bool isInsideWindow = false;

    bool lefthasBeenClicked = false;
    bool righthasBeenClicked = false;

    bool leftHasBeenReleased = false;
    bool rightHasBeenReleased = false;

    bool hasMoved = false;

    int x;
    int y;
    Vec2 cursor;
};

bool lastLeft = false;
bool lastRight = false;
int lastX = -1;
int lastY = -1;

MouseState mouse;

void SetMouseState()
{
    while(ismouseclick(WM_LBUTTONUP))
    {
        clearmouseclick(WM_LBUTTONUP);
        mouse.leftIsPressed = false;
    }

    while(ismouseclick(WM_RBUTTONUP))
    {
        clearmouseclick(WM_RBUTTONUP);
        mouse.rightIsPressed = false;
    }

    while(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        mouse.leftIsPressed = true;
    }

    while(ismouseclick(WM_RBUTTONDOWN))
    {
        clearmouseclick(WM_RBUTTONDOWN);
        mouse.rightIsPressed = true;
    }

    mouse.x = mousex();
    mouse.y = mousey();
    mouse.cursor = makeVec2(mouse.x,mouse.y);
    mouse.isInsideWindow = isPointInsideRect(mouse.cursor,getScreenRect());


    //left
    if(lastLeft == mouse.leftIsPressed)
    {
        mouse.lefthasBeenClicked = mouse.leftHasBeenReleased = false;
    }
    else if(lastLeft)
    {
        mouse.leftHasBeenReleased = true;
        mouse.lefthasBeenClicked = false;
    }
    else
    {
        mouse.leftHasBeenReleased = false;
        mouse.lefthasBeenClicked = true;
    }

    //right
    if(lastRight == mouse.rightIsPressed)
    {
        mouse.righthasBeenClicked = mouse.rightHasBeenReleased = false;
    }
    else if(lastRight)
    {
        mouse.rightHasBeenReleased = true;
        mouse.righthasBeenClicked = false;
    }
    else
    {
        mouse.rightHasBeenReleased = false;
        mouse.righthasBeenClicked = true;
    }

    mouse.hasMoved = mouse.x != lastX || mouse.y != lastY;

    lastX = mouse.x;
    lastY = mouse.y;
    lastLeft = mouse.leftIsPressed;
    lastRight = mouse.rightIsPressed;
}
