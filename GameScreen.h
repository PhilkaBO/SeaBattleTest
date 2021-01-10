#include "Ships.h"

using namespace sf;

class GameScreen
{
	bool IsOpen = 1;
	int MyField[10][10];
	int EnemyField[10][10];
	int FlagMark[10][10];

	vector <int> AvPos;
	vector <int> AvVec;

	int ModeII = -1;
	int lasthit = -1;
	int direct = -1;
	int SizeModeII = -1;

public:

	int GameDraw(RenderWindow& window, Ships& myShip, Ships& enemyShips, int Mode);
	void IsKill(int x, int y, Ships& Ship);

	int II(Ships& myShip);
	void DeleteVec(vector<int>&, int value);
	void RenewAvVec();
	int ChVect(int);
	bool FindVector(vector<int>&, int value);
	void ClearAround(int index, Ships& myShip);
};
