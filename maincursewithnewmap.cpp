#include <iostream>
// #include <ncurses.h>
#include <curses.h>
#include <string>
#include <unistd.h>
#include <windows.h>
// #include <unistd.h> //,replace windows.h for linux
#include <stdio.h>
#include "entities.h"
using namespace std;

//Notes:
//Compile with "g++ -pedantic-errors -std=c++11 maincursewithnewmap.cpp ghost.cpp -lncurses -o mainCurses", any method of compilation is allowed for this project 
//Make sure terminal is big enough BEFORE starting the game
//DON'T ADJUST TERMINAL SIZE WHILE PLAYING GAME, IT WILL BREAK!

void display(int y,int x,int last_y,int last_x,int face, int direction, string map[19][20], Ghost &Blinky, Ghost &Pinky){
    int xMax,yMax;
    int xCursor, yCursor; //Placement of cursor in "stdscr" window

    getmaxyx(stdscr,yMax,xMax);
    xCursor = (xMax/2)-20;
    yCursor = (yMax/2)-20;
    move(yCursor, xCursor);

    map[last_y][last_x] = "  ";//erase the old Pac-Man
    map[Blinky.getY()][Blinky.getX()] = "  "; //erase old Blinky
    map[Pinky.getY()][Pinky.getX()] = "  "; //erase old Pinky

    //Update ghost positions here!
    Blinky.chase(x, y, direction);
    Pinky.chase(x, y, direction);
    //Mr Pac Man XD
    if (face == 1) {
        map[y][x]="(<";
    } else {
        map[y][x]=">)";
    }
    map[Blinky.getY()][Blinky.getX()] = "[]"; //Mr.Blinky
    map[Pinky.getY()][Pinky.getX()] = "()"; //Ms.Pinky
    attron(COLOR_PAIR(1));

    for (int i = 0; i < 19; i++) 
    {
            for (int j = 0; j < 20; j++) {
                    if (i == y && j == x) {
                        attron(COLOR_PAIR(2));
                        addch(map[i][j][0]);
                        addch(map[i][j][1]);
                        attron(COLOR_PAIR(1));
                    } else {
                        addch(map[i][j][0]);
                        addch(map[i][j][1]);
                    }
                    
            }
            move(++yCursor, xCursor); //Moves the cursor position to a new line!
    }
    attroff(COLOR_PAIR(1));
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
            case 'q':
            direction = 5;
            break;
    }
}



int main()
{
    //Screen Settings
    initscr();
    start_color();
    if(can_change_color()) {
        init_color(COLOR_BLACK,0,0,0);
        init_color(COLOR_CYAN,0,0,888);
    }
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    //Game Startup
    int y=13;
    int x=2;
    int last_y = 13;
    int last_x = 2;
    int direction = 4;
    int face = 1;
    string map[19][20] = {
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","  ","##","##","##","  ","  ","  ","  ","  ","  ","  ","  ","##","##","##","  ","##","##"},
        {"##","  ","  ","  ","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","##","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","##","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","##","  ","##","  ","  ","##","##","##","##","##","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","  ","##","  ","##","##","  ","##","##","##","##","  ","##","##","  ","##","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","  ","##","##","##","  ","  ","##","##","##","  ","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","  ","##","##","##","  ","  ","##","##","##","  ","  ","##","  ","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}
    };
    bool quit = false;
    //Instantiate Ghosts here!
    Ghost Blinky(4, 5, "Blinky"); //x = 4, y =5
    Ghost Pinky(18, 6, "Pinky");

    
    //Game Flow
    while (!quit) {
        display(y,x,last_y,last_x,face,direction,map,Blinky, Pinky);
        input(direction);
        last_y = y;
        last_x = x;
        switch (direction) {
            case 1:
                if (y > 1 && map[y-1][x]!="##") y--;
                break;
            case 2:
                if (x > 1 && map[y][x-1]!="##") x--;
                face = 0;
                break;
            case 3:
                if (y < 17 && map[y+1][x]!="##") y++;
                break;
            case 4:
                if (x < 18 && map[y][x+1]!="##") x++;
                face = 1;
                break;
            case 5:
                quit = true;
                break;
        }
        Sleep(250); //use usleep(150000); in linux
    }

    getch();
    endwin();

    return 0;
}