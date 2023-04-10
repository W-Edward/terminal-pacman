#include <string>
using namespace std;

class Ghost
{
    public:
        Ghost(int posX, int posY);
        void update(int playerPosX, int playerPosY);
        int getX();
        int getY();
    private:
        int x,y;
};