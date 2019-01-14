#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Button.h"
#include "Colors.h"
#include "LevelManager.h"
#include "UtilityFunctions.h"
#include "CheckBox.h"
#include "Slider.h"

int selectedColorIndex = 0;

Button colorButton_partitions[BRD_SIZE];


CheckBox checkBox_allowUserToPlayAnyLevel = makeCheckBox(WINDOW_WIDTH/2-100,buttonHeight/2,30,buttonColor,buttonColor,"allow access to any level");
Button resetDefaultsButton = makeButton(makeRectFromCenter(WINDOW_WIDTH/4*3,WINDOW_HEIGHT-MARGIN,300,buttonHeight),"RESET DEFAULTS",buttonColor);

Slider r_slider;
Slider g_slider;
Slider b_slider;

Level settingsLevel;

void set_RGB_Sliders()
{
    Rect redBar = makeRectFromCenter(WINDOW_WIDTH/4*3+20,WINDOW_HEIGHT/2+50,WINDOW_WIDTH/4, 25);
    r_slider = makeSlider(redBar, 0, 255, RED_VALUE(PARTITION_COLORS[selectedColorIndex]), 0.2,WHITE, COLOR(255,0,0));
    g_slider = makeSlider(getSlided(redBar,0,40), 0, 255, GREEN_VALUE(PARTITION_COLORS[selectedColorIndex]), 0.2,WHITE, COLOR(0,255,0));
    b_slider = makeSlider(getSlided(redBar,0,80), 0, 255, BLUE_VALUE(PARTITION_COLORS[selectedColorIndex]), 0.2,WHITE, COLOR(0,0,255));
}

void initializeColorButtons()
{
    int spacing = 20;
    int colorButtonWidth = (WINDOW_WIDTH/2 - 5*spacing)/4;
    Rect firstRect = makeRect(WINDOW_WIDTH/2 + spacing, 250,WINDOW_WIDTH/2 + spacing + colorButtonWidth, 250+buttonHeight);

    for(int clr = 0; clr<8; clr++)
    {
        int x = clr % 4;
        int y = clr / 4;
        colorButton_partitions[clr] = makeButton(getSlided(firstRect, x*(colorButtonWidth+spacing), y*(buttonHeight+spacing)),"",PARTITION_COLORS[clr]);
    }
    set_RGB_Sliders();
    settingsLevel.brd = getEmptyBoard(8,3);
    setChenar(makeRectFromCenter(WINDOW_WIDTH/4,WINDOW_HEIGHT/2, WINDOW_WIDTH/4, WINDOW_WIDTH/4),settingsLevel.brd);
}

void LoadSettingsFromFile()
{
    std::ifstream settingsFile("Settings.txt");
    int buffer;
    settingsFile >> buffer;
    if(buffer != 0)
    {
        checkBox_allowUserToPlayAnyLevel.isChecked = allowUserToPlayAnyLevel = true;
    }
    else
    {
        checkBox_allowUserToPlayAnyLevel.isChecked = allowUserToPlayAnyLevel = false;
    }
    for(int clr = 0; clr < 8; clr++)
    {
        settingsFile >> PARTITION_COLORS[clr];
    }
    initializeColorButtons();
}

void SaveSettingsToFile()
{
    std::ofstream settingsFile("Settings.txt");
    if(allowUserToPlayAnyLevel)
    {
        settingsFile << 1 << " ";
    }
    else
    {
        settingsFile << 0 << " ";
    }
    for(int clr = 0; clr < 8; clr++)
    {
        settingsFile << PARTITION_COLORS[clr] << " ";
    }
}


void highlightSelectedColor(int bgColor)
{
    drawRect_StrokeOnly(getExpanded(colorButton_partitions[selectedColorIndex].chenar, 10), 1, getDarkerColor(bgColor,30));
}

void unhighlightSelectedColor(int bgColor)
{
    drawRect_StrokeOnly(getExpanded(colorButton_partitions[selectedColorIndex].chenar, 10), 1, bgColor);
}

void DrawSettings(int bgColor)
{
    drawCheckBox(checkBox_allowUserToPlayAnyLevel, bgColor);
    for(int clr = 0; clr<8; clr++)
    {
        drawButton(colorButton_partitions[clr]);
    }


    drawLine(0,buttonHeight, WINDOW_WIDTH,buttonHeight,buttonColor);
    //drawLine(WINDOW_WIDTH/2, buttonHeight + 100, WINDOW_WIDTH/2,WINDOW_HEIGHT - 30,  getDarkerColor(bgColor,30));
    drawText("CHANGE COLORS", WINDOW_WIDTH/2, buttonHeight  + 50, WHITE, bgColor, CENTER_ALIGNMENT);
    drawText("EXAMPLE", WINDOW_WIDTH/4, buttonHeight  + 120, getDarkerColor(bgColor,60), bgColor, CENTER_ALIGNMENT);
    drawText("SELECT COLOR", WINDOW_WIDTH/4*3, buttonHeight  + 120, getDarkerColor(bgColor,60), bgColor, CENTER_ALIGNMENT);
    drawText("RGB PICKER", WINDOW_WIDTH/4*3, r_slider.bar_chenar.top - 25, getDarkerColor(bgColor,60), bgColor, CENTER_ALIGNMENT);
    drawSlider(r_slider, WHITE, bgColor);
    drawSlider(g_slider, WHITE, bgColor);
    drawSlider(b_slider, WHITE, bgColor);

    highlightSelectedColor(bgColor);
    drawButton(resetDefaultsButton);
    drawBoard(settingsLevel.brd);
}

bool UpdateSettings(int bgColor)
{
    if(UpdateCheckBox(checkBox_allowUserToPlayAnyLevel, bgColor))
    {
        allowUserToPlayAnyLevel = checkBox_allowUserToPlayAnyLevel.isChecked;
        SaveSettingsToFile();
    }
    if(buttonHasBeenClicked(resetDefaultsButton))
    {
        for(int clr = 0; clr<8; clr++)
        {
            PARTITION_COLORS[clr] = DEFAULT_PARTITION_COLORS[clr];
            colorButton_partitions[clr].color = PARTITION_COLORS[clr];
            drawButton(colorButton_partitions[clr]);
            SaveSettingsToFile();
        }
        return true;
    }
    for(int clr = 0; clr<8; clr++)
    {
        if(buttonHasBeenClicked(colorButton_partitions[clr]))
        {
            unhighlightSelectedColor(bgColor);

            selectedColorIndex = clr;
            highlightSelectedColor(bgColor);

            set_RGB_Sliders();
            drawSlider(r_slider, WHITE, bgColor);
            drawSlider(g_slider, WHITE, bgColor);
            drawSlider(b_slider, WHITE, bgColor);
        }
    }

    if(updateSlider(r_slider,WHITE,bgColor) || updateSlider(g_slider,WHITE,bgColor) || updateSlider(b_slider,WHITE,bgColor))
    {
        PARTITION_COLORS[selectedColorIndex] = COLOR(r_slider.value,g_slider.value,b_slider.value);
        colorButton_partitions[selectedColorIndex].color = PARTITION_COLORS[selectedColorIndex];
        drawButton(colorButton_partitions[selectedColorIndex]);
        SaveSettingsToFile();
        return true;
    }
    return false;
}
