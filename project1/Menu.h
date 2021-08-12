#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	//menu
	void run();
	void draw(sf::RenderWindow& window);

	void MoveUp();
	void MoveDown();

private:
	//menu
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape option[MAX_NUMBER_OF_ITEMS];
	sf::Image title;
	sf::Texture texture;
	sf::Sprite sprite;
	int selectedItemIndex;
	sf::SoundBuffer move_buffer, end_buffer, enter_buffer;
	sf::Sound move, end, enter;
};

#endif
