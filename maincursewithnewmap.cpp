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

void display(int y,int x,int last_y,int last_x,int face, int direction, string map[19][20], Ghost &Blinky, Ghost &Pinky, Ghost &Inky, Ghost &Clyde){
    int xMax,yMax;
    int xCursor, yCursor; //Placement of cursor in "stdscr" window

    getmaxyx(stdscr,yMax,xMax);
    xCursor = (xMax/2)-20;
    yCursor = (yMax/2)-20;
    move(yCursor, xCursor);

    map[last_y][last_x] = "  ";//erase the old Pac-Man
    map[Blinky.getY()][Blinky.getX()] = "  "; //erase old Blinky
    map[Pinky.getY()][Pinky.getX()] = "  "; //erase old Pinky
    map[Inky.getY()][Inky.getX()] = "  "; //erase old Inky
    map[Clyde.getY()][Clyde.getX()] = "  "; //erase old Clyde
    map[8][9] = "==";
    map[8][10] = "==";
    
    //Update ghost positions here!
    Blinky.chase(x, y, Blinky.getX(), Blinky.getY(), direction); //Third and fourth arguments must be BLINKY!!!!!
    Pinky.chase(x, y, Blinky.getX(), Blinky.getY(), direction);
    Inky.chase(x, y, Blinky.getX(), Blinky.getY(), direction);
    Clyde.chase(x, y, Blinky.getX(), Blinky.getY(), direction);
    //Mr Pac Man XD
    if (face == 1) {
        map[y][x]="(<";
    } else {
        map[y][x]=">)";
    }
    map[Blinky.getY()][Blinky.getX()] = "[]"; //Mr.Blinky, he likes to squirt from behind.
    map[Pinky.getY()][Pinky.getX()] = "()"; //Ms.Pinky, she loves doing it from the front.
    map[Inky.getY()][Inky.getX()] = "{}"; //Mr.Inky, he is a third wheel helping out Blinky squirt.
    map[Clyde.getY()][Clyde.getX()] = "<>";//Mr.Clyde, the innocent one
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
    string map[19][20] = { //y max = 18, x max = 19
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","  ","##","##","##","  ","  ","  ","  ","  ","  ","  ","  ","##","##","##","  ","##","##"},
        {"  ","  ","  ","  ","  ","  ","  ","##","##","==","==","##","##","  ","  ","  ","  ","  ","  ","  "},
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
    Ghost Inky(1, 8, "Inky");
    Ghost Clyde(18, 17, "Clyde");

    
    //Game Flow
    while (!quit) {
        display(y,x,last_y,last_x,face,direction,map,Blinky, Pinky, Inky, Clyde);
        input(direction);
        last_y = y;
        last_x = x;
        switch (direction) {
            case 1:
                if (y > 1 && map[y-1][x]!="##") {y--;}
                break;
            case 2:
                if (x > 1 && map[y][x-1]!="##") {x--;}
                else if ( x <= 1 && y == 8) //used for Pac-Man Looping
                {
                    x--;
                    if (x == -1)
                    {
                        x = 19;
                    }
                } 
                face = 0;
                break;
            case 3:
                if (y < 17 && map[y+1][x]!="##" && map[y+1][x]!="==") {y++;}
                break;
            case 4:
                if (x < 18 && map[y][x+1]!="##") {x++;}
                else if (x >= 18 && y == 8) //used for Pac-Man Looping
                {
                    x++;
                    if (x == 20)
                    {
                        x = 0;
                    }
                } 
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