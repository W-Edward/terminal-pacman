#include <string>
using namespace std;

class Ghost
{
    public:
        Ghost(int posX, int posY, string ghostName);
        void chase(int playerPosX, int playerPosY);
        void scatter();
        void frightened();
        void eaten();
        int getX();
        int getY();
    private:
        int x,y,currentDirection;
        string name;
        int findOppositeDirection(int currentDir);
};