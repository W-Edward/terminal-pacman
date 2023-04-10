#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <string>
//#include <windows.h>
#include <unistd.h> //,replace windows.h for linux
#include <stdio.h>
using namespace std;

//Notes:
//Compile with "g++ -pedantic-errors -std=c++11 mainCurses.cpp -lncurses -o mainCurses", any method of compilation is allowed for this project 
//Make sure terminal is big enough BEFORE starting the game
//DON'T ADJUST TERMINAL SIZE WHILE PLAYING GAME, IT WILL BREAK!

void display(int y,int x,int last_y,int last_x,int face, string map[15][15]){
    int xMax,yMax;
    int xCursor, yCursor; //Placement of cursor in "stdscr" window

    getmaxyx(stdscr,yMax,xMax);
    xCursor = (xMax/2)-15;
    yCursor = (yMax/2)-15;
    move(yCursor, xCursor);

    map[last_y][last_x] = "  ";//erase the old Pac-Man
    //Mr Pac Man XD
    if (face == 1) {
        map[y][x]="(<";
    } else {
        map[y][x]=">)";
    }

    attron(COLOR_PAIR(1));
    for (int i = 0; i < 15; i++) 
    {
            for (int j = 0; j < 15; j++) {
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
    string map[15][15] = {
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

    

    //Game Flow
    while (!quit) {
        display(y,x,last_y,last_x,face,map);
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
                if (y < 13 && map[y+1][x]!="##") y++;
                break;
            case 4:
                if (x < 13 && map[y][x+1]!="##") x++;
                face = 1;
                break;
            case 5:
                quit = true;
                break;
        }
        usleep(150000); //use usleep(150000); in linux
    }

    getch();
    endwin();

    return 0;
}
