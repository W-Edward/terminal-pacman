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

int Ghost::chaseTargetTile(int targetX, int targetY)
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
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 2 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][--tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 3 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[++tempY][tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 4 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][++tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
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

void Ghost::chase(int playerPosX, int playerPosY, int blinkyPosX, int blinkyPosY, int direction) 
/*playerPosX and Y are Pac-Man's X and Y Coordinates, direction is Pac-Man's current direction, blinkyPosX and blinkyPosY are x and y positions of Blinky.
This function updates x and y coordinates + currentDirection of ghosts in chase mode */
{
    //Implementation to update posX and posY every frame to chase Pac-Man

    if (name == "Blinky")
    //Blinky chases Pac-Man directly (linearly)
    {
        chaseTargetTile(playerPosX, playerPosY);
    }

    else if (name == "Pinky") 
    /*Pinky chases the tile that is 4 tiles in front of Pac-Man's direction (exception when Pac-Man is facing 'up', in that case pinky chases 4 tiles in front +
    4 tiles to the left of Pac-Man )*/
    {
        int target[2];

        //Pinky determines target tile here

        if (direction == 1)
        {
            target[0] = playerPosX - 4;
            target[1] = playerPosY + 4;
        }
        else if (direction == 2)
        {
            target[0] = playerPosX - 4;
            target[1] = playerPosY;
        }
        else if (direction == 3)
        {
            target[0] = playerPosX;
            target[1] = playerPosY - 4;
        }
        else if (direction == 4)
        {
            target[0] = playerPosX + 4;
            target[1] = playerPosY;
        }
        else //just in case there is undefined behaviour
        {
            target[0] = playerPosX;
            target[1] = playerPosY;
        }
        
        chaseTargetTile(target[0], target[1]);   
    }
    
    else if (name == "Inky")
    /*Inky chases the tile that is rotated 180 degrees from Blinky's tile position around
    Point A: tile that is 2 tiles ahead of Pac-Man except 'up' direction, which is 2 tiles ahead and 2 tiles left.
    Let's call Blinky's position Point B and target tile Point C.*/
    {
        int pointA[2];
        if (direction == 1)
        {
            pointA[0] = playerPosX - 2;
            pointA[1] = playerPosY + 2;
        }
        else if (direction == 2)
        {
            pointA[0] = playerPosX - 2;
            pointA[1] = playerPosY;
        }
        else if (direction == 3)
        {
            pointA[0] = playerPosX;
            pointA[1] = playerPosY - 2;
        }
        else if (direction == 4)
        {
            pointA[0] = playerPosX + 2;
            pointA[1] = playerPosY;
        }
        else //just in case there is undefined behaviour
        {
            pointA[0] = playerPosX;
            pointA[1] = playerPosY;
        }

        int pointC[2];
        //rotate point B around point A 180 degrees to get point C
        pointC[0] = -(blinkyPosX - pointA[0]) + pointA[0];
        pointC[1] = -(blinkyPosY - pointA[1]) + pointA[1];

        chaseTargetTile(pointC[0], pointC[1]);
    }
    else if (name == "Clyde")
    //Clyde behaves similarly to Blinky but if Clyde is 8 tiles or closer to Pac-Man, he will turn to scatter mode.
    {
        if (sqrt( pow( (x-playerPosX) , 2 ) + pow( (y-playerPosY) , 2 )) <= 8)
        {
            //algo for scatter mode (bottomleft)
            chaseTargetTile(0, 20);
        } 
        else
        {
            chaseTargetTile(playerPosX, playerPosY);
        }
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

