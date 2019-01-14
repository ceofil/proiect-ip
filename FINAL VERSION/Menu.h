#pragma once

#include <iostream>

#include "Level.h"
#include "Button.h"
#include "LevelManager.h"
#include "UtilityFunctions.h"
#include "SetLevelProperties.h"
#include "RightInGameMenu.h"
#include "Instructions.h"
#include "Settings.h"

//gameState
#define FIRST_MENU 0
#define SELECT_LEVEL_TO_EDIT 1
#define SET_NEW_LEVEL_PROPERTIES 2
#define SELECT_LEVEL_TO_PLAY 3
#define EDIT_LEVEL 4
#define PLAY_LEVEL 5
#define INSTRUCTIONS 6
#define SETTINGS 7




int bgColor = COLOR(121,193,255);
int xCenter = WINDOW_WIDTH/2;

int gameState;
bool gameOver = false;
Level level;



Button playButton = makeButton(makeRectFromCenter(xCenter,255,buttonWidth,buttonHeight),"PLAY",buttonColor);
Button editButton = makeButton(makeRectFromCenter(xCenter,310,buttonWidth,buttonHeight),"EDIT",buttonColor);
Button instructionsButton = makeButton(makeRectFromCenter(xCenter,365,buttonWidth,buttonHeight),"INSTRUCTIONS",buttonColor);
Button settingsButton = makeButton(makeRectFromCenter(xCenter,420,buttonWidth,buttonHeight),"SETTINGS",buttonColor);
Button exitButton = makeButton(makeRectFromCenter(xCenter,475,buttonWidth,buttonHeight),"EXIT",buttonColor);

Button nextLevelButton = makeButton(setPartitionsButton.chenar, "NEXT", buttonColor);
Button previousLevelButton = makeButton(editPiecesButton.chenar, "PREVIOUS", buttonColor);


int i = 0;
int menu_TOP = 200;
int spacing = 2;


void Save()
{
    levels[selected_level] = level;
    SaveLevel(levels[selected_level], getLevelFileName(selected_level));
    save_levels();
}

void drawTitleScreen()
{
    drawText("SPLIT",WINDOW_WIDTH/2,150,buttonColor,bgColor,CENTER_ALIGNMENT,4,9);

    //just a lot of hard coded values


    drawFilledRect(makeRect(623,111,647,183),bgColor);

    drawLine(635,85,635,210,buttonColor,10);
    drawPiece(0,635,85,10);
    drawPiece(1,635,210,10);

    drawPiece(0,347,157,10);
    drawPiece(2,416,128,10);
    drawPiece(2,452,177,12);
    drawPiece(1,551,118,12);
    drawPiece(2,607,175,7);
    drawPiece(2,659,120,7);
    drawPiece(1,741,120,7);
    drawPiece(0,701,176,11);
}

void SetMenuTo_FIRST_MENU()
{
    DrawBackground(bgColor);
    gameState = FIRST_MENU;
    drawTitleScreen();
    drawButton(playButton);
    drawButton(editButton);
    drawButton(instructionsButton);
    drawButton(settingsButton);
    drawButton(exitButton);
}

void SetMenuTo_PLAY_LEVEL()
{
    DrawBackground(bgColor);
    gameState = PLAY_LEVEL;

    level = levels[selected_level];

    drawCurrentLevelIndex(selected_level,current_number_of_levels,bgColor);

    drawBoard(level.brd);
    drawButton(nextLevelButton);
    drawButton(previousLevelButton);
    drawInfo(level.brd,bgColor);
    drawButton(backButton);
    delay(256);
}

void SetMenuTo_EDIT_LEVEL()
{
    DrawBackground(bgColor);
    gameState = EDIT_LEVEL;
    editState = SET_PARTITIONS;

    level = levels[selected_level];

    drawBoard(level.brd);
    drawButton(editPiecesButton);
    drawButton(backButton);
    drawButton(setPartitionsButton);
    drawButton(deleteLevelButton);

    pieceType = 0;
    drawInfo(level.brd, bgColor);

    delay(256);
}

void SetMenuTo_SELECT_LEVEL_TO_PLAY()
{
    DrawBackground(bgColor);
    gameState = SELECT_LEVEL_TO_PLAY;

    DeselectLevel();

    SetScrollBarDimensions(bgColor);
    drawVertocalScrollBar(scrollBar);

    draw_MINI_LEVELS(bgColor);
    drawButton(backButton);
    delay(512);
}

void SetMenuTo_SELECT_LEVEL_TO_EDIT()
{
    DrawBackground(bgColor);
    gameState = SELECT_LEVEL_TO_EDIT;

    DeselectLevel();

    SetScrollBarDimensions(bgColor);
    drawVertocalScrollBar(scrollBar);

    draw_MINI_LEVELS(bgColor);
    drawButton(backButton);
    DrawAddLevelButton();
    delay(512);
}

void SetMenuTo_SET_NEW_LEVEL_PROPERTIES()
{
    DrawBackground(bgColor);
    gameState = SET_NEW_LEVEL_PROPERTIES;

    drawSetLevelProperties_Options(bgColor);

    delay(256);
}

void SetMenuTo_INSTRUCTIONS()
{
    DrawBackground(bgColor);
    gameState = INSTRUCTIONS;
    level = instructionsLevel;

    drawAllInstructions(bgColor);
    drawButton(backButton);
    delay(256);
}


void SetMenuTo_SETTINGS()
{
    DrawBackground(bgColor);
    gameState = SETTINGS;

    level = settingsLevel;

    DrawSettings(bgColor);
    drawButton(backButton);
    delay(256);
}

void HandleBoardInput_PARTITIONS()
{
    if(mouse.isInsideWindow == false || mouse.leftIsPressed == false)
    {
        level.brd.partitionIsSelected = false;
    }

    if(isPointInsideRect(mouse.cursor,level.brd.chenar))
    {
        if(mouse.leftIsPressed)
        {
            if(level.brd.partitionIsSelected)
            {
                if(setCellToPartition(mouse.cursor, level.brd) && gameState != INSTRUCTIONS && gameState != SETTINGS)
                {
                    drawInfo_OF_PARTITIONS(level.brd, bgColor);
                    level.isSolved = checkFor_SOLVED.isChecked;
                }
            }
            else
            {
                setSelectedPartition(mouse.cursor, level.brd);
            }
        }
        else if(mouse.rightIsPressed)
        {
            if(removeCellFromPartition(mouse.cursor, level.brd)  && gameState != INSTRUCTIONS && gameState != SETTINGS)
            {
                drawInfo_OF_PARTITIONS(level.brd, bgColor);
                level.isSolved = checkFor_SOLVED.isChecked;
            }
        }
    }
}

void HandleBoardInput_PIECES()
{
    if(isPointInsideRect(mouse.cursor,level.brd.chenar))
    {
        Vec2 gridPos = cursorToGridPos(mouse.cursor, level.brd);
        if(mouse.lefthasBeenClicked)
        {
            PlacePiece(gridPos.x, gridPos.y, pieceType, level.brd);

            //I should make PlacePiece() retrun a bool that tells me if the board has modified so i don't redraw the info if not needed, just like I did with setCellToPartition
            //but this redrawing is only done once when the mouse is clicked, only one frame, so it doesn't bother me
            drawInfo_OF_PARTITIONS(level.brd, bgColor);
        }
        else if(mouse.righthasBeenClicked)
        {
            RemovePiece(gridPos.x, gridPos.y, level.brd);
            drawInfo_OF_PARTITIONS(level.brd, bgColor);
        }
    }
}

void HandleInput()
{
    switch(gameState)
    {
    case FIRST_MENU:
    {
        if(buttonHasBeenClicked(playButton))
        {
            LEVELS_ABOSOLUTE_TOP = 0;
            SetMenuTo_SELECT_LEVEL_TO_PLAY();
        }
        if(buttonHasBeenClicked(editButton))
        {
            LEVELS_ABOSOLUTE_TOP = 0;
            SetMenuTo_SELECT_LEVEL_TO_EDIT();
        }
        if(buttonHasBeenClicked(instructionsButton))
        {
            SetMenuTo_INSTRUCTIONS();
        }
        if(buttonHasBeenClicked(settingsButton))
        {
            SetMenuTo_SETTINGS();
        }
        if(buttonHasBeenClicked(exitButton))
        {
            save_levels();
            gameOver = true;
        }
        break;

    }
    case SELECT_LEVEL_TO_PLAY:
    {
        Highlight_OnMouseOver(bgColor);
        updateScrollBar(bgColor);
        if(level_is_selected)
        {
            level = levels[selected_level];
            SetMenuTo_PLAY_LEVEL();
        }
        else
        {
            SelectLevel(gameState,SELECT_LEVEL_TO_PLAY);
        }
        if(buttonHasBeenClicked(backButton))
        {
            SetMenuTo_FIRST_MENU();
        }
        break;
    }
    case SELECT_LEVEL_TO_EDIT:
    {
        Highlight_OnMouseOver(bgColor);
        updateScrollBar(bgColor,true);
        if(level_is_selected)
        {
            level = levels[selected_level];
            SetMenuTo_EDIT_LEVEL();
        }
        else
        {
            SelectLevel(gameState,SELECT_LEVEL_TO_PLAY);
        }
        if(buttonHasBeenClicked(backButton))
        {
            SetMenuTo_FIRST_MENU();
        }
        else if(buttonHasBeenClicked(addLevelButton) && current_number_of_levels<MAX_NUMBER_OF_LEVELS)
        {
            SetMenuTo_SET_NEW_LEVEL_PROPERTIES();
        }
        break;
    }
    case SET_NEW_LEVEL_PROPERTIES:
    {
        if(propertiesAreReady && buttonHasBeenClicked(confirmButton))
        {
            level.brd = getEmptyBoard(numberOf_PIECES,numberOf_PIECE_TYPES);
            addLevel(level);
            selected_level = current_number_of_levels-1;
            level_is_selected = true;
            ResetSelectedLevelProperties();
            SetMenuTo_EDIT_LEVEL();
        }
        SetLevelProperties(bgColor);
        break;
    }
    case PLAY_LEVEL:
    {
        HandleBoardInput_PARTITIONS();
        if(buttonHasBeenClicked(backButton))
        {
            Save();
            SetMenuTo_SELECT_LEVEL_TO_PLAY();
        }
        else if(buttonHasBeenClicked(nextLevelButton) && (allowUserToPlayAnyLevel || checkFor_SOLVED.isChecked == true)) //isSolved is kinda expensive and its already called for the check box so I'll use that
        {
            if(selected_level + 1 < current_number_of_levels)
            {
                Save();
                selected_level++;
                level = levels[selected_level];
                SetMenuTo_PLAY_LEVEL();
            }
        }
        else if(buttonHasBeenClicked(previousLevelButton))
        {
            if(selected_level - 1 >= 0)
            {
                Save();
                selected_level--;
                level = levels[selected_level];
                SetMenuTo_PLAY_LEVEL();
            }
        }
        break;
    }
    case INSTRUCTIONS:
    {
        if(buttonHasBeenClicked(backButton))
        {
            SetMenuTo_FIRST_MENU();
        }
        HandleBoardInput_PARTITIONS();
        break;
    }
    case SETTINGS:
    {
        if(buttonHasBeenClicked(backButton))
        {
            SetMenuTo_FIRST_MENU();
        }
        HandleBoardInput_PARTITIONS();
        if(UpdateSettings(bgColor))
        {
            drawBoard(level.brd);
        }
        break;
    }
    case EDIT_LEVEL:
    {
        switch(editState)
        {
        case SET_PARTITIONS:
        {
            HandleBoardInput_PARTITIONS();
            break;
        }
        case EDIT_PIECES:
        {
            HandleBoardInput_PIECES();
            UpdateSelectedPieceType(level.brd.numberOfPieceTypes, bgColor);
            break;
        }
        }

        if(buttonHasBeenClicked(backButton))
        {
            Save();
            SetMenuTo_SELECT_LEVEL_TO_EDIT();
        }
        else if(buttonHasBeenClicked(editPiecesButton))
        {
            editState = EDIT_PIECES;
            drawPieceOptions(level.brd.numberOfPieceTypes, bgColor);
        }
        else if(buttonHasBeenClicked(setPartitionsButton))
        {
            editState = SET_PARTITIONS;
            drawPieceOptions(level.brd.numberOfPieceTypes, bgColor);
            pieceType = 0;
        }
        else if(buttonHasBeenClicked(deleteLevelButton))
        {
            removeLevel(selected_level);
            DeselectLevel();
            SetMenuTo_SELECT_LEVEL_TO_EDIT();
        }
        break;
    }
    }
}

