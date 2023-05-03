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
        void escape();
        int getX();
        int getY();
        bool getFrightened();
    private:
        int x,y,currentDirection;
        string name;
        bool isFrightened; // flag for whether or not it is frightened
        int findOppositeDirection(int currentDir);
        void chaseTargetTile(int targetX, int targetY);
};