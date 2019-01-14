#pragma once

#include <iostream>
#include <cassert>

#include "Board.h"

bool visitedBuffer_CELLS[BRD_SIZE][BRD_SIZE]; // to avoid recursive loop
bool visitedBuffer_PARTITIONS[BRD_SIZE]; // to check for continuity
bool hasPieceBuffer_PARTITIONS[BRD_SIZE][3];// to check if every partiton has a piece of each type


void resetVisitedBuffer()
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            visitedBuffer_CELLS[y][x] = false;
        }
        visitedBuffer_PARTITIONS[y] = false;
    }
}

void resetHasPieceBuffer()
{
    for(int i = 0; i< BRD_SIZE; i++)
    {
        for(int j = 0; j<3; j++)
        {
            hasPieceBuffer_PARTITIONS[i][j] = false;
        }
    }
}



bool isBoardSet(Board& brd)
{
    for(int i = 0; i<brd.numberOfPieceTypes; i++)
    {
        if(brd.currNumberOfPieces[i] != brd.maxNumberOfPartitions)
        {
            return false;
        }
    }
    return true;
}

bool isBoardComplete(Board& brd)
{
    for(int i = 0; i<brd.maxNumberOfPartitions; i++)
    {
        if(brd.partitionCounter[i]!=brd.maxPartitionLength)
        {
            return false;
        }
    }
    return true;
}

void visitNeighborhood(int x, int y, int previousCellPartition, Board& brd)
{
    if(validGridPos(x,y))
    {
        if(visitedBuffer_CELLS[y][x] == false)
        {
            Cell& cell = cellAt(x,y,brd);
            if(cell.isInPartiton && cell.parititonId == previousCellPartition)
            {
                visitedBuffer_PARTITIONS[cell.parititonId] = true;
                visitedBuffer_CELLS[y][x] = true;
                visitNeighborhood(x-1,y,cell.parititonId,brd);
                visitNeighborhood(x+1,y,cell.parititonId,brd);
                visitNeighborhood(x,y-1,cell.parititonId,brd);
                visitNeighborhood(x,y+1,cell.parititonId,brd);
            }
        }
    }
}




bool arePartitionsUninterrupted(Board& brd)
{
    resetVisitedBuffer();
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            Cell& cell = cellAt(x,y,brd);
            if(cell.isInPartiton)
            {
                if(visitedBuffer_PARTITIONS[cell.parititonId] && visitedBuffer_CELLS[y][x] == false)
                {
                    //if all the cells in the partition were uninterrupted this cell should have been visited already because the some other cell in the partition was visited
                    return false;
                }
                else
                {
                    visitNeighborhood(x,y,cell.parititonId,brd);
                }
            }
        }
    }
    return true;
}

bool _partitionHasPieceType(Board brd, int partititionId, int pieceType) //this function is used to display weather or not a partition contains a type of piece in RightInGameMenu.h
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            Cell& cell = cellAt(x,y,brd);
            if(cell.isInPartiton && cell.parititonId == partititionId && cell.isHoldingPiece && cell.pieceType == pieceType)
            {
                return true;
            }
        }
    }
    return false;
}

bool eachPartitionHasEveryTypeOfPiece(Board& brd)
{
    resetHasPieceBuffer();
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            Cell& cell = cellAt(x,y,brd);
            if(cell.isInPartiton && cell.isHoldingPiece)
            {
                hasPieceBuffer_PARTITIONS[cell.parititonId][cell.pieceType] = true;
            }
        }
    }

    for(int i = 0; i < brd.maxNumberOfPartitions; i++)
    {
        for(int j = 0; j< brd.numberOfPieceTypes; j++)
        {
            if(hasPieceBuffer_PARTITIONS[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}



/* - - - - - - - - - - -data and functions for solving the 4-partition; same form board- - - - - - - - - - - - - -- - - */

struct PartitionMatrix
{
    bool data[BRD_SIZE][BRD_SIZE];
};

PartitionMatrix makePartitionMatrix(Board& brd, int partitionId)
{
    PartitionMatrix matrix;
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x< BRD_SIZE; x++)
        {
            Cell cell = cellAt(x,y,brd);
            if(cell.isInPartiton && cell.parititonId == partitionId)
            {
                matrix.data[y][x] = true;
            }
            else
            {
                matrix.data[y][x] = false;
            }
        }
    }
    return matrix;
}

PartitionMatrix getReflected(PartitionMatrix matrix)
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x< BRD_SIZE/2; x++)
        {
            std::swap(matrix.data[y][x],matrix.data[y][BRD_SIZE-1-x]);
        }
    }
    return matrix;
}

PartitionMatrix getRotatedClockWise(PartitionMatrix matrix)
{
    PartitionMatrix rotated;
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            rotated.data[x][BRD_SIZE-1-y] = matrix.data[y][x];
        }
    }
    return rotated;
}

PartitionMatrix getTranslatedToTopLeft(PartitionMatrix matrix)
{
    int yOffset = -1;
    for(int y = 0; y < BRD_SIZE && yOffset == -1; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            if(matrix.data[y][x])
            {
                yOffset = y;
                break;
            }
        }
    }

    int xOffset = -1;
    for(int x = 0; x < BRD_SIZE && xOffset == -1; x++)
    {
        for(int y = 0; y < BRD_SIZE; y++)
        {
            if(matrix.data[y][x])
            {
                xOffset = x;
                break;
            }
        }
    }

    if(xOffset == -1)
    {
        return matrix;
    }

    if(xOffset > 0 || yOffset > 0 )
    {
        for(int y = 0; y < BRD_SIZE; y++)
        {
            for(int x = 0; x < BRD_SIZE; x++)
            {
                if(matrix.data[y][x])
                {
                    matrix.data[y-yOffset][x-xOffset] = matrix.data[y][x];
                    matrix.data[y][x] = false;
                }
            }
        }
    }

    return matrix;
}

bool twoPartitionsAreEqual(PartitionMatrix first, PartitionMatrix second)
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x < BRD_SIZE; x++)
        {
            if(first.data[y][x] != second.data[y][x])
            {
                return false;
            }
        }
    }
    return true;
}

bool twoPartitionsHaveTheSameForm(Board& brd, int part1, int part2)
{
    PartitionMatrix first = makePartitionMatrix(brd, part1);
    PartitionMatrix second = makePartitionMatrix(brd, part2);
    first = getTranslatedToTopLeft(first);

    for(int i = 0; i < 4; i++)
    {
        second = getTranslatedToTopLeft(second);
        if(twoPartitionsAreEqual(first,second))
        {
            return true;
        }
        second = getRotatedClockWise(second);
    }

    second = getReflected(second);
    for(int i = 0; i < 4; i++)
    {
        second = getTranslatedToTopLeft(second);
        if(twoPartitionsAreEqual(first,second))
        {
            return true;
        }
        second = getRotatedClockWise(second);
    }

    return false;
}

bool AllPartitionsHaveTheSameForm(Board& brd)
{
    for(int i = 1; i < brd.maxNumberOfPartitions; i++)
    {
        if(twoPartitionsHaveTheSameForm(brd,0,i) == false)
        {
            return false;
        }
    }
    return true;
}

void displayPartitionMatrix(PartitionMatrix matrix)
{
    for(int y = 0; y < BRD_SIZE; y++)
    {
        for(int x = 0; x< BRD_SIZE; x++)
        {
            if(matrix.data[y][x])
            {
                std::cout<<1;
            }
            else
            {
                std::cout<<'*';
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}





bool isBoardSolved(Board& brd)
{
    if(brd.maxNumberOfPartitions == 4)
    {
        return AllPartitionsHaveTheSameForm(brd) && isBoardSet(brd) && isBoardComplete(brd) && arePartitionsUninterrupted(brd) && eachPartitionHasEveryTypeOfPiece(brd);
    }
    return isBoardSet(brd) && isBoardComplete(brd) && arePartitionsUninterrupted(brd) && eachPartitionHasEveryTypeOfPiece(brd);
}
