#pragma once
#include <algorithm>
#include "CheckBox.h"
#include "Button.h"
#include "MouseState.h"
#include "Board.h"
#include "Rect.h"
#include "Colors.h"

//editState
#define SET_PARTITIONS 0
#define EDIT_PIECES 1
int editState;

//playState;
//TO DO
//TO DO
//TO DO
//int playState;

const int xAlignCenter = WINDOW_WIDTH - MARGIN - buttonWidth / 2;
const int yAlignSpacing = 10;
const int rightMenuStroke = 4;

Button editPiecesButton = makeButton(makeRectFromCenter(  xAlignCenter,  MARGIN + buttonHeight/2,  buttonWidth, buttonHeight), "PIECES", buttonColor);
Button setPartitionsButton = makeButton(makeRectFromCenter(  xAlignCenter,  MARGIN + buttonHeight*3/2 + yAlignSpacing,  buttonWidth, buttonHeight), "PARTITIONS", buttonColor);
Button deleteLevelButton = makeButton(makeRectFromCenter(xAlignCenter , WINDOW_HEIGHT-MARGIN - buttonHeight/2 - 5, buttonWidth,buttonHeight),"DELETE LEVEL", buttonColor);
Rect chenarInfo = getExpanded(makeRect(WINDOW_WIDTH - MARGIN - buttonWidth, setPartitionsButton.chenar.bottom + yAlignSpacing, WINDOW_WIDTH - MARGIN, deleteLevelButton.chenar.top - yAlignSpacing), -rightMenuStroke);


int checkBox_left = xAlignCenter - 100;
int checkBox_spacing = 30;
CheckBox checkFor_SOLVED = makeCheckBox(checkBox_left,chenarInfo.bottom - checkBox_spacing * 1 - buttonHeight, 20, buttonColor, buttonColor, "solved");
CheckBox checkFor_UNINTERRUPTED = makeCheckBox(checkBox_left,chenarInfo.bottom - checkBox_spacing * 2 - buttonHeight, 20, buttonColor,  buttonColor, "uninterrupted");
CheckBox checkFor_COMPLETE = makeCheckBox(checkBox_left,chenarInfo.bottom - checkBox_spacing * 3 - buttonHeight, 20, buttonColor,  buttonColor, "complete");
CheckBox checkFor_SAMEFORM = makeCheckBox(checkBox_left,chenarInfo.bottom - checkBox_spacing * 4 - buttonHeight, 20, buttonColor,  buttonColor, "same form");

int pieceType = 0;

void drawCurrentLevelIndex(int selected_level, int current_number_of_levels, int bgColor)
{
    drawFilledRect(deleteLevelButton.chenar,getDarkerColor(bgColor,0));
    drawText("Level " + int_to_string(selected_level+1) + "/" + int_to_string(current_number_of_levels), deleteLevelButton.chenar.xcenter, deleteLevelButton.chenar.ycenter, BLACK, getDarkerColor(bgColor,0), CENTER_ALIGNMENT);
}


void drawPieceOptions(int nrTypes, int bgColor)
{
    assert(nrTypes > 0 && nrTypes <= 3);
    int optionWidth = buttonWidth / nrTypes + 1;
    int firstLeft = chenarInfo.left;
    for(int i = 0; i < nrTypes; i++)
    {
        int right = std::min(firstLeft + (i+1)*optionWidth, deleteLevelButton.chenar.right);
        int left = right - optionWidth;
        Rect chenar = makeRect(left, chenarInfo.bottom-buttonHeight, right, chenarInfo.bottom);
        if(pieceType == i && editState == EDIT_PIECES)
        {
            drawFilledRect(chenar, getBrighterColor(bgColor,25));
        }
        else
        {
            drawFilledRect(chenar, bgColor);
        }
        drawPiece(i, chenar.xcenter, chenar.ycenter, chenar.height/4);
    }
    drawRect_StrokeOnly(makeRect(chenarInfo.left,chenarInfo.bottom - buttonHeight, chenarInfo.right, chenarInfo.bottom), rightMenuStroke, buttonColor);
}

void hidePieceOptions(int bgColor)
{
    drawFilledRect(chenarInfo.left,chenarInfo.bottom - buttonHeight, chenarInfo.right, chenarInfo.bottom, bgColor);
}

void drawInfo_OF_PARTITIONS(Board brd, int bgColor)
{
    drawFilledRect(makeRect(chenarInfo.left,chenarInfo.top,chenarInfo.right,chenarInfo.bottom-rightMenuStroke-buttonHeight),bgColor);
    if(brd.maxNumberOfPartitions == 4)
    {
        for(int partitionId = 0; partitionId < brd.maxNumberOfPartitions; partitionId++)
        {
            int infoPieceSpacing = 5;
            int infoSpacing = 10 + textheight((char*)"16/16");
            int infoTop = chenarInfo.top + infoSpacing;
            int infoLeft = checkBox_left;



            Rect partChenar = makeRectFromCenter(infoLeft, infoTop + infoSpacing * partitionId, 10, 10);
            drawFilledRect( partChenar, PARTITION_COLORS[partitionId] );
            std::string infoText = int_to_string(brd.partitionCounter[partitionId]) + "/" + int_to_string(brd.maxPartitionLength);
            drawText(infoText, partChenar.right+infoPieceSpacing, partChenar.ycenter, BLACK, bgColor, RIGHT_ALIGNMENT);

            for(int pType = 0; pType < brd.numberOfPieceTypes; pType++)
            {
                if(_partitionHasPieceType(brd, partitionId, pType))
                {
                    drawPiece(pType, chenarInfo.right - (infoLeft - chenarInfo.left) - (infoPieceSpacing + partChenar.width) * pType, partChenar.ycenter, partChenar.width/2);
                }
            }
        }
    }
    else
    {
        for(int partitionId = 0; partitionId < 4; partitionId++)
        {
            int infoPieceSpacing = 5;
            int infoSpacing = 10 + textheight((char*)"16/16");
            int infoTop = chenarInfo.top + infoSpacing;
            int infoLeft = chenarInfo.left + 18;



            Rect partChenar = makeRectFromCenter(infoLeft, infoTop + infoSpacing * partitionId, 10, 10);
            drawFilledRect( partChenar, PARTITION_COLORS[partitionId] );
            std::string infoText = int_to_string(brd.partitionCounter[partitionId]) + "/" + int_to_string(brd.maxPartitionLength);
            drawText(infoText, partChenar.right+infoPieceSpacing, partChenar.ycenter, BLACK, bgColor, RIGHT_ALIGNMENT);

            int infoPieceLeft = partChenar.right+5 + textwidth((char*)infoText.c_str()) + partChenar.width;
            for(int pType = 0; pType < brd.numberOfPieceTypes; pType++)
            {
                if(_partitionHasPieceType(brd, partitionId, pType))
                {
                    drawPiece(pType, infoPieceLeft + (infoPieceSpacing + partChenar.width) * pType, partChenar.ycenter, partChenar.width/2);
                }
            }
        }
        for(int partitionId = 0; partitionId < 4; partitionId++)
        {
            int infoPieceSpacing = 5;
            int infoSpacing = 10 + textheight((char*)"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
            int infoTop = chenarInfo.top + infoSpacing;
            int infoLeft = chenarInfo.xcenter + 18;



            Rect partChenar = makeRectFromCenter(infoLeft, infoTop + infoSpacing * partitionId, 10, 10);
            drawFilledRect( partChenar, PARTITION_COLORS[partitionId+4] );
            std::string infoText = int_to_string(brd.partitionCounter[partitionId+4]) + "/" + int_to_string(brd.maxPartitionLength);
            drawText(infoText, partChenar.right+infoPieceSpacing, partChenar.ycenter, BLACK, bgColor, RIGHT_ALIGNMENT);

            int infoPieceLeft = partChenar.right+5 + textwidth((char*)infoText.c_str()) + partChenar.width;
            for(int pType = 0; pType < brd.numberOfPieceTypes; pType++)
            {
                if(_partitionHasPieceType(brd, partitionId+4, pType))
                {
                    drawPiece(pType, infoPieceLeft + (infoPieceSpacing + partChenar.width) * pType, partChenar.ycenter, partChenar.width/2);
                }
            }
        }
    }

    checkFor_SOLVED.isChecked = isBoardSolved(brd);
    checkFor_UNINTERRUPTED.isChecked = arePartitionsUninterrupted(brd);
    checkFor_COMPLETE.isChecked = isBoardComplete(brd);
    drawCheckBox(checkFor_SOLVED, bgColor);
    drawCheckBox(checkFor_UNINTERRUPTED, bgColor);
    drawCheckBox(checkFor_COMPLETE, bgColor);

    if(brd.maxNumberOfPartitions == 4)
    {
        checkFor_SAMEFORM.isChecked = AllPartitionsHaveTheSameForm(brd);
        drawCheckBox(checkFor_SAMEFORM, bgColor);
    }
}

void drawInfo(Board brd, int bgColor)
{
    drawPieceOptions(brd.numberOfPieceTypes, bgColor);
    drawRect_StrokeOnly(chenarInfo, rightMenuStroke, buttonColor);
    drawInfo_OF_PARTITIONS(brd, bgColor);

}


void UpdateSelectedPieceType(int nrTypes, int bgColor)
{
    Rect r = makeRect(chenarInfo.left,chenarInfo.bottom - buttonHeight, chenarInfo.right, chenarInfo.bottom);
    if(mouse.lefthasBeenClicked && isPointInsideRect(mouse.cursor, r))
    {
        pieceType = (mouse.x - r.left) / (r.width / (float)nrTypes);
        drawPieceOptions(nrTypes, bgColor);
    }
}
