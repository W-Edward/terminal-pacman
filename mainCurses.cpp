#include <ncurses.h>
#include <string>
//#include <windows.h>
 #include <unistd.h> //,replace windows.h for linux
#include <stdio.h>
using namespace std;

//Notes:
//Compile with "g++ -pedantic-errors -std=c++11 mainCurses.cpp -lncurses -o mainCurses", any method of compilation is allowed for this project 
//Make sure terminal is big enough BEFORE starting the game
//DON'T ADJUST TERMINAL SIZE WHILE PLAYING GAME, IT WILL BREAK!

void display(int y,int x){

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
	    case 'q':
	    direction = 5;
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

    //Game Flow
    while (!quit) {
        for (int i = 0; i < 10; i++) { 
            display(y,x);
            input(direction);
            switch (direction) {
                case 1:
                    if (y > 1 && a[y-1][x]!="##") y--;
                    break;
                case 2:
                    if (x > 1 && a[y][x-1]!="##") x--;
                    break;
                case 3:
                    if (y < 13 && a[y+1][x]!="##") y++;
                    break;
                case 4:
                    if (x < 13 && a[y][x+1]!="##") x++;
                    break;
		case 5:
		    quit = true;
		    break;
            }
            usleep(150000); //use usleep(150000); in linux
        }
    }

    getch();
    endwin();

    return 0;
}