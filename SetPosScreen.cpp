#include "SetPosScreen.h"

int SetPosScreen::SetPosDraw(RenderWindow& window, Ships& myShips)
{
	Texture TexSetPosScreen;
	Texture TexShip;

	//Кнопки
	Texture TexMenuOff;
	Texture TexMenuOn;
	Texture TexDeleteLastShipOff;
	Texture TexDeleteLastShipOn;
	Texture TexSetRandomOff;
	Texture TexSetRandomOn;
	Texture TexSetShipOff;
	Texture TexSetShipOn;
	Texture TexStartGameOff;
	Texture TexStartGameOn;

	TexMenuOff.loadFromFile("images/SetPos/MenuOff.png");
	TexMenuOn.loadFromFile("images/SetPos/MenuOn.png");
	TexDeleteLastShipOff.loadFromFile("images/SetPos/RemoveLastShipOff.png");
	TexDeleteLastShipOn.loadFromFile("images/SetPos/RemoveLastShipOn.png");
	TexSetRandomOff.loadFromFile("images/SetPos/SetRandomOff.png");
	TexSetRandomOn.loadFromFile("images/SetPos/SetRandomOn.png");
	TexSetShipOff.loadFromFile("images/SetPos/SetShipOff.png");
	TexSetShipOn.loadFromFile("images/SetPos/SetShipOn.png");
	TexStartGameOff.loadFromFile("images/SetPos/StartGameOff.png");
	TexStartGameOn.loadFromFile("images/SetPos/StartGameOn.png");

	Sprite MenuOff(TexMenuOff);
	Sprite DeleteLastShipOff(TexDeleteLastShipOff);
	Sprite SetRandomOff(TexSetRandomOff);
	Sprite SetShipOff(TexSetShipOff);

	MenuOff.setPosition(42, 500);
	DeleteLastShipOff.setPosition(294, 500);
	SetRandomOff.setPosition(546, 500);
	SetShipOff.setPosition(546, 390);

	TexSetPosScreen.loadFromFile("images/SetPos/SetScreen.png");
	TexShip.loadFromFile("images/SetPos/Ship.png");

	Sprite SetPosScreen(TexSetPosScreen);
	Sprite Ship(TexShip);

	//Загружаем шрифт
	Font font;

	font.loadFromFile("font/Unispace.ttf");

	Text single_deck_text("", font, 30);
	Text double_deck_text("", font, 30);
	Text three_deck_text("", font, 30);
	Text four_deck_text("", font, 30);

	single_deck_text.setPosition(498, 157);
	double_deck_text.setPosition(498, 217);
	three_deck_text.setPosition(498, 277);
	four_deck_text.setPosition(498, 337);

	Color color(246, 135, 65);

	single_deck_text.setFillColor(color);
	double_deck_text.setFillColor(color);
	three_deck_text.setFillColor(color);
	four_deck_text.setFillColor(color);

	single_deck_text.setString(to_string(single_deck));
	double_deck_text.setString(to_string(double_deck));
	three_deck_text.setString(to_string(three_deck));
	four_deck_text.setString(to_string(four_deck));

	bool repeat = true;
	int temp = -1;
	counter = 0;

	while (IsOpenWindow)
	{
		button = -1;
	
		MenuOff.setTexture(TexMenuOff);
		MenuOff.setTextureRect(IntRect(0, 0, 215, 90));

		DeleteLastShipOff.setTexture(TexDeleteLastShipOff);
		DeleteLastShipOff.setTextureRect(IntRect(0, 0, 215, 90));

		SetRandomOff.setTexture(TexSetRandomOff);
		SetRandomOff.setTextureRect(IntRect(0, 0, 215, 90));

		//Замена текстур кнопок
		if (IntRect(42, 500, 215, 90).contains(Mouse::getPosition(window)))
		{
			MenuOff.setTexture(TexMenuOn);
			MenuOff.setTextureRect(IntRect(0, 0, 215, 90));
			button = 0;
		}
		if (IntRect(294, 500, 215, 90).contains(Mouse::getPosition(window)))
		{
			DeleteLastShipOff.setTexture(TexDeleteLastShipOn);
			DeleteLastShipOff.setTextureRect(IntRect(0, 0, 215, 90));
			button = 1;
		}
		if (IntRect(546, 500, 215, 90).contains(Mouse::getPosition(window)))
		{
			SetRandomOff.setTexture(TexSetRandomOn);
			SetRandomOff.setTextureRect(IntRect(0, 0, 215, 90));
			button = 2;
		}

		SetShipOff.setTexture(TexSetShipOff);
		SetShipOff.setTextureRect(IntRect(0, 0, 215, 90));

		if (IntRect(546, 390, 215, 90).contains(Mouse::getPosition(window)))
		{
			SetShipOff.setTexture(TexSetShipOn);
			SetShipOff.setTextureRect(IntRect(0, 0, 215, 90));
			button = 3;
		}

		if (counter == 10) {
			SetShipOff.setTexture(TexStartGameOff);
			SetShipOff.setTextureRect(IntRect(0, 0, 215, 90));

			if (IntRect(546, 390, 215, 90).contains(Mouse::getPosition(window)))
			{
				SetShipOff.setTexture(TexStartGameOn);
				SetShipOff.setTextureRect(IntRect(0, 0, 215, 90));
				button = 3;
			}
		}

		single_deck = 4;
		double_deck = 3;
		three_deck = 2;
		four_deck = 1;

		single_deck = single_deck - myShips.CheckType(1);
		double_deck = double_deck - myShips.CheckType(2);
		three_deck = three_deck - myShips.CheckType(3);
		four_deck = four_deck - myShips.CheckType(4);

		window.draw(SetPosScreen);//Рисуем фон	
		//Отрисовка кораблей
		for (int i = 0; i < 10; i++) {
			for (int k = 0; k < myShips.GetSizeShip(i); k++)
			{
				if (myShips.GetSizeShip(i) != 0) 
				{
					Ship.setPosition(50 + int(myShips.GetX(i, k) * 30), 160 + int(myShips.GetY(i, k)*30));
					window.draw(Ship);
				}
			}
		}

		//Отображение количества кораблей 
		if (counter != temp)
		{
			single_deck_text.setString(to_string(single_deck));
			double_deck_text.setString(to_string(double_deck));
			three_deck_text.setString(to_string(three_deck));
			four_deck_text.setString(to_string(four_deck));
		}
		temp = counter;

		//Обработчик событий
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				IsOpenWindow = false;
				return -1;
				window.close();
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					x = Mouse::getPosition(window).x;
					y = Mouse::getPosition(window).y;

					x = (x - 50) / 30;
					y = (y - 160) / 30;

					if (x < 10 && x >= 0 && y < 10 && y >= 0)
					{
						repeat = true;
						for (int i = 0; i < myShips.GetSizeShip(counter); i++)
						{
							if (myShips.GetX(counter, i) == x && myShips.GetY(counter, i) == y)
							{
								myShips.ClearPosition(counter, i);
								repeat = false;
							}
						}
						if (repeat == true && counter < 10)
						{
							myShips.SetCoord(counter, x, y);
						}
					}
					if (button == 0)
					{
						//Запуск меню
						for (int i = 0; i < 10; i++) {
							myShips.ClearShip(i);
						}
						counter = 0;
						IsOpenWindow == false;
						return button;
					}
					if (button == 1) 
					{
						//Удаление последнего поставленного корабля
						if (counter >= 0)
						{
							if (myShips.GetSizeShip(counter) == 0 && counter > 0 || counter == 10) {
								counter--;
								myShips.ClearShip(counter);
							}
							else
							{
								myShips.ClearShip(counter);
							}
						}
					}
					if (button == 2) 
					{
						myShips.RandomSet();
						counter = 10;
					}
					if (button == 3) 
					{
						//Установить корабль
						if (!myShips.CheckShip(counter) && counter < 10)
						{
							myShips.ClearShip(counter);
						}
						else if (counter < 10)
						{
							counter++;
						}
						else if (counter == 10)
						{
							return button;
						}
					}
				}
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Enter) {
					//Установить корабль
					if (!myShips.CheckShip(counter) && counter < 10)
					{
						myShips.ClearShip(counter);
					}
					else if (counter < 10)
					{
						counter++;
					}
					cout << endl << counter << endl;
				}
				if (event.key.code == Keyboard::Escape) 
				{
					if (myShips.GetSizeShip(counter) == 0 && counter > 0 || counter == 10) {
						counter--;
						myShips.ClearShip(counter);
					}
					else
					{
						myShips.ClearShip(counter);
					}
				}
			default:
				break;
			}
		}

		window.draw(single_deck_text);
		window.draw(double_deck_text);
		window.draw(three_deck_text);
		window.draw(four_deck_text);

		window.draw(MenuOff);
		window.draw(DeleteLastShipOff);
		window.draw(SetRandomOff);
		window.draw(SetShipOff);

		window.display();
	}
}
