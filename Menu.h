#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Ships.h"

using namespace sf;

class MainMenu {
private:
    bool IsOpenMenu = true;
    int GameMode = -1;

public:
    int MenuDraw(RenderWindow& window, bool IsOpenMenu);
};