#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY 85
#include "SFML/Graphics.hpp"

class Self_Keyboard {
public:
	Self_Keyboard(float keyboard_start);
	~Self_Keyboard();
	void key_pressed(int index);
	void key_released(int index);
	void keyboard_draw(sf::RenderWindow& window);
	int keyindex(int code);


private:
	//keyboard
	sf::RectangleShape container;
	sf::RectangleShape key[KEY];
	sf::Text letter[KEY];
	sf::Font keyfont;
};


#endif