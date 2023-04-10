#include <curses.h>
#include <string>
#include <windows.h>
// #include <unistd.h> ,replace windows.h for linux
#include <stdio.h>
#include "entities.h"
using namespace std;

//Notes:
//Compile with "g++ -pedantic-errors -std=c++11 mainCurses.cpp ghost.cpp -lncurses -o mainCurses", any method of compilation is allowed for this project 
//Make sure terminal is big enough BEFORE starting the game
//DON'T ADJUST TERMINAL SIZE WHILE PLAYING GAME, IT WILL BREAK!

void display(int y,int x, Ghost Blinky){

    int xCursor = 0, yCursor = 0; //Placement of cursor in "stdscr" window

    string tempa[15][15] = {
    {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
    {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
    {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
    {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
    {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
    {"##","  ","##","##","  ","  ","  ","  ","  ","  ","  ","##","##","  ","##"},
    {"##","  ","  ","##","  ","##","  ","  ","  ","##","  ","  ","  ","  ","##"},
    {"##","##","##","##","  ","##","  ","  ","  ","##","  ","##","##","##","##"},
    {"##","  ","  ","  ","  ","##","  ","  ","  ","##","  ","##","  ","  ","##"},
    {"##","  ","##","##","  ","##","##","##","##","##","  ","##","##","  ","##"},
    {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
    {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
    {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
    {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
    {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}
    };

    tempa[y][x]="(<"; //Mr. Pac-Man xD
    tempa[Blinky.getY()][Blinky.getX()] = "[]"; //Mr.Blinky

    for (int i = 0; i < 14; i++) 
    {
            for (int j = 0; j < 15; j++) {
                    addch(tempa[i][j][0]);
                    addch(tempa[i][j][1]);
            }
            move(++yCursor, xCursor); //Moves the cursor position to a new line!
    }
    refresh(); //Print output to window "stdscr"
}

void input(int& direction){
    char ch = getch();
    switch(ch){
            case 'w':
            direction = 1;
            break;
            case 'a':
            direction = 2;
            break;
            case 's':
            direction = 3;
            break;
            case 'd':
            direction = 4;
            break;
    }
}



int main()
{
    //Screen Settings
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    //Game Startup
    int y=13;
    int x=2;
    int direction = 4;
    string a[15][15] = {
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
        {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","##","##","  ","  ","  ","  ","  ","  ","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","##","  ","  ","  ","##","  ","  ","  ","  ","##"},
        {"##","##","##","##","  ","##","  ","  ","  ","##","  ","##","##","##","##"},
        {"##","  ","  ","  ","  ","##","  ","  ","  ","##","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","##","##","##","##","##","  ","##","##","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
        {"##","  ","##","##","  ","##","  ","##","  ","##","  ","##","##","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}
    };
    bool quit = false;
    //Instantiate Ghosts here!
    Ghost Blinky(4, 5, "Blinky"); //Instantiates Blinky

    //Game Flow
    while (!quit) {
        for (int i; i < 10; i++)
        {
            display(y,x,Blinky);
            input(direction);
            //Updates Ghosts Positions
            //Updates Pac-Man's Position
            switch (direction) {
                case 1:
                    if (y > 1 && a[y-1][x]!="##") y--;
                    Blinky.chase(x, y);
                    break;
                case 2:
                    if (x > 1 && a[y][x-1]!="##") x--;
                    Blinky.chase(x, y);
                    break;
                case 3:
                    if (y < 13 && a[y+1][x]!="##") y++;
                    Blinky.chase(x, y);
                    break;
                case 4:
                    if (x < 13 && a[y][x+1]!="##") x++;
                    Blinky.chase(x, y);
                    break;
        }
        Sleep(150); //use usleep(150000); in linux
        }
    }
    

    getch();
    endwin();

    return 0;
}