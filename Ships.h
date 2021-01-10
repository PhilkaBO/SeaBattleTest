#pragma once
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Сoordinates
{
private:
    int x;
    int y;
public:
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
};
class OneShip
{
private:
    vector <Сoordinates> Position;
public:
    int GetSizeShip();
    void SetCoord(int x, int y);
    int GetX(int i);
    int GetY(int i);
    void PrintCoordShips();
    void ClearShip();
    void ClearPosIdex(int i);

};
class Ships
{
    private:
    OneShip ships[10];
    vector <int> AviablePos;
public:
    bool FindCoord(int i, int x, int y);
    void SetCoord(int i, int x, int y);
    bool CheckShip(int i);
    bool FindAround(int i, int x, int y);

    int FindPos(int x, int y);
    void DeletePos(int x, int y);


    void RandomSet();
private:
    void RandomSetShip(int type, int num);
    bool FindRand(int num);
    bool CheckVectRight(int randnum, int type);
    bool CheckVectUp(int randnum, int type);
public:
    int ShipsSize();
    void ClearShip(int i);
    void Print();
    int CheckType(int size);
    int GetSizeShip(int i);
    int GetX(int i, int k);
    int GetY(int i, int k);
    void ClearPosition(int numship, int index);
    void SetCoord(int i, int x, int y);
};