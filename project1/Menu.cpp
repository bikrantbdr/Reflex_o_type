#include "Menu.h"
#include "CLassic.h"
#include "User.h"
#include"Rapid.h"
#include <iostream>
float width = 1200, height = 900;
Menu::Menu(float width, float height)
{
	selectedItemIndex = 0;
	int start = 250, gap = 125;
	if (!move_buffer.loadFromFile("data/sound/menu.wav")) {
		//sound not loaded
	}
	if (!end_buffer.loadFromFile("data/sound/over.wav")) {
		//sound not loaded
	}
	if (!enter_buffer.loadFromFile("data/sound/enter.wav")) {
		//sound not loaded
	}
	move.setBuffer(move_buffer);
	end.setBuffer(end_buffer);
	enter.setBuffer(enter_buffer);


	if (!font.loadFromFile("data/font/arial.ttf"))
	{
		// handle error
	}

	//load the title image/logo design
	texture.loadFromFile("data/image/title.PNG");
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(width / 2 - 181, 50));


	//classic button
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(43, 234, 40));
	menu[0].setString("Classic");
	menu[0].setPosition(sf::Vector2f((width / 2 - 50), (start + gap * 0 + 5)));

	//rapid button
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color(43, 234, 40));
	menu[1].setString("Rapid");
	menu[1].setPosition(sf::Vector2f((width / 2 - 38), (start + gap * 1 + 5)));

	//user button
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color(43, 234, 40));
	menu[2].setString("User");
	menu[2].setPosition(sf::Vector2f((width / 2 - 30), (start + gap * 2 + 5)));

	//exit button
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color(43, 234, 40));
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f((width / 2 - 30), (start + gap * 3 + 5)));


	//classic button container
	option[0].setSize(sf::Vector2f(200, 50));
	option[0].setFillColor(sf::Color(183, 183, 184));
	option[0].setPosition((width / 2 - 100), start + gap * 0);

	//rapid button container
	option[1].setSize(sf::Vector2f(200, 50));
	option[1].setFillColor(sf::Color(64, 64, 64));
	option[1].setPosition((width / 2 - 100), start + gap * 1);

	//user button container
	option[2].setSize(sf::Vector2f(200, 50));
	option[2].setFillColor(sf::Color(64, 64, 64));
	option[2].setPosition((width / 2 - 100), start + gap * 2);

	//exit button container
	option[3].setSize(sf::Vector2f(200, 50));
	option[3].setFillColor(sf::Color(64, 64, 64));
	option[3].setPosition((width / 2 - 100), start + gap * 3);




}
Menu::~Menu()
{
}

void Menu::run() {

	sf::RenderWindow window(sf::VideoMode(width, height), "Typing", sf::Style::None);


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					this->MoveUp();
					//std::cout<<"up was pressed \n";
					break;

				case sf::Keyboard::Down:
					this->MoveDown();
					//std::cout<<"down was pressed\n";
					break;
				case sf::Keyboard::Return:
					//std::cout<<"enter\n";
					enter.play();

					//select a option based on selectedItemIndex
					switch (selectedItemIndex)
					{
					case 0:
					{
						Classic classic;
						classic.classic_run();
					}
					break;
					case 1:
					{
						Rapid rapid;
						rapid.rapid_run();
					}
					break;
					case 2:
					{
						User usr;
						usr.user_run();
					}

					break;
					case 3:
						window.close();
						break;

					}
					break;
				}

			}

		}

		//update
		window.clear(sf::Color(13, 13, 13));
		this->draw(window);
		window.display();
	}
}


void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(option[i]);
		window.draw(menu[i]);
	}
	window.draw(sprite);

}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		option[selectedItemIndex].setFillColor(sf::Color(64, 64, 64));
		selectedItemIndex--;
		option[selectedItemIndex].setFillColor(sf::Color(183, 183, 184));
		move.play();
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		option[selectedItemIndex].setFillColor(sf::Color(64, 64, 64));
		selectedItemIndex++;
		option[selectedItemIndex].setFillColor(sf::Color(183, 183, 184));
		move.play();
	}

}