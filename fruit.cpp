#include <curses.h>
#include <cmath>
#include "entities.h"

Fruit::Fruit(int posX, int posY){
	x = posX;
	y = posY;
}

int Fruit::getX(){
	return x;
}

int Fruit::getY(){
	return y;
}

void Fruit::eaten(){
	currentState=3;
int Fruit::getCurrentState(){ //check if fruit is eaten
	return currentState;
}

int Fruit::getEaten(){
	//if (isEaten==true)
	//	score+=300;
	return currentState;
