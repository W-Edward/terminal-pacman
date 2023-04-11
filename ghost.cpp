#include <string>
#include <curses.h>
#include <cmath>
#include "entities.h"
using namespace std;

//Notes:
//Ghost should never turn around unless when changing states

string tempa[19][20] = {
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
        int availableDirections[4] = {4, 3, 2, 1}; //According to the priority list for ghost movement! 

        double shortestDistance = 1e5;
        double distance = 0;
        int originalDirection = currentDirection;
        for (int i = 0; i < 4; i++)
        {
            int tempX = x, tempY = y;
            if (availableDirections[i] == 1 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[--tempY][tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 2 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][--tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 3 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[++tempY][tempX] != "##")
            {
                distance = sqrt( pow( (tempX-playerPosX) , 2 ) + pow( (tempY-playerPosY) , 2 )); //Linear Distance formula
                if (distance <= shortestDistance) 
                {
                    shortestDistance = distance;
                    currentDirection = availableDirections[i];
                }
            }
            else if (availableDirections[i] == 4 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][++tempX] != "##")
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

