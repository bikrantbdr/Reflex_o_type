#include "SFML/Graphics.hpp"
#include <iostream>

#include "Menu.h"

using namespace sf;

int main() {
	//std::cout << "begins\n";
	Menu menu(1200, 900);
	menu.run();
}