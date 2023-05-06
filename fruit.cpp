#include <curses.h>
#include <cmath>
#include "entities.h"

Fruit::Fruit(int posX, int posY, bool big){
	x = posX;
	y = posY;
	eatenState = 0;
}

int Fruit::getX(){
	return x;
}

int Fruit::getY(){
	return y;
}

void Fruit::eaten(){
	eatenState = 1;
}

int Fruit::getCurrentState(){ //check if fruit is eaten
	return eatenState;
}