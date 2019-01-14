#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

#include "graphics.h"
#include "Geometrie.h"
#include "Rect.h"
#include "MouseState.h"
#include "UtilityFunctions.h"

#define Slider_STROKE 2

struct Slider
{
    Rect bar_chenar;
    Rect handle_chenar;
    float minValue;
    float maxValue;
    float value;

    bool isBeingSlided = false;
    int xOnHandle;

    int barColor;
    int handleColor;

    Rect value_chenar;
};
float interpolare(float value, float maxim)
{
    return value / maxim;
}

float interpolare(float value, float minim, float maxim)
{
    return interpolare(value-minim, maxim-minim);
}

float interpolare(float value, float minim, float maxim, float otherMinim, float otherMaxim)
{
    return otherMinim + (otherMaxim - otherMinim) * interpolare(value,minim,maxim);
}

void initSlider(Slider& Slider, Rect bar_chenar, float minValue, float maxValue, float value, float handleToBarRatio, int barColor, int handleColor)
{
    Slider.bar_chenar = bar_chenar;
    Slider.minValue = minValue;
    Slider.maxValue = maxValue;
    Slider.value = value;

    int left = bar_chenar.left + bar_chenar.width * (1.0f - handleToBarRatio) * interpolare(value,minValue,maxValue);
    Slider.handle_chenar = makeRect(left, bar_chenar.top, left + bar_chenar.width * handleToBarRatio, bar_chenar.bottom);

    int Slider_SPACING_OFFSET = 10;
    int chenar_right = bar_chenar.left - Slider_SPACING_OFFSET / 2;
    int chenar_left = chenar_right - textwidth( (char*)(int_to_string(maxValue).c_str()) ) - Slider_SPACING_OFFSET - 25;
    int chenar_height = std::max(textheight( (char*)(int_to_string(maxValue).c_str()) ) + Slider_SPACING_OFFSET, bar_chenar.height);
    Slider.value_chenar = getExpanded(makeRect( chenar_left, bar_chenar.ycenter - chenar_height / 2, chenar_right, bar_chenar.ycenter + chenar_height / 2), -Slider_STROKE);

    Slider.barColor = barColor;
    Slider.handleColor = handleColor;
}

Slider makeSlider(Rect bar_chenar, float minValue, float maxValue, float value, float handleToBarRatio, int barColor, int handleColor)
{
    Slider s;
    initSlider(s,bar_chenar,minValue,maxValue,value,handleToBarRatio, barColor, handleColor);
    return s;
}

void _drawSliderValue(Slider& Slider, int textColor, int bgColor)
{
    drawFilledRect(Slider.value_chenar, bgColor);

    drawText(int_to_string(Slider.value), Slider.value_chenar.xcenter, Slider.bar_chenar.ycenter, textColor, bgColor, CENTER_ALIGNMENT);

    drawRect_StrokeOnly(Slider.value_chenar, Slider_STROKE, WHITE);
}

void drawSlider(Slider& Slider, int textColor, int bgColor)
{
    drawFilledRect(Slider.bar_chenar, Slider.barColor);
    drawFilledRect(getExpanded(Slider.handle_chenar,-Slider_STROKE), Slider.handleColor);
    _drawSliderValue(Slider, textColor, bgColor);
}

void followMouse(Slider& Slider)
{
    assert(Slider.isBeingSlided);
    int new_left = mouse.x - Slider.xOnHandle;
    if(new_left < Slider.bar_chenar.left)
    {
        new_left = Slider.bar_chenar.left;
    }
    else if(new_left > Slider.bar_chenar.right - Slider.handle_chenar.width)
    {
        new_left = Slider.bar_chenar.right - Slider.handle_chenar.width;
    }
    Slider.handle_chenar = getSlided(Slider.handle_chenar, new_left - Slider.handle_chenar.left, 0);
    Slider.value = interpolare(Slider.handle_chenar.left, Slider.bar_chenar.left, Slider.bar_chenar.right - Slider.handle_chenar.width, Slider.minValue, Slider.maxValue);
}

bool updateSlider(Slider& Slider, int textColor, int bgColor)
{
    if(Slider.isBeingSlided)
    {
        if(mouse.leftHasBeenReleased)
        {
            Slider.isBeingSlided = false;
        }
        else
        {
            if(mouse.hasMoved)
            {
                followMouse(Slider);
                drawSlider(Slider, textColor, bgColor);
                return true;
            }
        }
    }
    else if(mouse.lefthasBeenClicked && isPointInsideRect(mouse.cursor,Slider.handle_chenar))
    {
        Slider.isBeingSlided = true;
        Slider.xOnHandle = mouse.x - Slider.handle_chenar.left;
    }
    return false;
}



////////////// SCROLL BAR ////////////////////////////////////
struct VertocalScrollBar
{
    Rect bar_chenar;
    Rect handle_chenar;
    float minValue;
    float maxValue;
    float value;

    bool isBeingSlided = false;
    int yOnHandle;
    float handleToBarRatio;

    int barColor;
    int handleColor;
};

void drawVertocalScrollBar(VertocalScrollBar& scrollBar)
{
    drawFilledRect(scrollBar.bar_chenar, scrollBar.barColor);
    drawFilledRect(getExpanded(scrollBar.handle_chenar,-Slider_STROKE), scrollBar.handleColor);

    //drawText(int_to_string(scrollBar.value), scrollBar.bar_chenar.xcenter, scrollBar.bar_chenar.ycenter, WHITE,BLACK,LEFT_ALIGNMENT);
}


void initVertocalScrollBar(VertocalScrollBar& scrollBar, Rect bar_chenar, float minValue, float maxValue, float value, float handleToBarRatio, int barColor, int handleColor)
{
    scrollBar.bar_chenar = bar_chenar;
    scrollBar.minValue = minValue;
    scrollBar.maxValue = maxValue;

    scrollBar.barColor = barColor;
    scrollBar.handleColor = handleColor;



    scrollBar.value = value;

    int top = bar_chenar.top + bar_chenar.height * (1.0f- handleToBarRatio) * interpolare(value,minValue,maxValue);
    scrollBar.handle_chenar = makeRect(bar_chenar.left, top, bar_chenar.right, top + bar_chenar.height * handleToBarRatio);
}

VertocalScrollBar makeVertocalScrollBar(Rect bar_chenar, float minValue, float maxValue, float value, float handleToBarRatio, int barColor, int handleColor)
{
    VertocalScrollBar s;
    initVertocalScrollBar(s,bar_chenar,minValue,maxValue,value,handleToBarRatio,barColor,handleColor);
    return s;
}



void followMouse(VertocalScrollBar& scrollBar)
{
    assert(scrollBar.isBeingSlided);
    int new_top = mouse.y - scrollBar.yOnHandle;
    if(new_top < scrollBar.bar_chenar.top)
    {
        new_top = scrollBar.bar_chenar.top;
    }
    else if(new_top > scrollBar.bar_chenar.bottom - scrollBar.handle_chenar.height)
    {
        new_top = scrollBar.bar_chenar.bottom - scrollBar.handle_chenar.height;
    }
    scrollBar.handle_chenar = getSlided(scrollBar.handle_chenar,  0, new_top - scrollBar.handle_chenar.top);
    scrollBar.value = interpolare(scrollBar.handle_chenar.top, scrollBar.bar_chenar.top, scrollBar.bar_chenar.bottom - scrollBar.handle_chenar.height, scrollBar.minValue, scrollBar.maxValue);
}

void updateVertocalScrollBar(VertocalScrollBar& scrollBar)
{
    if(scrollBar.isBeingSlided)
    {
        if(mouse.leftHasBeenReleased)
        {
            scrollBar.isBeingSlided = false;
        }
        else
        {
            if(mouse.hasMoved)
            {
                followMouse(scrollBar);
                drawVertocalScrollBar(scrollBar);
            }
        }
    }
    else if(mouse.lefthasBeenClicked && isPointInsideRect(mouse.cursor,scrollBar.handle_chenar))
    {
        scrollBar.isBeingSlided = true;
        scrollBar.yOnHandle = mouse.y - scrollBar.handle_chenar.top;
    }
}
