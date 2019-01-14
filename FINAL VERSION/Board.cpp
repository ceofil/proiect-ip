
#include "Board.h"


void initBoard(Board& brd, Rect chenar, int color, int maxNumberOfPartitions)
{
    //nu e neaparat sa fie asa dar daca nu sunt egale trebuie ca in loc de celllSize sa avem cellWidth si cellHeight
    //in plus, ar arata inestetic
    assert(chenar.width == chenar.height);

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
            brd.cells[y][x].color = color;
        }
    }
    brd.color = color;

    assert(maxNumberOfPartitions <= BRD_SIZE);

    brd.maxNumberOfPartitions = maxNumberOfPartitions;
    for(int i = 0; i< BRD_SIZE; i++)
    {
        brd.partitionCounter[i] = 0;
    }
}

