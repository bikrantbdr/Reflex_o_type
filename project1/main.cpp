#include "SFML/Graphics.hpp"
#include <iostream>

#include "Menu.h"

using namespace sf;

int main() {
	//start menu interface
	Menu menu(1200, 900);
	menu.run();
}