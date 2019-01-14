#pragma once

#include <iostream>
#include <cassert>

#include "graphics.h"
#include "Geometrie.h"
#include "Rect.h"
#include "Vec2.h"
#include "Colors.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 800
#define BOARD_TO_WINDOW_RATIO 0.65

//don't change these
#define BOARD_SCREEN_SIZE std::min(WINDOW_WIDTH,WINDOW_HEIGHT)*BOARD_TO_WINDOW_RATIO
#define MARGIN (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) - BOARD_SCREEN_SIZE) / 2

#define BRD_SIZE 8

struct Cell
{
    Rect chenar;
    bool isInPartiton = false;
    int parititonId;

    bool isHoldingPiece = false;
    int pieceType;
};

struct Board
{
    Rect chenar;
    Cell cells[BRD_SIZE][BRD_SIZE];
    int cellSize;
    int color;
    int strokeColor = COLOR(50,50,50);
    int strokeThickness;

    int selectedPartition;
    bool partitionIsSelected = false;

    int partitionCounter[BRD_SIZE];

    int maxNumberOfPieces;
    int currNumberOfPieces[3];
    int numberOfPieceTypes;
    int maxPartitionLength;
    int maxNumberOfPartitions;
};




bool validGridPos(int x, int y)
{
    return x >= 0 && x < BRD_SIZE && y >= 0 && y < BRD_SIZE;
}

void setChenar(Rect chenar, Board& brd)
{
    //este posibil ca latura chenarului sa nu fie divizibila cu BRD_SIZE si in acest caz este necesara trunchierea acestuia
    brd.cellSize = chenar.width / BRD_SIZE;
    brd.chenar = makeRect(chenar.left, chenar.top, chenar.left + brd.cellSize*BRD_SIZE, chenar.top + brd.cellSize*BRD_SIZE);

    for(int y = 0; y < BRD_SIZE; y++)
    {
        int cellTop = brd.chenar.top + y * brd.cellSize;
        for(int x = 0; x < BRD_SIZE; x++)
        {
            int cellLeft = brd.chenar.left + x * brd.cellSize;
            brd.cells[y][x].chenar = makeRect(cellLeft, cellTop, cellLeft + brd.cellSize, cellTop + brd.cellSize);
        }
    }
    brd.strokeThickness = std::max(1,chenar.width/256);
}

void initBoard(Board& brd, Rect chenar, int color, int maxNumberOfPieces, int numberOfPieceTypes)
{
    //nu e neaparat sa fie asa dar daca nu sunt egale trebuie ca in loc de celllSize sa avem cellWidth si cellHeight
    //in plus, ar arata inestetic
    assert(chenar.width == chenar.height);
    brd.color = color;
    brd.maxNumberOfPartitions = maxNumberOfPieces;
    brd.maxNumberOfPieces = maxNumberOfPieces; //TO DO: AVOID USING TWO VARIABLES FOR THE SAME THING
    brd.maxPartitionLength = BRD_SIZE*BRD_SIZE / maxNumberOfPieces;
    brd.numberOfPieceTypes = numberOfPieceTypes;

    setChenar(chenar, brd);


    for(int i = 0; i< BRD_SIZE; i++)
    {
        brd.partitionCounter[i] = 0;
    }
    for(int i = 0; i<3; i++)
    {
        brd.currNumberOfPieces[i] = 0;
    }
}
Board makeBoard(Rect chenar, int color, int maxNumberOfPieces, int numberOfPieceTypes)
{
    Board brd;
    initBoard(brd, chenar, color, maxNumberOfPieces, numberOfPieceTypes);
    return brd;
}



Vec2 cursorToGridPos(Vec2 cursor, const Board& brd)
{
    assert(isPointInsideRect(cursor,brd.chenar));
    int xGrid = (cursor.x - brd.chenar.left) / brd.cellSize;
    int yGrid = (cursor.y - brd.chenar.top) / brd.cellSize;
    return makeVec2(xGrid,yGrid);
}

Cell& cellAt(int x, int y, Board& brd)
{
    assert(x >= 0 && x < BRD_SIZE && y >= 0 && y < BRD_SIZE);
    return brd.cells[y][x];
}

Cell& cellAt(Vec2 gridPos, Board& brd)
{
    return cellAt(gridPos.x,gridPos.y,brd);
}

Cell& cellAtCursor(Vec2 cursor, Board& brd)
{
    return cellAt(cursorToGridPos(cursor,brd), brd);
}


void DrawCellStroke_TOP(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left-thickness,r.top-thickness,r.right+thickness,r.top+thickness,color);
}

void DrawCellStroke_BOTTOM(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left-thickness,r.bottom-thickness,r.right+thickness,r.bottom+thickness,color);
}

void DrawCellStroke_LEFT(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left-thickness,r.top-thickness,r.left+thickness,r.bottom+thickness,color);
}

void DrawCellStroke_RIGHT(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.right-thickness,r.top-thickness,r.right+thickness,r.bottom+thickness,color);
}


void DrawCellStroke_TOP__(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left+thickness,r.top-thickness,r.right-thickness,r.top+thickness,color);
}

void DrawCellStroke_BOTTOM__(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left+thickness,r.bottom-thickness,r.right-thickness,r.bottom+thickness,color);
}

void DrawCellStroke_LEFT__(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.left-thickness,r.top+thickness,r.left+thickness,r.bottom-thickness,color);
}

void DrawCellStroke_RIGHT__(int x, int y, int thickness, int color, Board& brd)
{
    Rect r = cellAt(x,y,brd).chenar;
    drawFilledRect(r.right-thickness,r.top+thickness,r.right+thickness,r.bottom-thickness,color);
}

void DrawStroke(Board& brd)
{
    for(int x = 0; x<BRD_SIZE; x++)
    {
        DrawCellStroke_TOP(x,0,brd.strokeThickness,brd.strokeColor,brd);
    }
    for(int y = 0; y<BRD_SIZE; y++)
    {
        DrawCellStroke_LEFT(0,y,brd.strokeThickness,brd.strokeColor,brd);
    }
}

void drawPiece(int pieceType, int xScreen, int yScreen, float radius)
{
    assert( pieceType <3 );
    drawFilledCircle(xScreen, yScreen, radius, BLACK);
    drawFilledCircle(xScreen, yScreen, radius*0.95f, WHITE);
    drawFilledCircle(xScreen, yScreen, radius*0.75f, BLACK);
    drawFilledCircle(xScreen, yScreen, radius*0.7f, PIECE_COLORS[pieceType]);
}

int getCellColor(const Cell& cell)
{
    if(cell.isInPartiton)
    {
        return PARTITION_COLORS[cell.parititonId];
    }
    return WHITE;
}

void drawCellFill(const Cell& cell)
{
    drawFilledRect( cell.chenar, getCellColor(cell) );
    if(cell.isHoldingPiece)
    {
        drawFilledCircle(cell.chenar.xcenter,cell.chenar.ycenter,cell.chenar.width/4,PIECE_COLORS[cell.pieceType]);
        drawPiece(cell.pieceType, cell.chenar.xcenter,cell.chenar.ycenter,cell.chenar.width/4);
    }
}

bool cellsAreInTheSamePartition(const Cell& a, const Cell& b)
{
    if(a.isInPartiton == b.isInPartiton)
    {
        if(a.isInPartiton == false)
        {
            return true;
        }
        return a.parititonId == b.parititonId;
    }
    return false;
}


void DrawBoardStroke_TOPLEFT(Board& brd)
{
    for(int x = 0; x < BRD_SIZE; x++)
    {
        DrawCellStroke_TOP(x,0,brd.strokeThickness,brd.strokeColor,brd);
    }
    for(int y = 0; y < BRD_SIZE; y++)
    {
        DrawCellStroke_LEFT(0,y,brd.strokeThickness,brd.strokeColor,brd);
    }
}
void drawCell(int x, int y, Board& brd)
{
    assert(validGridPos(x,y));
    drawCellFill(cellAt(x,y,brd));
    Cell& cellToDraw = cellAt(x,y,brd);
    if(validGridPos(x-1,y) && cellsAreInTheSamePartition(cellToDraw,cellAt(x-1,y,brd)))
    {
        DrawCellStroke_LEFT__(x,y,brd.strokeThickness,getDarkerColor(getCellColor(cellToDraw)),brd);
    }
    else
    {
        DrawCellStroke_LEFT(x,y,brd.strokeThickness,brd.strokeColor,brd);
    }

    if(validGridPos(x+1,y) && cellsAreInTheSamePartition(cellToDraw,cellAt(x+1,y,brd)))
    {
        DrawCellStroke_RIGHT__(x,y,brd.strokeThickness,getDarkerColor(getCellColor(cellToDraw)),brd);
    }
    else
    {
        DrawCellStroke_RIGHT(x,y,brd.strokeThickness,brd.strokeColor,brd);
    }

    if(validGridPos(x,y-1) && cellsAreInTheSamePartition(cellToDraw,cellAt(x,y-1,brd)))
    {
        DrawCellStroke_TOP__(x,y,brd.strokeThickness,getDarkerColor(getCellColor(cellToDraw)),brd);
    }
    else
    {
        DrawCellStroke_TOP(x,y,brd.strokeThickness,brd.strokeColor,brd);
    }

    if(validGridPos(x,y+1) && cellsAreInTheSamePartition(cellToDraw,cellAt(x,y+1,brd)))
    {
        DrawCellStroke_BOTTOM__(x,y,brd.strokeThickness,getDarkerColor(getCellColor(cellToDraw)),brd);
    }
    else
    {
        DrawCellStroke_BOTTOM(x,y,brd.strokeThickness,brd.strokeColor,brd);
    }

}

void drawBoard(Board& brd)
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            drawCell(x,y,brd);
        }
    }
}


void redrawNeighborhood(int x, int y, Board& brd)
{
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(validGridPos(x+j,y+i))
            {
                drawCell(x+j,y+i,brd);
            }
        }
    }
}


void PlacePiece(int x, int y, int pieceType, Board& brd, bool dontRedraw = false)
{
    assert(pieceType < brd.numberOfPieceTypes);
    Cell& cell = cellAt(x,y,brd);
    if(cell.isHoldingPiece == false && brd.currNumberOfPieces[pieceType]<brd.maxNumberOfPieces)
    {
        cell.isHoldingPiece = true;
        cell.pieceType = pieceType;
        brd.currNumberOfPieces[pieceType]++;
        if(dontRedraw == false)
        {
            redrawNeighborhood(x,y,brd);
        }
    }
}

void RemovePiece(int x, int y, Board& brd, bool dontRedraw = false)
{
    Cell& cell = cellAt(x,y,brd);
    if(cell.isHoldingPiece == true)
    {
        brd.currNumberOfPieces[cell.pieceType]--;
        cell.isHoldingPiece = false;
        if(dontRedraw == false)
        {
            redrawNeighborhood(x,y,brd);
        }
    }
}

int firstUnoccupiedPartition(const Board& brd)
{
    for(int i = 0; i < brd.maxNumberOfPartitions; i++)
    {
        if(brd.partitionCounter[i] == 0)
        {
            return i;
        }
    }
    return -1;
}



bool removeCellFromPartition(Vec2 cursor, Board& brd, bool dontRedraw = false)
{
    assert(isPointInsideRect(cursor,brd.chenar));

    Cell& cell = cellAtCursor(cursor, brd);
    if(cell.isInPartiton)
    {
        cell.isInPartiton = false;
        brd.partitionCounter[cell.parititonId]--;
        Vec2 gridPos = cursorToGridPos(cursor,brd);
        if(dontRedraw == false)
        {
            redrawNeighborhood(gridPos.x,gridPos.y,brd);
        }
        return true;
    }
    return false;
}

bool setCellToPartition(Vec2 cursor, Board& brd, bool dontRedraw = false)
{
    assert(isPointInsideRect(cursor,brd.chenar));

    Cell& cell = cellAtCursor(cursor, brd);
    if(cell.isInPartiton == false || brd.selectedPartition != cell.parititonId) //
    {
        if(brd.partitionIsSelected && brd.partitionCounter[brd.selectedPartition] < brd.maxPartitionLength)
        {
            removeCellFromPartition(cursor, brd, true);

            cell.isInPartiton = true;
            cell.parititonId = brd.selectedPartition;
            brd.partitionCounter[cell.parititonId]++;


            Vec2 gridPos = cursorToGridPos(cursor,brd);
            if(dontRedraw == false)
            {
                redrawNeighborhood(gridPos.x,gridPos.y,brd);
            }
            return true;
        }
    }
    return false;
}

void setSelectedPartition(Vec2 cursor, Board& brd)
{
    assert(brd.partitionIsSelected == false);
    assert(isPointInsideRect(cursor,brd.chenar));


    //check to see if the selected cell aldready has a partition
    //if it does we ll set the selected part. equal to this one
    Cell& cell = cellAtCursor(cursor, brd);
    if(cell.isInPartiton)
    {
        brd.selectedPartition = cell.parititonId;
        brd.partitionIsSelected = true;
    }
    else
    {
        int freePart = firstUnoccupiedPartition(brd);
        if(freePart != -1)
        {
            brd.selectedPartition = freePart;
            brd.partitionIsSelected = true;
        }
        else
        {
            //TO DO: let the user know why nothing is happening
        }
    }
}

void _SetCellToPartition(int x, int y, int partitionId, Board& brd) //ONLY USE WHEN LOADING FROM FILE; DONT USE IN PLAY MODE
{
    assert(validGridPos(x,y));
    assert(partitionId < BRD_SIZE);

    brd.partitionIsSelected = true;
    brd.selectedPartition = partitionId;

    //this is kinda shady and should not be done
    //the correct thing to do was to make overloads for setCellToPartition take x,y or grid pos
    //and call them here and also make cursor version call one of them but this header is already too long
    Vec2 not_an_acutal_cursor = getCenter(cellAt(x,y,brd).chenar);
    setCellToPartition(not_an_acutal_cursor,brd,true);

    brd.partitionIsSelected = false;
}
