#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include "Menu.h"
#include <windows.h>
#include "CheckBox.h"
int main()
{

    initwindow(WINDOW_WIDTH,WINDOW_HEIGHT);

    load_levels();
    LoadInstructionBoards();
    LoadSettingsFromFile();

    SetMenuTo_FIRST_MENU();

    do
    {
        SetMouseState();
        HandleInput();
    }
    while (!gameOver);

    closegraph();
    return 0;
}
