#include "Ships.h"

int Сoordinates::GetX()
{
	return x;
}

int Сoordinates::GetY()
{
	return y;
}

void Сoordinates::SetX(int x)
{
	this->x = x;
}

void Сoordinates::SetY(int y)
{
	this->y = y;
}
int OneShip::GetSizeShip()
{
	return Position.size();
}

void OneShip::SetCoord(int x, int y)
{
	Сoordinates coord;
	coord.SetX(x);
	coord.SetY(y);
	Position.push_back(coord);
}

int OneShip::GetX(int i)
{
	return Position[i].GetX();
}

int OneShip::GetY(int i)
{
	return Position[i].GetY();
}

void OneShip::PrintCoordShips()
{
	for (int i = 0; i < GetSizeShip(); i++)
	{
		cout << Position[i].GetX() << " " << Position[i].GetY() << endl;
	}
}

void OneShip::ClearShip()
{
    Position.clear();
}

void OneShip::ClearPosIdex(int i)
{
    Position.erase(Position.begin() + i);
}

bool Ships::FindCoord(int i, int x, int y)//не трогай заебал
{
    bool result = true;

    for (int k = 0; k < i; k++)
    {
        for (int j = 0; j < ships[k].GetSizeShip(); j++)
        {
            if (ships[k].GetX(j) == x && ships[k].GetY(j) == y)
            {
                result = false;
            }
        }
    }
    return result;
}

bool Ships::CheckShip(int i)//Не трогай оно работает
{
    if (ships[i].GetSizeShip() >= 1 && ships[i].GetSizeShip() <= 4) {
        switch (ships[i].GetSizeShip())
        {
        case 1:
            if (CheckType(ships[i].GetSizeShip()) > 4) {
                return false;
            }
            break;
        case 2:
            if (CheckType(ships[i].GetSizeShip()) > 3) {
                return false;
            }
            break;
        case 3:
            if (CheckType(ships[i].GetSizeShip()) > 2) {
                return false;
            }
            break;
        case 4:
            if (CheckType(ships[i].GetSizeShip()) > 1) {
                return false;
            }
            break;
        default:
            break;
        }
        
        for (int k = 0; k < ships[i].GetSizeShip(); k++) 
        {
            if (!FindCoord(i, ships[i].GetX(k), ships[i].GetY(k) - 1)) { return false; }
            if (!FindCoord(i, ships[i].GetX(k), ships[i].GetY(k) + 1)) { return false; }
            if (!FindCoord(i, ships[i].GetX(k) - 1, ships[i].GetY(k))) { return false; }
            if (!FindCoord(i, ships[i].GetX(k) + 1, ships[i].GetY(k))) { return false; }
            if (!FindCoord(i, ships[i].GetX(k) + 1, ships[i].GetY(k) + 1)) { return false; }
            if (!FindCoord(i, ships[i].GetX(k) - 1, ships[i].GetY(k) - 1)) { return false; };
            if (!FindCoord(i, ships[i].GetX(k) - 1, ships[i].GetY(k) + 1)) { return false; };
            if (!FindCoord(i, ships[i].GetX(k) + 1, ships[i].GetY(k) - 1)) { return false; };
        }
        if (ships[i].GetSizeShip() == 1) //Если корабль однопалубный,то он всегда правильный
            return true;
        else
        {
            if (ships[i].GetSizeShip() > 4 || ships[i].GetSizeShip() < 1) //Если корабль имеет более 4 палуб, то он не правильный
                return false;
            else //Если корабль не однопалубный и имеет не более 4 палуб
            {
                int tempX = 0;
                int tempY = 0;
                for (int k = 0; k < ships[i].GetSizeShip(); k++)//Проверка на горизонтальность/вертикальность
                {
                    if (ships[i].GetX(0) != ships[i].GetX(k)) tempX = 1;
                    if (ships[i].GetY(0) != ships[i].GetY(k)) tempY = 1;
                }

                if (tempX == 1 && tempY == 1)
                    return false;
                else if (tempX == 0) //Расположен вертикально. Проверка на разрывы по Y
                {
                    int minY = ships[i].GetY(0);
                    for (int k = 0; k < ships[i].GetSizeShip(); k++)
                        if (minY > ships[i].GetY(k)) minY = ships[i].GetY(k);//Поиск минимума

                    int counter = 1;
                    for (int j = 0; j < ships[i].GetSizeShip(); j++)
                    {
                        if (ships[i].GetY(j) == minY + 1)
                        {
                            minY++;
                            counter++;
                            j = -1;
                        }
                    }
                    if (counter == ships[i].GetSizeShip())
                        return true;
                    else
                        return false;
                }
                else if (tempY == 0) //Расположен горизонтально. Проверка на разрывы по X
                {
                    int minX = ships[i].GetX(0);
                    for (int k = 0; k < ships[i].GetSizeShip(); k++)
                        if (minX > ships[i].GetX(k)) minX = ships[i].GetX(k);//Поиск минимума

                    int counter = 1;
                    for (int j = 0; j < ships[i].GetSizeShip(); j++)
                    {
                        if (ships[i].GetX(j) == minX + 1)
                        {
                            minX++;
                            counter++;
                            j = -1;
                        }
                    }
                    if (counter == ships[i].GetSizeShip())
                        return true;
                    else
                        return false;
                }

            }
        }
    }
    else
    {
        return false;
    }
}

bool Ships::FindAround(int i, int x, int y)
{
    for (int k = 0; k < GetSizeShip(i); i++)
    {
        if (GetX(i, k) == x && GetY(i, k) == y) {
            return true;
        }
    }
    return false;
}

int Ships::FindPos(int x, int y)
{
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < ships[i].GetSizeShip(); k++)
        {
            if (ships[i].GetX(k) == x && ships[i].GetY(k) == y)
            {
                return i;
            }
        }
    }
    return -1;
}

void Ships::DeletePos(int x, int y)
{
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < ships[i].GetSizeShip(); k++)
        {
            if (ships[i].GetX(k) == x && ships[i].GetY(k) == y)
            {
                ships[i].ClearPosIdex(k);
            }
        }
    }
}

void Ships::RandomSetShip(int type, int num)
{
    int numtemp = num;
    int typetemp = type;
    int randnum;
    int Vect;
    int size;
    int randnumtemp;
    int x, y;

    randnum = AviablePos[rand() % AviablePos.size()];
    randnumtemp = randnum;

    Vect = rand() % 2;

    if (Vect == 0)
    {
        if (CheckVectRight(randnum, type) == true)
        {
            size = ShipsSize();

            while (!(typetemp == 0)) //Установка
            {
                x = randnumtemp % 10;
                y = randnumtemp / 10;
                SetCoord(size, x, y);

                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x - 1)), AviablePos.end());

                randnumtemp++;
                typetemp--;
            }
            num--;
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
        else if (CheckVectUp(randnum, type) == true) {
            size = ShipsSize();

            while (!(typetemp == 0)) //Установка
            {
                x = randnumtemp % 10;
                y = randnumtemp / 10;

                SetCoord(size, x, y);

                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x - 1)), AviablePos.end());

                randnumtemp = randnumtemp - 10;
                typetemp--;
            }
            num--;
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
        else
        {
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
    }

    if (Vect == 1)
    {
        if (CheckVectUp(randnum, type) == true)
        {
            size = ShipsSize();

            while (!(typetemp == 0)) //Установка
            {
                x = randnumtemp % 10;
                y = randnumtemp / 10;

                SetCoord(size, x, y);

                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x - 1)), AviablePos.end());

                randnumtemp = randnumtemp - 10;
                typetemp--;
            }
            num--;
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
        else if (CheckVectRight(randnum, type) == true) {
            size = ShipsSize();

            while (!(typetemp == 0)) //Установка
            {
                x = randnumtemp % 10;
                y = randnumtemp / 10;
                SetCoord(size, x, y);

                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + x), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), y * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x - 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y - 1) * 10 + (x + 1)), AviablePos.end());
                AviablePos.erase(std::remove(AviablePos.begin(), AviablePos.end(), (y + 1) * 10 + (x - 1)), AviablePos.end());

                randnumtemp++;
                typetemp--;
            }
            num--;
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
        else
        {
            if (!(num == 0))
            {
                RandomSetShip(type, num);
            }
        }
    }
}

bool Ships::FindRand(int num)
{
    for (int i = 0; i < AviablePos.size(); i++)
    {
        if(num == AviablePos[i]){
            return true;
        }
    }
    return false;
}

void Ships::RandomSet()
{
    //Oчистка расстановки
    for (int i = 0; i < 10; i++)
    {
        ClearShip(i);
    }

    //Очистка вектора допустимых координат
    AviablePos.clear();

    for (int i = 0; i < 100; i++)//Заполнение вектора допустимых координат
    {
        AviablePos.push_back(i);
    }

    //Генерация расстановки
    RandomSetShip(4, 1);
    RandomSetShip(3, 2);
    RandomSetShip(2, 3);
    RandomSetShip(1, 4);


}

bool Ships::CheckVectUp(int randnum, int type)
{
    int randtemp = randnum - 10;
    while (!(type - 1 == 0))
    {
        if (!(FindRand(randtemp))) 
        {
            return false;
        }
        
        randtemp = randtemp - 10;
        type--;
    }
    return true;
}

bool Ships::CheckVectRight(int randnum, int type)
{
    int randtemp = randnum + 1;

    if ((randnum / 10) == ((randnum + type - 1) / 10)) {
        while (!(type - 1 == 0))
        {
            if (!(FindRand(randtemp))) 
            {
                return false;
            }
            randtemp++;
            type--;
        }
        return true;
    }
    else {
        return false;
    }
    
}

int Ships::GetX(int i, int k)
{
    return ships[i].GetX(k);
}

int Ships::GetY(int i, int k)
{
    return ships[i].GetY(k);
}

void Ships::SetCoord(int i, int x, int y)
{
    if (FindCoord(i, x, y)) 
    {
        ships[i].SetCoord(x, y);
    }
    else {
        cout << "lox";
    }
}

void Ships::ClearPosition(int numship, int index)
{
    ships[numship].ClearPosIdex(index);
}

int Ships::GetSizeShip(int i)
{
    return ships[i].GetSizeShip();
}

int Ships::CheckType(int size)
{
    int result = 0;
    for (int i = 0; i < 10; i++) {
        if (size == ships[i].GetSizeShip()) 
        {
            result++;
        }
    }
    return result;
}

void Ships::Print()
{
    for (int i = 0; i < 10; i++) {
        cout << i << "-";
        ships[i].PrintCoordShips();
        cout << endl;
    }
}

void Ships::ClearShip(int i)
{
    ships[i].ClearShip();
}

int Ships::ShipsSize()
{
    for (int i = 0; i < 10; i++) {
        if (ships[i].GetSizeShip() == 0)
        {
            return i;
        }
    }
}