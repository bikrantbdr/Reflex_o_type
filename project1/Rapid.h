#ifndef RAPID_H
#define RAPID_H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<fstream>
#include <string>
#include<vector>
#include <stdlib.h> 
#include <stdlib.h>
#include <sstream>
#include <Windows.h>

class Rapid
{
public:
	Rapid();
	~Rapid();
	void rapid_run();
	void rapid_draw(sf::RenderWindow& window);
	void rapid_draw_values(sf::RenderWindow& window);
	void set_activeword();
	void set_values();
	void set_user_word();
	void check();
	void timer_f();
	void write_high();
private:
	//rapid 
	std::vector<std::string> words;
	std::string line, active_word, user_word;
	sf::Font font;
	sf::Text rapid_head, timer_text, life_text, score_text, active_text, user_text, timer_val, life_val, score_val, gameover_overlay;
	sf::RectangleShape container_a, container_b, container_c;
	sf::Clock clock;
	sf::SoundBuffer gameover_buffer, wrong_buffer, right_buffer;	
	sf::Sound gameover_sound, wrong_sound, right_sound;
	int gap;
	int timer, score, life, countdown;
	int gameover;

};

#endif