#include "GameScreen.h"

int GameScreen::GameDraw(RenderWindow& window, Ships& myShips, Ships& enemyShips, int Mode)
{
    //Загрузка необходимых файлов
    Texture TexGameScreen;
    Texture TexShip;
    Texture TexMiss;
    Texture TexHit;
    Texture TexFlag;
    Texture TexMenuOff;
    Texture TexMenuOn;

    TexGameScreen.loadFromFile("images/Game/GameScreen.png");
    TexShip.loadFromFile("images/Game/Ship.png");
    TexMiss.loadFromFile("images/Game/Miss.png");
    TexHit.loadFromFile("images/Game/Hit.png");
    TexFlag.loadFromFile("images/Game/Flag.png");
    TexMenuOff.loadFromFile("images/Game/MenuOff.png");
    TexMenuOn.loadFromFile("images/Game/MenuOn.png");

    Sprite Hit(TexHit);
    Sprite Ship(TexShip);
    Sprite GameScreen(TexGameScreen);
    Sprite Miss(TexMiss);
    Sprite Flag(TexFlag);
    Sprite MenuOff(TexMenuOff);

    MenuOff.setPosition(50, 500);

    //Загружаем шрифт
    Font font;

    font.loadFromFile("font/Unispace.ttf");

    Text won("YOU WON!", font, 30);
    Text lose("YOU LOSE. TRY AGAIN!", font, 30);

    won.setPosition(330, 55);
    lose.setPosition(220, 55);

    Color color(246, 135, 65);

    won.setFillColor(color);
    lose.setFillColor(color);

    //Расстановка кораблей противника
    enemyShips.RandomSet();

    int x;
    int y;

    int enemystep;
    bool ismystep = true;
    int winer = 0;
    int button = -1;

    //Обнуляем переменные для выхода в меню
    for (int i = 0; i < 100; i++)
    {
        AvPos.push_back(i);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            MyField[i][k] = 0;
            EnemyField[i][k] = 0;
            FlagMark[i][k] = 0;
        }
    }

    ModeII = -1;
    lasthit = -1;
    direct = -1;
    SizeModeII = -1;

    //Заполнение массивов для отображение
    //Мое поле
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < myShips.GetSizeShip(i); k++)
        {
            MyField[myShips.GetX(i, k)][myShips.GetY(i, k)] = 1;
        }
    }
    //Поле противника
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < enemyShips.GetSizeShip(i); k++)
        {
            EnemyField[enemyShips.GetX(i, k)][enemyShips.GetY(i, k)] = 1;
        }
    }

    while (IsOpen)
    {
        window.clear();
        window.draw(GameScreen);

        //Отрисовка своего поля
        for (int i = 0; i < 10; i++) {
            for (int k = 0; k < 10; k++)
            {
                if (MyField[i][k] == 1 || MyField[i][k] == 2)
                {
                    Ship.setPosition(53 + int(i * 30), 156 + int(k * 30));
                    window.draw(Ship);
                }
                if (MyField[i][k] == -1)//Мимо
                {
                    Miss.setPosition(53 + 11 + int(i * 30), 156 + 11 + int(k * 30));
                    window.draw(Miss);
                }
                if (MyField[i][k] == 2)//Попал
                {
                    Hit.setPosition(53 + int(i * 30), 156 + int(k * 30));
                    window.draw(Hit);
                }
            }
        }

        //Отрисовка поля противника
        for (int i = 0; i < 10; i++) {
            for (int k = 0; k < 10; k++)
            {
                if (EnemyField[i][k] == -1)
                {
                    Miss.setPosition(453 + 11 + int(i * 30), 156 + 11 + int(k * 30));
                    window.draw(Miss);
                }
                if (EnemyField[i][k] == 2 || EnemyField[i][k] == 3)
                {
                    Hit.setPosition(453 + int(i * 30), 156 + int(k * 30));
                    window.draw(Hit);
                    if (EnemyField[i][k] == 3)
                    {
                        Ship.setPosition(453 + int(i * 30), 156 + int(k * 30));
                        window.draw(Ship);
                        Hit.setPosition(453 + int(i * 30), 156 + int(k * 30));
                        window.draw(Hit);
                    }

                }
            }
        }
        
        //Отрисовка маркеров
        for (int i = 0; i < 10; i++) {
            for (int k = 0; k < 10; k++)
            {
                if (FlagMark[i][k] == 1)
                {
                    Flag.setPosition(453 + int(i * 30), 156 + int(k * 30));
                    window.draw(Flag);
                }
            }
        }

        //Отрисовка сообщения о выигрыше\проигрыше
        if (winer == 1)
        {
            window.draw(won);
        }
        else if(winer == 2)
        {
            window.draw(lose);
        }

        //Кнопки
        MenuOff.setTexture(TexMenuOff);
        MenuOff.setTextureRect(IntRect(0, 0, 215, 90));
        button = -1;
        if (IntRect(42, 500, 215, 90).contains(Mouse::getPosition(window)))
        {
            MenuOff.setTexture(TexMenuOn);
            MenuOff.setTextureRect(IntRect(0, 0, 215, 90));
            button = 0;
        }

        //Стрельба противника
        while (!ismystep && winer == 0)
        {
            enemystep = II(myShips);

            x = enemystep % 10;
            y = enemystep / 10;

            if (MyField[x][y] == 0)
            {
                MyField[x][y] = -1;
                ismystep = true;
            }
            else if (MyField[x][y] == 1)
            {
                MyField[x][y] = 2;
            }

            winer = 2;
            for (int i = 0; i < 10; i++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (MyField[i][k] == 1)
                    {
                        winer = 0;
                    }
                }
            }

        }

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                IsOpen = 0;
                return -1;
            case Event::MouseButtonPressed:
                x = Mouse::getPosition(window).x;
                y = Mouse::getPosition(window).y;

                x = (x - 453) / 30;
                y = (y - 156) / 30;

                if (event.mouseButton.button == Mouse::Left)
                {
                    if (winer == 0)
                    {
                        if (x < 10 && x >= 0 && y < 10 && y >= 0)
                        {
                            //Стрельба игрока
                            if (ismystep)
                            {
                                if (FlagMark[x][y] == 0)
                                {
                                    if (EnemyField[x][y] == 1)//попал
                                    {
                                        EnemyField[x][y] = 2;
                                        IsKill(x, y, enemyShips);
                                    }
                                    else if (EnemyField[x][y] == 0)//мимо
                                    {
                                        EnemyField[x][y] = -1;
                                        ismystep = false;
                                    }
                                }
                                winer = 1;
                                for (int i = 0; i < 10; i++)
                                {
                                    for (int k = 0; k < 10; k++)
                                    {
                                        if (EnemyField[i][k] == 1)
                                        {
                                            winer = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (button == 0)
                    {
                        for (int i = 0; i < 10; i++) {
                            myShips.ClearShip(i);
                            enemyShips.ClearShip(i);
                        }
                        return button;
                    }
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    if (winer == 0)
                    {
                        if (x < 10 && x >= 0 && y < 10 && y >= 0)
                        {
                            if ((EnemyField[x][y] == 0 || EnemyField[x][y] == 1) && FlagMark[x][y] == 0)
                            {
                                FlagMark[x][y] = 1;
                            }
                            else if (FlagMark[x][y] == 1)
                            {
                                FlagMark[x][y] = 0;
                            }
                        }
                    }
                }
            default:
                break;
            }
        }
        window.draw(MenuOff);
        window.display();
    }
    return 0;
}
void GameScreen::IsKill(int x, int y, Ships& Ship)
{

    bool iskill = true;
    int index = Ship.FindPos(x, y);

    for (int i = 0; i < Ship.GetSizeShip(index); i++)
    {
        if (EnemyField[Ship.GetX(index, i)][Ship.GetY(index, i)] == 1)
        {
            iskill = false;
        }
    }
  
    if (iskill)
    {
        for (int i = 0; i < Ship.GetSizeShip(index); i++)
        {
            EnemyField[Ship.GetX(index, i)][Ship.GetY(index, i)] = 3;
        }
    }
}

int GameScreen::II(Ships& myShip)
{
    int temp;
    int x, y = 0;
    int randomvalue;
    if (ModeII == -1)//режим поиска корабля
    {
        randomvalue = AvPos[rand() % AvPos.size()];
        x = randomvalue % 10;
        y = randomvalue / 10;

        direct = -1;//направление не выбрано

        DeleteVec(AvPos, randomvalue);

        if (myShip.FindPos(x, y) != -1)//Если попали
        {
            ModeII = randomvalue;//режим выбран
            SizeModeII = myShip.GetSizeShip(myShip.FindPos(x, y)) - 1;
            if (SizeModeII == 0)
            {
                ClearAround(myShip.FindPos(x, y), myShip);
                ModeII = -1;
                lasthit = -1;
                direct = -1;
                return randomvalue;
            }
            else {
                lasthit = ModeII;
                return lasthit;
            }
        }
        else//Если мимо
        {
            return randomvalue;
        }

    }
    else//корабль найден первое попадание
    {
        if (direct == -1)//направление не выбрано
        {
            RenewAvVec();//вектор направлений
            randomvalue = AvVec[rand() % AvVec.size()];

            x = randomvalue % 10;
            y = randomvalue / 10;

            DeleteVec(AvPos, randomvalue);

            if (myShip.FindPos(x, y) != -1)//если попал
            {
                SizeModeII--;
                if (SizeModeII == 0)
                {
                    ClearAround(myShip.FindPos(x, y), myShip);
                    ModeII = -1;
                    return randomvalue;
                }
                else
                {
                    direct = ChVect(randomvalue);
                    lasthit = randomvalue;
                    return randomvalue;
                }
            }
            else//Если мимо
            {
                //RenewAvVec();
                //DeleteVec(AvVec, randomvalue);
                direct = -1;
                return randomvalue;
            }

        }
        else if (direct == 0)//лево
        {
            lasthit = lasthit - 1;
            if (lasthit % 10 != 9)
            {
                if (FindVector(AvPos, lasthit))
                {
                    DeleteVec(AvPos, lasthit);
                    x = lasthit % 10;
                    y = lasthit / 10;
                    if (myShip.FindPos(x, y) != -1)
                    {
                        SizeModeII--;
                        if (SizeModeII == 0)
                        {
                            ClearAround(myShip.FindPos(x, y), myShip);
                            direct = -1;
                            ModeII = -1;
                            return lasthit;
                        }
                        else
                        {
                            return lasthit;
                        }
                    }
                    else
                    {
                        direct = 2;
                        temp = lasthit;
                        lasthit = ModeII;
                        return temp;
                    }
                }
                else
                {
                    direct = 2;
                    lasthit = ModeII;
                    II(myShip);
                }
            }
            else
            {
                direct = 2;
                lasthit = ModeII;
                II(myShip);
            }
        }
        else if (direct == 1)//Вверх
        {
            lasthit = lasthit - 10;

            if (FindVector(AvPos, lasthit))
            {
                DeleteVec(AvPos, lasthit);
                x = lasthit % 10;
                y = lasthit / 10;
                if (myShip.FindPos(x, y) != -1)
                {
                    SizeModeII--;
                    if (SizeModeII == 0)
                    {
                        ClearAround(myShip.FindPos(x, y), myShip);
                        direct = -1;
                        ModeII = -1;
                        return lasthit;
                    }
                    else
                    {
                        return lasthit;
                    }
                }
                else
                {
                    direct = 3;
                    temp = lasthit;
                    lasthit = ModeII;
                    return temp;
                }
            }
            else
            {
                direct = 3;
                lasthit = ModeII;
                II(myShip);
            }
        }
        else if (direct == 2)//Вправо
        {
            lasthit = lasthit + 1;
            if (lasthit % 10 != 0)
            {
                if (FindVector(AvPos, lasthit))
                {
                    DeleteVec(AvPos, lasthit);
                    x = lasthit % 10;
                    y = lasthit / 10;
                    if (myShip.FindPos(x, y) != -1)
                    {
                        SizeModeII--;
                        if (SizeModeII == 0)
                        {
                            ClearAround(myShip.FindPos(x, y), myShip);
                            direct = -1;
                            ModeII = -1;
                            return lasthit;
                        }
                        else
                        {
                            return lasthit;
                        }
                    }
                    else
                    {
                        direct = 0;
                        temp = lasthit;
                        lasthit = ModeII;
                        return temp;
                    }
                }
                else
                {
                    direct = 0;
                    lasthit = ModeII;
                    II(myShip);
                }
            }
            else
            {
                direct = 0;
                lasthit = ModeII;
                II(myShip);
            }
        }
        else if (direct == 3)//Вниз
        {
            lasthit = lasthit + 10;
            if (FindVector(AvPos, lasthit))
            {
                DeleteVec(AvPos, lasthit);
                x = lasthit % 10;
                y = lasthit / 10;
                if (myShip.FindPos(x, y) != -1)
                {
                    SizeModeII--;
                    if (SizeModeII == 0)
                    {
                        ClearAround(myShip.FindPos(x, y), myShip);
                        direct = -1;
                        ModeII = -1;
                        return lasthit;
                    }
                    else
                    {
                        return lasthit;
                    }
                }
                else
                {
                    direct = 1;
                    temp = lasthit;
                    lasthit = ModeII;
                    return temp;
                }
            }
            else
            {
                direct = 1;
                lasthit = ModeII;
                II(myShip);
            }
        }
    }
}

void GameScreen::DeleteVec(vector<int>& Vect, int value)
{
    for (int i = 0; i < Vect.size(); i++)
    {
        if (value == Vect[i])
        {
            Vect.erase(Vect.begin() + i);
        }
    }
}

void GameScreen::RenewAvVec()
{
    AvVec.clear();

    int right = ModeII + 1;
    int left = ModeII - 1;
    int up = ModeII - 10;
    int down = ModeII + 10;

    for (int i = 0; i < AvPos.size(); i++)
    {
        if (right == AvPos[i] && ModeII % 10 != 9)
        {
            AvVec.push_back(right);
        }
        if (left == AvPos[i] && ModeII % 10 != 0)
        {
            AvVec.push_back(left);
        }
        if (up == AvPos[i])
        {
            AvVec.push_back(up);
        }
        if (down == AvPos[i])
        {
            AvVec.push_back(down);
        }
    }
}

int GameScreen::ChVect(int RandomHit)
{
    switch (ModeII - RandomHit)
    {
    case (1):
        return 0;
    case (10):
        return 1;
    case (-1):
        return 2 ;
    case (-10):
        return 3;
    default:
        return -1;
    }
}

bool GameScreen::FindVector(vector<int>& Vect, int value)
{
    for (int i = 0; i < Vect.size(); i++)
    {
        if (value == Vect[i])
        {
            return true;
        }
    }
    return false;
}

void GameScreen::ClearAround(int index, Ships& myShip)
{
    int n;
    for (int i = 0; i < myShip.GetSizeShip(index); i++)
    {
        n = myShip.GetY(index, i) * 10 + myShip.GetX(index, i);
        
        if (n % 10 != 9)
        {
            DeleteVec(AvPos, n - 9);
            DeleteVec(AvPos, n + 1);
            DeleteVec(AvPos, n + 11);
        }
        if (n % 10 != 0)
        {
            DeleteVec(AvPos, n + 9);
            DeleteVec(AvPos, n - 1);
            DeleteVec(AvPos, n - 11);
        }
        DeleteVec(AvPos, n - 10);
        DeleteVec(AvPos, n + 10);
    }
}
