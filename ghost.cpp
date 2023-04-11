#include <string>
#include <curses.h>
#include <cmath>
#include "entities.h"
using namespace std;

//Notes:
//Ghost should never turn around unless when changing states

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

int Ghost::findOppositeDirection(int currentDir)
{
    int direction = (currentDir+2)%4;
    if (direction == 0)
    {
        direction = 4;
    }
    return direction;
}

Ghost::Ghost(int posX, int posY, string ghostName)
{
    x = posX;
    y = posY;
    name = ghostName;
    currentDirection = 2; //1 is up, 2 is left, 3 is down and 4 is right
}

void Ghost::chase(int playerPosX, int playerPosY) //playerPosX and Y are Pac-Man's X and Y Coordinates, updates x and y coordinates + currentDirection of ghosts in chase mode
{
    //Implementation to update posX and posY every frame to chase Pac-Man
    if (name == "Blinky") //Blinky chases Pac-Man directly
    {
        int availableDirections[3];
        int direction = 4; //directions to be inputted into availableDirections, decreasing from 4 because the movement priority is up left down right

        for (int i = 0; i < 3; i++)
        {
            if (direction == findOppositeDirection(currentDirection))
            {
                --direction;
            }
            availableDirections[i] = direction;
            --direction;
        }       

        double shortestDistance = 1e5;
        double distance = 0;
        for (int i = 0; i < 3; i++)
        {
            int tempX = x, tempY = y;
            if (availableDirections[i] == 1 && tempa[--tempY][tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 2 && tempa[tempY][--tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 3 && tempa[++tempY][tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 4 && tempa[tempY][++tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
        }

        switch (currentDirection)
        {
            case 1:
                y--;
                break;
            case 2:
                x--;
                break;
            case 3:
                y++;
                break;
            case 4:
                x++;
                break;
        }
    }

    else if (name == "Pinky")
    {
        
    }
    else if (name == "Inky")
    {


    }
    else if (name == "Clyde")
    {
   
    }
}

int Ghost::getX()
{
    return x;
}

int Ghost::getY()
{
    return y;
}

