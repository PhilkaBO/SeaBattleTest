#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Ships.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;


class SetPosScreen
{
private:

	//MainMenu Menu;
	int x, y = -1;
	int button = -1;
	bool IsOpenWindow = true;
	int counter = 0;
	int single_deck = 4;
	int double_deck = 3;
	int three_deck = 2;
	int four_deck = 1;

public:
	int SetPosDraw(RenderWindow& window, Ships& myShip);
};
