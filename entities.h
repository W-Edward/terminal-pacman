#include <string>
using namespace std;

class Ghost
{
    public:
        Ghost(int posX, int posY, string ghostName);
        void chase(int playerPosX, int playerPosY, int blinkyPosX, int blinkyPosY, int direction);
        void scatter();
        void frightened();
        void eaten();
        void escape();
        int getX();
        int getY();
    private:
        int x,y,currentDirection;
        string name;
        int findOppositeDirection(int currentDir);
        int chaseTargetTile(int targetX, int targetY);
};