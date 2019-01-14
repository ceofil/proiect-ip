#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Level.h"
#include "UtilityFunctions.h"
#include "Slider.h"
#include "BoardSolvingFunctions.h"

#define MAX_NUMBER_OF_LEVELS 128

//user will be able to change this in the options menu
//if it's false the user will not be able to press "next level" until he solves the current one
bool allowUserToPlayAnyLevel;

int current_number_of_levels;
int selected_level = 0;
bool level_is_selected = false;
int LEVELS_ABOSOLUTE_TOP = 0;

const int MINI_WIDTH = 225;
const int MINI_SPACING = 30;
Rect FIRST_MINI_RECT()
{
    return makeRect(MARGIN, LEVELS_ABOSOLUTE_TOP + MARGIN, MARGIN + MINI_WIDTH - MINI_WIDTH%8, LEVELS_ABOSOLUTE_TOP + MARGIN + MINI_WIDTH - MINI_WIDTH%8);
}
const int MINI_OFFSET = FIRST_MINI_RECT().width + MINI_SPACING;
const int LEVELS_PER_ROW = (WINDOW_WIDTH - 2 * MARGIN - MINI_WIDTH)/MINI_OFFSET + 1;

Button addLevelButton = makeButton(FIRST_MINI_RECT(),"NEW",GREEN);
Button backButton = makeButton(makeRect(0,0,MARGIN-MINI_SPACING,buttonHeight),"BACK",buttonColor);

Level levels[MAX_NUMBER_OF_LEVELS];
VertocalScrollBar scrollBar;

bool highlightBuffer[MAX_NUMBER_OF_LEVELS];
#define MINI_HIGHLIGHT_STROKE 2
#define MINI_HIGHLIGHT_SPACING 10
#define MINI_HIGHLIGHT_COLOR BLACK


std::string getLevelFileName(int level_index)
{
    return "level" + int_to_string(level_index) + ".txt";
}

void load_levels()
{
    std::ifstream gameDataFile("GameData.txt");
    gameDataFile >> current_number_of_levels;


    for(int level_index = 0; level_index < current_number_of_levels; level_index++)
    {
        LoadLevel(levels[level_index], getLevelFileName(level_index));
    }
}

void save_levels()
{
    std::ofstream gameDataFile("GameData.txt");
    gameDataFile << current_number_of_levels;

    for(int level_index = 0; level_index < current_number_of_levels; level_index++)
    {
        SaveLevel(levels[level_index], getLevelFileName(level_index));
    }
}

bool validLevelIndex(int index)
{
    return index >= 0 && index < current_number_of_levels;
}

void addLevel(Level& lvl)
{
    if(current_number_of_levels<MAX_NUMBER_OF_LEVELS)
    {
        levels[current_number_of_levels++] = lvl;
    }
    else
    {
        // TO DO: let the user know why nothing is happening
    }
}

void removeLevel(int index)
{
    if(validLevelIndex(index))
    {
        for(int i = index; i + 1 < current_number_of_levels; i++)
        {
            levels[i] = levels[i+1];
        }
        current_number_of_levels--;
    }
}

void drawLevel_MINI(Level& lvl, Rect chenar, int bgColor)
{
    Rect aux = lvl.brd.chenar;
    setChenar(chenar, lvl.brd);
    drawBoard(lvl.brd);
    setChenar(aux, lvl.brd);
    if(lvl.isSolved)
    {
        drawRect_StrokeOnly(chenar, 3, WHITE);//getBrighterColor(bgColor,50));
    }

}

Rect getMiniRect(int levelIndex)
{
    int y = levelIndex / LEVELS_PER_ROW;
    int x = levelIndex % LEVELS_PER_ROW;
    return getSlided(FIRST_MINI_RECT(), x*MINI_OFFSET,  y*MINI_OFFSET);
}

void draw_NumberOfSolvedLevels(int bgColor)
{
    int nrOfSolvedLevels = 0;
    for(int index = 0; index < current_number_of_levels; index++)
    {
        if(levels[index].isSolved)
        {
            nrOfSolvedLevels++;
        }
    }
    drawText("SOLVED", MARGIN/2-5, WINDOW_HEIGHT-20, getDarkerColor(bgColor,45), bgColor, CENTER_ALIGNMENT);
    drawText(int_to_string(nrOfSolvedLevels) + "/" + int_to_string(current_number_of_levels), MARGIN/2-5, WINDOW_HEIGHT - 39, getDarkerColor(bgColor,45), bgColor, CENTER_ALIGNMENT);
}

void draw_MINI_LEVELS(int bgColor)
{
    int firstBottom = getMiniRect(0).bottom;
    int startIndex = 0;
    while(firstBottom <= 0)
    {
        firstBottom += MINI_OFFSET;
        startIndex += LEVELS_PER_ROW;
    }

    int lastTop = getMiniRect(startIndex).top;
    int endIndex = startIndex;
    while(lastTop <= WINDOW_HEIGHT)
    {
        lastTop += MINI_OFFSET;
        endIndex += LEVELS_PER_ROW;
    }

    startIndex = std::max(startIndex, 0);
    endIndex = std::min(endIndex, current_number_of_levels - 1);


    for(int index = startIndex; index <= endIndex; index++)
    {
        drawLevel_MINI(levels[index],getMiniRect(index), bgColor);
    }

    draw_NumberOfSolvedLevels(bgColor);
}

bool levelHasBeenClicked(int index)
{
    assert(validLevelIndex(index));
    return mouse.lefthasBeenClicked && isPointInsideRect(mouse.cursor, getMiniRect(index));
}

void SelectLevel(int gameState, int SELECT_LEVEL_TO_PLAY)
{
    assert(level_is_selected == false);
    for(int index = 0; index < current_number_of_levels; index++)
    {
        if(levelHasBeenClicked(index))
        {
            if(gameState != SELECT_LEVEL_TO_PLAY || allowUserToPlayAnyLevel || index == 0 || levels[index-1].isSolved || levels[index].isSolved)
            {
                selected_level = index;
                level_is_selected = true;
            }
            return;
        }
    }
}

void DeselectLevel()
{
    for(int i = 0 ; i< MAX_NUMBER_OF_LEVELS; i++)
    {
        highlightBuffer[i] = false;
    }
    level_is_selected = false;
}


void HighlightLevel(int index)
{
    drawRect_StrokeOnly(getExpanded(getMiniRect(index),MINI_HIGHLIGHT_SPACING),MINI_HIGHLIGHT_STROKE,MINI_HIGHLIGHT_COLOR);
}

void UnhighlightLevel(int index, int bgColor)
{
    drawRect_StrokeOnly(getExpanded(getMiniRect(index),MINI_HIGHLIGHT_SPACING),MINI_HIGHLIGHT_STROKE,bgColor);
}


void Highlight_OnMouseOver(int bgColor)
{
    for(int i = 0 ; i < current_number_of_levels; i++)
    {
        Rect mini_rect = getMiniRect(i);
        if(highlightBuffer[i] == false)
        {
            if(isPointInsideRect(mouse.cursor,mini_rect))
            {
                highlightBuffer[i] = true;
                HighlightLevel(i);
            }
        }
        else
        {
            if(isPointInsideRect(mouse.cursor,mini_rect) == false)
            {
                highlightBuffer[i] = false;
                UnhighlightLevel(i,bgColor);
            }
        }
    }
}

int lastAbsoluteTop = LEVELS_ABOSOLUTE_TOP;
void SetScrollBarDimensions(int bgColor)
{
    lastAbsoluteTop = LEVELS_ABOSOLUTE_TOP;
    LEVELS_ABOSOLUTE_TOP = 0;
    float absoluteHeight = getMiniRect(current_number_of_levels).bottom + MARGIN;
    float handleRatio = WINDOW_HEIGHT / absoluteHeight;
    handleRatio = std::min(0.85f, handleRatio);
    LEVELS_ABOSOLUTE_TOP = lastAbsoluteTop;
    scrollBar = makeVertocalScrollBar(makeRect(WINDOW_WIDTH-25,0,WINDOW_WIDTH,WINDOW_HEIGHT),0,absoluteHeight - WINDOW_HEIGHT,-LEVELS_ABOSOLUTE_TOP,handleRatio,  bgColor , getDarkerColor(bgColor,50));
}

void DrawAddLevelButton()
{
    addLevelButton.chenar = getMiniRect(current_number_of_levels);
    drawButton(addLevelButton);
    drawRect_StrokeOnly(getExpanded(addLevelButton.chenar,-2),2,WHITE);
}

void updateScrollBar(int bgColor,bool drawAddLevelButton = false)
{

    updateVertocalScrollBar(scrollBar);
    int newAbsoluteTop = -scrollBar.value;
    if(newAbsoluteTop != lastAbsoluteTop && mouse.leftHasBeenReleased)
    {

        DrawBackground(bgColor);

        drawVertocalScrollBar(scrollBar);
        LEVELS_ABOSOLUTE_TOP = lastAbsoluteTop = newAbsoluteTop;
        draw_MINI_LEVELS(bgColor);

        if(drawAddLevelButton == true)
        {
            DrawAddLevelButton();
        }

        drawButton(backButton);
    }
}
