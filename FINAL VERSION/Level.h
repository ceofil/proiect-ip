#pragma once
#include "Board.h"
#include "BoardSolvingFunctions.h"
#include <string>
#include <fstream>

Board getEmptyBoard(int maxNumberOfPieces, int numberOfPieceTypes)
{
    return makeBoard(makeRect(MARGIN,MARGIN,MARGIN+BOARD_SCREEN_SIZE,MARGIN+BOARD_SCREEN_SIZE), WHITE, maxNumberOfPieces, numberOfPieceTypes);
}

struct Level
{
    Board brd;
    bool isSolved = false;
};

void LoadLevel(Level& lvl, std::string filename)
{
    int maxNumberOfPieces;
    int numberOfPieceTypes;
    std::ifstream file(filename.c_str());
    file >> maxNumberOfPieces >> numberOfPieceTypes;
    lvl.brd = getEmptyBoard(maxNumberOfPieces,numberOfPieceTypes);
    char c;
    //load each piece
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            file >> c;
            if(c!='*')
            {
                int pieceType = c - '0';
                PlacePiece(x,y,pieceType,lvl.brd, true);
            }
        }
    }

    //load partition state
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            file>>c;
            if(c!='*')
            {
                int partitionId = c - '0';
                _SetCellToPartition(x,y,partitionId,lvl.brd);
            }
        }
    }
    lvl.isSolved = isBoardSolved(lvl.brd);
    file.close();
}

void SaveLevel(Level& lvl, std::string filename)
{
    std::ofstream file(filename.c_str());

    file << lvl.brd.maxNumberOfPieces << " " << lvl.brd.numberOfPieceTypes << std::endl;

    //save each piece
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            const Cell& cell = cellAt(x,y,lvl.brd);
            if(cell.isHoldingPiece)
            {
                file<<cell.pieceType;
            }
            else
            {
                file<<'*';
            }
        }
        file<<std::endl;
    }
    file<<std::endl;

    //save partition state
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            const Cell& cell = cellAt(x,y,lvl.brd);
            if(cell.isInPartiton)
            {
                file<<cell.parititonId;
            }
            else
            {
                file<<'*';
            }
        }
        file<<std::endl;
    }
    file.close();
}


