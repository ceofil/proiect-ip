#pragma once
#include "CheckBox.h"
#include "Button.h"
#include "MouseState.h"

#define XSPACING 10
#define xAlign WINDOW_WIDTH/2
#define CHOICE_HIGHLIGHT_COLOR BLACK

int yAlignNumberOfPiecsButtons = 150;
Button nrpieces_4 = makeButton(getSlided(makeRectFromCenter(xAlign,yAlignNumberOfPiecsButtons,buttonWidth,buttonHeight),-buttonWidth/2 - XSPACING,0),"4 pieces",buttonColor);
Button nrpieces_8 = makeButton(getSlided(makeRectFromCenter(xAlign,yAlignNumberOfPiecsButtons,buttonWidth,buttonHeight), buttonWidth/2+XSPACING,0),"8 pieces",buttonColor);


int littleWidth = (2*buttonWidth - XSPACING) / 3;

int yAlignPieceTypesButtons = 250;
Button nrtypes_2 = makeButton(getSlided(makeRectFromCenter(xAlign,yAlignPieceTypesButtons,littleWidth,buttonHeight),0,0),"MEDIUM",buttonColor);
Button nrtypes_1 = makeButton(getSlided(makeRectFromCenter(xAlign,yAlignPieceTypesButtons,littleWidth,buttonHeight),-littleWidth-3*XSPACING/2,0),"EASY",buttonColor);
Button nrtypes_3 = makeButton(getSlided(makeRectFromCenter(xAlign,yAlignPieceTypesButtons,littleWidth,buttonHeight),littleWidth+3*XSPACING/2,0),"HARD",buttonColor);

Button confirmButton = makeButton(makeRectFromCenter(xAlign, WINDOW_HEIGHT - 2*buttonHeight,buttonWidth,buttonHeight), "CONFIRM",buttonColor);


int numberOf_PIECES = -1;
int numberOf_PIECE_TYPES = -1;
bool propertiesAreReady = false;

void highlightChoice(Button choice)
{
    drawRect_StrokeOnly(getExpanded(choice.chenar, XSPACING/2), 2, CHOICE_HIGHLIGHT_COLOR);
}

void unhighlightChoice(Button choice, int bgColor)
{
    drawRect_StrokeOnly(getExpanded(choice.chenar, XSPACING/2), 2, bgColor);
}



void drawLevelRequirements(int bgColor)
{
    Rect req = getExpanded(makeRect(nrtypes_1.chenar.left,nrtypes_1.chenar.bottom+2*XSPACING, nrtypes_3.chenar.right, confirmButton.chenar.top - 2*XSPACING),-2);
    drawFilledRect(req,bgColor);
    //drawRect_StrokeOnly(req, 2, getDarkerColor(bgColor,50));
    int spacing = 10;
    int textHeight = textheight((char*)"text");
    int yText = req.top + spacing + textHeight/2;
    if(numberOf_PIECES != -1)
    {
        drawText("PARTITION REQUIREMENTS:", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        drawText("-must contain a piece of every type", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        drawText("-must be the same length", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        drawText("-must be uninterrupted", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        drawText("-the board must be filled", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        if(numberOf_PIECES == 4)
        {
            drawText("-partitions must have the same form", xAlign, yText, buttonColor, bgColor, CENTER_ALIGNMENT); yText += spacing + textHeight;
        }
    }

    if(numberOf_PIECE_TYPES != -1)
    {
        int radius = req.width / 12;
        int yPieces = req.bottom - radius - spacing;
        int xPiece = xAlign - (2*radius*numberOf_PIECE_TYPES + spacing*(numberOf_PIECE_TYPES-1)) / 2 + radius;
        for(int pType = 0; pType < numberOf_PIECE_TYPES; pType++)
        {
            drawPiece(pType, xPiece, yPieces, radius);
            xPiece += 2*radius + spacing;
        }
    }

}

void HandleChoice_PIECES(int bgColor)
{
    if(buttonHasBeenClicked(nrpieces_4))
    {
        numberOf_PIECES = 4;
        highlightChoice(nrpieces_4);
        unhighlightChoice(nrpieces_8,bgColor);
        drawLevelRequirements(bgColor);
    }
    else if(buttonHasBeenClicked(nrpieces_8))
    {
        numberOf_PIECES = 8;
        highlightChoice(nrpieces_8);
        unhighlightChoice(nrpieces_4,bgColor);
        drawLevelRequirements(bgColor);
    }
}

void HandleChoice_PIECE_TYPES(int bgColor)
{
    if(buttonHasBeenClicked(nrtypes_1))
    {
        numberOf_PIECE_TYPES = 1;
        highlightChoice(nrtypes_1);
        unhighlightChoice(nrtypes_2,bgColor);
        unhighlightChoice(nrtypes_3,bgColor);
        drawLevelRequirements(bgColor);
    }
    else if(buttonHasBeenClicked(nrtypes_2))
    {
        numberOf_PIECE_TYPES = 2;
        highlightChoice(nrtypes_2);
        unhighlightChoice(nrtypes_1,bgColor);
        unhighlightChoice(nrtypes_3,bgColor);
        drawLevelRequirements(bgColor);
    }
    else if(buttonHasBeenClicked(nrtypes_3))
    {
        numberOf_PIECE_TYPES = 3;
        highlightChoice(nrtypes_3);
        unhighlightChoice(nrtypes_1,bgColor);
        unhighlightChoice(nrtypes_2,bgColor);
        drawLevelRequirements(bgColor);
    }
}

void LetTheUserConfrimProperties()
{
    if(propertiesAreReady == false && numberOf_PIECES != -1 && numberOf_PIECE_TYPES != -1)
    {
        propertiesAreReady = true;
        drawButton(confirmButton);
    }
}

void ResetSelectedLevelProperties()
{
    numberOf_PIECES = -1;
    numberOf_PIECE_TYPES = -1;
    propertiesAreReady = false;
}

void SetLevelProperties(int bgColor)
{
    HandleChoice_PIECES(bgColor);
    HandleChoice_PIECE_TYPES(bgColor);
    LetTheUserConfrimProperties();
}

void drawSetLevelProperties_Options(int bgColor)
{
    drawButton(nrpieces_4);
    drawButton(nrpieces_8);
    drawButton(nrtypes_1);
    drawButton(nrtypes_2);
    drawButton(nrtypes_3);

    drawText("GAME MODE",xAlign,yAlignNumberOfPiecsButtons-50, WHITE, bgColor, CENTER_ALIGNMENT);
    drawText("DIFFICULTY",xAlign,yAlignPieceTypesButtons-50, WHITE, bgColor, CENTER_ALIGNMENT);
}

//void highlight option

// void unhighlight option



