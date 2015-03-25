/*
 *File: Life.cpp
 * Implements the Game of Life.
 *
 * There is a bacteria cell colony represented by 2-D grid,
 * each element of the grid is a cell, it can be either dead or alive.
 * Game goes on step-by-step, each step(tick) leads to a new
 * generation of colony. The state of each cell in the new
 * generation is computed by the following rules, applied
 * simultaneously every tick to all cells:
 * 1) If a living cell is surrounded by 1 or 0 living cells, it dies
 * 2) If a cell is surrounded by 2 living cells, it doesn't change its state
 * 3) If a cell is surrounded by 3 living cells, it becomes alive
 * 4) if a living cell is surrounded by 4 or more living cells, it dies
 *
 * The program reads an initial state of bacteria cells colony
 * from the text file specified by user,
 * computes next generations of the cell colony and prints it.
 * The program has a console-based text interface.
 * User may select either to step forward one generation(tick),
 * by pressing 't', or animate evolution of the cell colony
 * by pressing 'a'.
 *
 * Impemented by Galina Galimova
*/

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;


void ReadFile(istream&, Grid<char>&);
void PrintGrid(Grid<char>&);
char askForAction(void);
void tick(Grid<char>&);

int main() {
    setConsoleSize(700, 400);

    cout << "Welcome to Game of Life," << endl
         << "A simulation of the lifecycle of a bacteria colony." << endl
            << "Cells (X) live and die by the following rules:" << endl
               << "- A cell with 1 o fewer neighbors dies." << endl
                  << "- Locations with 2 neighbors remain stable." << endl
                     << "- Locations with 3 neighbors will create life." << endl
                        << "- A cell with 4 or more neighbors dies."  << endl << endl;

    Grid<char> currentGrid;
    ifstream fileStream;
    string fileName =  getLine("Grid input file name? ");

    openFile(fileStream, fileName);
    ReadFile(fileStream,  currentGrid);
    PrintGrid(currentGrid);

    while(true)
    {
        int frames = 1;
        switch (askForAction())
        {
            case 't':
             {
                tick(currentGrid);
                PrintGrid(currentGrid);
                break;
             }
            case 'a':
            {
                frames = stringToInteger(getLine("How many frames? "));
                for(int i = 0; i < frames; i++)
                {
                    clearConsole();
                    tick(currentGrid);
                    PrintGrid(currentGrid);
                    pause(100);
                 }
                break;
             }
            case 'q':
            {
                cout << "Have a nice Life!";
                return 0;
            }
        }
    }
}

//Reads file and fills in the grid
void ReadFile(istream& file, Grid<char>& grid)
{
    //Get dimentions of the grid from first two lines of file
    string line;
    getline(file, line);
    int rows = stringToInteger(line);
    getline(file, line);
    int columns = stringToInteger(line);

    //Resize grid to the given dimentions
    grid.resize(rows, columns);

    //Read a grid from file to grid
    for (int i = 0; i < rows; i++)
    {
        //read each row
        getline(file, line);

        //Read each char in row and write char to grid
        for (int k=0; k < columns; k++)
        {
             grid[i][k] = line[k];
        }

    }
}

//Prints grid
void PrintGrid(Grid<char>& grid)
{
    for (int i = 0; i < grid.numRows(); i++)
    {
        for (int k = 0; k < grid.numCols(); k++)
        {
                cout << grid[i][k];
        }
        cout << endl;
    }
}


//Asks user for action (tick, animate or quit)
char askForAction()
{
    string line = getLine("a)nimate, t)ick, q)uit? ");
    if(line.size() == 1)
        return line[0];
    else
        return 0;
}

//Ticks one frame
void tick(Grid<char>& grid)
{
    Grid<char> tmp(grid.numRows(),grid.numCols());

    for (int x = 0; x < grid.numRows(); x++)
    {
        for (int y = 0; y < grid.numCols(); y++)
        {
            int count = 0;
            for (int dx = -1; dx < 2; dx++)
                for (int dy = -1; dy < 2; dy++)
                     if ((grid.inBounds(x+dx,y+dy))&&(grid[x+dx][y+dy]=='X')&&(!((dx==dy)&&(dx==0))))
                     {
                         count++;
                     };
            if ((count < 2)||(count > 3))
                tmp[x][y] = '-';
            else
                if (count == 2)
                    tmp[x][y] = grid[x][y];
                else
                    if (count == 3)
                        tmp[x][y] = 'X';
        }

    }
   grid = tmp;
}
