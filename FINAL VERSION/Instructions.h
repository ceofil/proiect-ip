#pragma once

#define COMPLETE 0
#define UNINTERRUPTED 1
#define A_PIECE_OF_EACH_TYPE 2
#define SAME_FORM 3

#define CORRECT_LEVEL 0
#define INCORRECT_LEVEL 1

#include <iostream>
#include <fstream>
#include <string>

#include "Level.h"
#include "UtilityFunctions.h"
#include "Slider.h"
#include "BoardSolvingFunctions.h"

Level COMPLETE_CORRECT_LEVEL;
Level COMPLETE_INCORRECT_LEVEL;

Level UNINTERRUPTED_CORRECT_LEVEL;
Level UNINTERRUPTED_INCORRECT_LEVEL;

Level A_PIECE_OF_EACH_TYPE_CORRECT_LEVEL;
Level A_PIECE_OF_EACH_TYPE_INCORRECT_LEVEL;

Level SAME_FORM_CORRECT_LEVEL;
Level SAME_FORM_INCORRECT_LEVEL;

Level instructionsLevel;

const Rect instructionsChenar = makeRect(0,50,WINDOW_WIDTH/2,WINDOW_HEIGHT/3);


Rect getInstructionChenar(int x, int y)
{
    return getExpanded( getSlided(instructionsChenar,instructionsChenar.width*x,instructionsChenar.height*y), -5);
}

Rect getBoardRect(int x, int y, int correctness)
{
    Rect instructionRect = getInstructionChenar(x,y);
    int boardCenter =  instructionRect.left + 0.25 * instructionRect.width;
    if(correctness == CORRECT_LEVEL)
    {
        boardCenter = instructionRect.left + 0.75 * instructionRect.width;
    }
    return makeRectFromCenter(boardCenter, instructionRect.bottom - 70, 100,100);

}


void LoadInstructionBoards()
{
    LoadLevel(COMPLETE_CORRECT_LEVEL,"COMPLETE_CORRECT.txt");
    setChenar(getBoardRect(0,0,CORRECT_LEVEL),COMPLETE_CORRECT_LEVEL.brd);
    LoadLevel(COMPLETE_INCORRECT_LEVEL, "COMPLETE_INCORRECT.txt");
    setChenar(getBoardRect(0,0,INCORRECT_LEVEL),COMPLETE_INCORRECT_LEVEL.brd);

    LoadLevel(UNINTERRUPTED_CORRECT_LEVEL,"UNINTERRUPTED_CORRECT.txt");
    setChenar(getBoardRect(1,0,CORRECT_LEVEL),UNINTERRUPTED_CORRECT_LEVEL.brd);
    LoadLevel(UNINTERRUPTED_INCORRECT_LEVEL, "UNINTERRUPTED_INCORRECT.txt");
    setChenar(getBoardRect(1,0,INCORRECT_LEVEL),UNINTERRUPTED_INCORRECT_LEVEL.brd);

    LoadLevel(A_PIECE_OF_EACH_TYPE_CORRECT_LEVEL,"A_PIECE_OF_EACH_TYPE_CORRECT.txt");
    setChenar(getBoardRect(0,1,CORRECT_LEVEL),A_PIECE_OF_EACH_TYPE_CORRECT_LEVEL.brd);
    LoadLevel(A_PIECE_OF_EACH_TYPE_INCORRECT_LEVEL, "A_PIECE_OF_EACH_TYPE_INCORRECT.txt");
    setChenar(getBoardRect(0,1,INCORRECT_LEVEL),A_PIECE_OF_EACH_TYPE_INCORRECT_LEVEL.brd);

    LoadLevel(SAME_FORM_CORRECT_LEVEL,"SAME_FORM_CORRECT.txt");
    setChenar(getBoardRect(1,1,CORRECT_LEVEL),SAME_FORM_CORRECT_LEVEL.brd);
    LoadLevel(SAME_FORM_INCORRECT_LEVEL, "SAME_FORM_INCORRECT.txt");
    setChenar(getBoardRect(1,1,INCORRECT_LEVEL),SAME_FORM_INCORRECT_LEVEL.brd);

    instructionsLevel.brd = getEmptyBoard(8,3);

    setChenar(makeRectFromCenter(getInstructionChenar(1,2).xcenter,getInstructionChenar(1,2).ycenter+40,250,250),instructionsLevel.brd);
}

//im going to use some hard coded file names for some files that were created beforehand and contain the board informations
//for examples respected or not respected requirements
void drawInstruction(std::string title, Rect chenar, int bgColor)
{
    int leftColumn = chenar.left + 0.25 * chenar.width;
    int rightColumn = chenar.left + 0.75 * chenar.width;
    int textColor = getDarkerColor(bgColor,200);
    int spacing = 25;
    drawText(title, chenar.xcenter, chenar.top + spacing, textColor, bgColor, CENTER_ALIGNMENT);
    drawText("INCORRECT", leftColumn, chenar.top+spacing*2.5, textColor, bgColor, CENTER_ALIGNMENT);
    drawText("CORRECT", rightColumn, chenar.top+spacing*2.5, textColor, bgColor, CENTER_ALIGNMENT);

}

void drawAllInstructions(int bgColor)
{
    drawInstruction("COMPLETE",getInstructionChenar(0,0),bgColor);
    drawBoard(COMPLETE_CORRECT_LEVEL.brd);
    drawBoard(COMPLETE_INCORRECT_LEVEL.brd);

    drawInstruction("UNINTERRUPTED",getInstructionChenar(1,0),bgColor);
    drawBoard(UNINTERRUPTED_CORRECT_LEVEL.brd);
    drawBoard(UNINTERRUPTED_INCORRECT_LEVEL.brd);

    drawInstruction("A PIECE OF EACH TYPE",getInstructionChenar(0,1),bgColor);
    drawBoard(A_PIECE_OF_EACH_TYPE_CORRECT_LEVEL.brd);
    drawBoard(A_PIECE_OF_EACH_TYPE_INCORRECT_LEVEL.brd);


    drawInstruction("SAME FORM",getInstructionChenar(1,1),bgColor);
    drawBoard(SAME_FORM_CORRECT_LEVEL.brd);
    drawBoard(SAME_FORM_INCORRECT_LEVEL.brd);


    int xControlText = WINDOW_WIDTH/4+75;
    int yControlText = instructionsLevel.brd.chenar.top+50;
    int spacing = 50;
    drawText("CONTROLS",xControlText,yControlText,WHITE,bgColor,CENTER_ALIGNMENT);
    drawText("-left click to add or the extend a partition",xControlText,yControlText+spacing,WHITE,bgColor,CENTER_ALIGNMENT);
    drawText("-right click to remove cells from partition",xControlText,yControlText+2*spacing,WHITE,bgColor,CENTER_ALIGNMENT);
    drawText("TRY IT",xControlText,yControlText+3.5*spacing,getDarkerColor(bgColor,40),bgColor,CENTER_ALIGNMENT);

    drawBoard(instructionsLevel.brd);
}
