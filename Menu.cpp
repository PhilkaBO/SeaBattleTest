#include "Menu.h"

int MainMenu::MenuDraw(RenderWindow& window, bool IsOpenMenu)
{

    Texture TexMenuScreen;
    Texture TexFreeModeOff;
    Texture TexFreeModeOn;
    Texture TexCompetitiveModeOff;
    Texture TexCompetitiveModeOn;
    Texture TexRecordsTableOff;
    Texture TexRecordsTableOn;
    Texture TexExitOff;
    Texture TexExitOn;

    TexMenuScreen.loadFromFile("images/Menu/MenuScreen.png");
    TexFreeModeOff.loadFromFile("images/Menu/FreeModeOff.png");
    TexFreeModeOn.loadFromFile("images/Menu/FreeModeOn.png");
    TexCompetitiveModeOff.loadFromFile("images/Menu/CompetitiveModeOff.png");
    TexCompetitiveModeOn.loadFromFile("images/Menu/CompetitiveModeOn.png");
    TexRecordsTableOff.loadFromFile("images/Menu/RecordsTableOff.png");
    TexRecordsTableOn.loadFromFile("images/Menu/RecordsTableOn.png");
    TexExitOff.loadFromFile("images/Menu/ExitOff.png");
    TexExitOn.loadFromFile("images/Menu/ExitOn.png");

    Sprite MenuScreen(TexMenuScreen);
    Sprite FreeModeOff(TexFreeModeOff);
    Sprite CompetitiveModeOff(TexCompetitiveModeOff);
    Sprite RecordsTableOff(TexRecordsTableOff);
    Sprite ExitOff(TexExitOff);


    FreeModeOff.setPosition(50, 250);
    CompetitiveModeOff.setPosition(50, 350);
    RecordsTableOff.setPosition(50, 450);
    ExitOff.setPosition(550, 450);

    Font font;

    font.loadFromFile("font/Unispace.ttf");

    Text version("Version: 1.0", font, 15);
    version.setPosition(600, 560);

    Color color(246, 135, 65);

    version.setFillColor(color);

    while (IsOpenMenu)
    {

        GameMode = -1;

        FreeModeOff.setTexture(TexFreeModeOff);
        FreeModeOff.setTextureRect(IntRect(0, 0, 215, 90));

        CompetitiveModeOff.setTexture(TexCompetitiveModeOff);
        CompetitiveModeOff.setTextureRect(IntRect(0, 0, 215, 90));

        RecordsTableOff.setTexture(TexRecordsTableOff);
        RecordsTableOff.setTextureRect(IntRect(0, 0, 215, 90));

        ExitOff.setTexture(TexExitOff);
        ExitOff.setTextureRect(IntRect(0, 0, 215, 90));

        //Замена текстур кнопок
        if (IntRect(50, 250, 215, 90).contains(Mouse::getPosition(window)))
        {
            FreeModeOff.setTexture(TexFreeModeOn);
            FreeModeOff.setTextureRect(IntRect(0, 0, 215, 90));
            GameMode = 0;
        }
        if (IntRect(50, 350, 215, 90).contains(Mouse::getPosition(window)))
        {
            CompetitiveModeOff.setTexture(TexCompetitiveModeOn);
            CompetitiveModeOff.setTextureRect(IntRect(0, 0, 215, 90));
            GameMode = 1;
        }
        if (IntRect(50, 450, 215, 90).contains(Mouse::getPosition(window)))
        {
            RecordsTableOff.setTexture(TexRecordsTableOn);
            RecordsTableOff.setTextureRect(IntRect(0, 0, 215, 90));
            GameMode = 2;
        }

        if (IntRect(550, 450, 215, 90).contains(Mouse::getPosition(window)))
        {
            ExitOff.setTexture(TexExitOn);
            ExitOff.setTextureRect(IntRect(0, 0, 215, 90));
            GameMode = 3;
        }

        //Обработка событий
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                IsOpenMenu = false;
                window.close();
                return -1;
                break;
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left)//Нажатие на клавиши меню
                {
                    switch (GameMode)
                    {
                    case 0:
                        //Не реализовано FreeMode
                        IsOpenMenu = false;
                        return 0;

                    case 1:
                        //Не реализовано CompetitiveMode
                        IsOpenMenu = false;
                        return 0;
                    case 2:
                        //Не реализовано RecordsTable
                        cout << "2";
                        break;

                    case 3:
                        IsOpenMenu = false;
                        return -1;
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }

        window.draw(MenuScreen);
        window.draw(FreeModeOff);
        window.draw(CompetitiveModeOff);
        window.draw(RecordsTableOff);
        window.draw(ExitOff);
        window.draw(version);

        window.display();
    }
}