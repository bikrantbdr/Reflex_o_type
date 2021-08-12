#include "Rapid.h"
#include "Keyboard.h"
#include<iostream>

Rapid::Rapid() {
	float width = 1200, height = 900;
	int a_width = 950, a_height = 75, a_start = 100;
	int b_width = 950, b_height = 150;
	int c_width = 950, c_height = 150;
	gap = 30;

	timer = 5;
	score = 0;
	life = 3;



	if (!font.loadFromFile("data/font/arial2.ttf"))
	{
		// handle error
	}

	rapid_head.setFont(font);
	rapid_head.setFillColor(sf::Color(43, 234, 40));
	rapid_head.setString("RAPID");
	rapid_head.setPosition(sf::Vector2f((width / 2 - 50), 10));

	//load text files
	std::ifstream  rapid_text("data/textfiles/rapid_text.txt");
	if (!rapid_text)
	{
		std::cout << "File can not opened" << std::endl;
		exit(0);
	}

	while (getline(rapid_text, line))
	{
		words.push_back(line);
	}
	rapid_text.close();
	//sounds
	if (!wrong_buffer.loadFromFile("data/sound/wrong.wav")) {
		//nothing
	}
	if (!gameover_buffer.loadFromFile("data/sound/aww.wav")) {
		//nothing
	}
	if (!right_buffer.loadFromFile("data/sound/right.wav")) {
		//nothing
	}
	gameover_sound.setBuffer(gameover_buffer);
	wrong_sound.setBuffer(wrong_buffer);
	right_sound.setBuffer(right_buffer);

	//container a
	container_a.setSize(sf::Vector2f(a_width, a_height));
	container_a.setFillColor(sf::Color(13, 13, 13));
	container_a.setPosition((1200 - a_width) / 2, a_start);

	//container b
	container_b.setSize(sf::Vector2f(b_width, b_height));
	container_b.setFillColor(sf::Color(50, 50, 50));
	container_b.setPosition((1200 - b_width) / 2, container_a.getPosition().y + container_a.getSize().y + gap + 10);

	//container c
	container_c.setSize(sf::Vector2f(c_width, c_height));
	container_c.setFillColor(sf::Color(64, 64, 64));
	container_c.setPosition((1200 - c_width) / 2, container_b.getPosition().y + container_b.getSize().y + gap);

	//container a texts which remains unchanged
	//timer text
	timer_text.setFont(font);
	timer_text.setFillColor(sf::Color(113, 247, 119));
	timer_text.setPosition(container_a.getPosition().x + 25, container_a.getPosition().y + 20);
	timer_text.setString("Timer:");

	//timer value
	timer_val.setFont(font);
	timer_val.setFillColor(sf::Color(113, 247, 119));
	timer_val.setPosition(container_a.getPosition().x + 25 + 95, container_a.getPosition().y + 20);

	//score text
	score_text.setFont(font);
	score_text.setFillColor(sf::Color(113, 247, 119));
	score_text.setPosition(container_a.getPosition().x + container_a.getSize().x / 2 - 50, container_a.getPosition().y + 20);
	score_text.setString("Score:");

	//score value
	score_val.setFont(font);
	score_val.setFillColor(sf::Color(113, 247, 119));
	score_val.setPosition(container_a.getPosition().x + container_a.getSize().x / 2 - 50 + 95, container_a.getPosition().y + 20);

	//life text
	life_text.setFont(font);
	life_text.setFillColor(sf::Color(113, 247, 119));
	life_text.setPosition(container_a.getPosition().x + container_a.getSize().x - 125, container_a.getPosition().y + 20);
	life_text.setString("Life:");

	//life value
	life_val.setFont(font);
	life_val.setFillColor(sf::Color(113, 247, 119));
	life_val.setPosition(container_a.getPosition().x + container_a.getSize().x - 125 + 70, container_a.getPosition().y + 20);



	//active text
	active_text.setFont(font);
	active_text.setFillColor(sf::Color(255, 255, 255));
	active_text.setPosition(container_b.getPosition().x + container_b.getSize().x / 2 - 55, container_b.getPosition().y + container_b.getSize().y / 2 - 10);

	//user text
	user_text.setFont(font);
	user_text.setFillColor(sf::Color(255, 255, 255));
	user_text.setPosition(container_c.getPosition().x + container_c.getSize().x / 2 - 100, container_c.getPosition().y + container_c.getSize().y / 2 - 10);

	//game over overlay
	gameover_overlay.setFont(font);
	gameover_overlay.setString("\t\t\t\tGAMEOVER\n\n\n PRESS SPACE TO PLAY AGAIN");
	gameover_overlay.setFillColor(sf::Color(113, 247, 119));
	gameover_overlay.setPosition(container_c.getPosition().x + container_c.getSize().x / 2 - 200, container_c.getPosition().y + container_c.getSize().y / 2 - 120);

	//inatilize
	set_activeword();
	gameover = 0;
}
Rapid::~Rapid() {
	//nothing
}




void Rapid::rapid_run() {
	//keyboard init
	Self_Keyboard key(container_c.getPosition().y + container_c.getSize().y + gap);
	sf::RenderWindow rapid_window(sf::VideoMode(1200, 900), "rapid", sf::Style::None);
	while (rapid_window.isOpen())
	{
		sf::Event event;


		while (rapid_window.pollEvent(event))
		{
			//user text input
			if (event.type == sf::Event::TextEntered && gameover == 0)
			{
				if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 27) {
					user_word.push_back(static_cast<char>(event.text.unicode));
				}
				if (event.text.unicode == 8 && user_word.size() != 0) {
					user_word.erase(user_word.size() - 1, 1);
				}
				if (event.text.unicode == 13 && user_word.size() != 0) {
					
					check();
					this->write_high();
				}
			}
			//common event loop
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				//keyboard pressed
				if (event.key.code != sf::Keyboard::Escape)
				key.key_pressed(key.keyindex(event.key.code));
				//std::cout << event.key.code << std::endl;
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					rapid_window.close();
					break;
				case sf::Keyboard::Space:
					if (gameover == 1) {
						gameover = 0;
						life = 3;
						score = 0;
						timer = 5;
					}
				}
				//keyboard released
				key.key_released(key.keyindex(event.key.code));
				break;
			}
		}


		if (gameover == 0)
		{

			this->set_values();
			this->set_user_word();
			this->timer_f();
			rapid_window.clear(sf::Color(40, 40, 40));
			this->rapid_draw(rapid_window);
			this->rapid_draw(rapid_window);
			//keyboard draw
			key.keyboard_draw(rapid_window);
			rapid_window.display();
		}
		else {
			rapid_window.clear(sf::Color(40, 40, 40));
			rapid_window.draw(gameover_overlay);
			rapid_window.display();
		}

	}
}
void Rapid::rapid_draw(sf::RenderWindow& rapid_window) {

	rapid_window.draw(rapid_head);
	rapid_window.draw(container_a);
	rapid_window.draw(container_b);
	rapid_window.draw(container_c);
	rapid_window.draw(active_text);
	rapid_window.draw(user_text);
	rapid_window.draw(timer_text);
	rapid_window.draw(score_text);
	rapid_window.draw(life_text);
	rapid_window.draw(timer_val);
	rapid_window.draw(score_val);
	rapid_window.draw(life_val);

}
void Rapid::rapid_draw_values(sf::RenderWindow& rapid_window) {
	rapid_window.draw(timer_val);
	rapid_window.draw(score_val);
	rapid_window.draw(life_val);

}
void Rapid::set_activeword() {
	srand(time(0));
	int random = rand() % words.size();
	active_word = words[random];
	words.erase(words.begin() + random);
	active_text.setString(active_word);
}

void Rapid::set_values() {
	std::stringstream life_s, score_s, timer_s;

	life_s << life;
	score_s << score;
	timer_s << timer;
	timer_val.setString(timer_s.str());
	life_val.setString(life_s.str());
	score_val.setString(score_s.str());
}

void::Rapid::set_user_word() {
	user_text.setString(user_word);
}

void::Rapid::timer_f() {
	countdown = clock.getElapsedTime().asSeconds();
	if (countdown > 0 && gameover == 0) {
		timer--;
		clock.restart();
	}
	if (timer < 0) {
		life--;
		if (life >= 1)
		{
			wrong_sound.play();
		}
		else
		{
			gameover_sound.play();
		}
		this->set_activeword();
		user_word.clear();
		if (life >= 1) {
			timer = 5;
		}
		else {
			timer = 0;
		}
	}
	set_values();
	if (life == 0) {
		gameover = 1;
	}
}


void::Rapid::check() {
	if (user_word == active_word) {
		score += 20;
		timer = 5;
		right_sound.play();
	}
	else {
		life--;
		timer = 5;
		if (life >= 1)
		{
			wrong_sound.play();
		}
		else {
			gameover_sound.play();
			gameover = 1;
		}

	}
	user_word.clear();
	this->set_activeword();
}

void Rapid::write_high() {
	int prev;
	std::fstream rapid_highest("data/textfiles/rapid_highest.txt", std::ios::in);
	rapid_highest >> prev;
	rapid_highest.close();

	std::fstream rapid_rewrite("data/textfiles/rapid_highest.txt", std::ios::out);
	if (prev < score) {
		rapid_rewrite << score;
	}
	else {
		rapid_rewrite << prev;
	}
	rapid_rewrite.close();
}

