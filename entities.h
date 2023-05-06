#include <string>
using namespace std;

class Ghost
{
    public:
        Ghost(int posX, int posY, string ghostName);
        void chase(int playerPosX, int playerPosY, int blinkyPosX, int blinkyPosY, int direction);
        void scatter();
        void frightened(); // instigates frightened state
        void eaten();
        int getX();
        int getY();
        int getLastX();
        int getLastY();
        void setPotentialState(int state);
        int getPotentialState();
        int getCurrentState();
        void setCurrentState(int i);
        void toggleCurrentDirection();
        int getEaten(); // proposed scoring func
    private:
        int x, y, last_x, last_y, currentDirection, currentState, potentialState;
        string name;
        int findOppositeDirection(int currentDir);
        void updateLastPosition();
        void chaseTargetTile(int targetX, int targetY);
};

class Pacman
{
    public:
        Pacman(int posX, int posY);
        int getFaceDirection();
        int getX();
        int getY();
        int getLastX();
        int getLastY();
        void updatePosition(int posX, int posY);
        void toggleFaceDirection(); // chances faceDirection
    private:
        int x, y, last_x, last_y, faceDirection; // faceDirection is the direction the face of pacman is facing (i.e. 0 for left, 1 for right)
};

class PrintASCII 
{
    public:
        void txtprint(int deviationFromMidX, int deviationFromMidY, string filename);
    private:
        int pictureHeight(string filename);
        int pictureWidth(string filename);
};

class Fruit
{
	public:
		Fruit(int posX, int posY);
		int getX();
		int getY();
		void eaten();
		int getCurrentState(); //Check if fruit is eaten
		int getEaten();
	private:
		int x, y, currentState;
};
