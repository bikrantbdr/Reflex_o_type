
#ifndef USER_H
#define USER_H

#include "SFML/Graphics.hpp"
#include<fstream>
#include <sstream>
class User {
public:
	User();
	~User();
	void user_run();
	void user_draw(sf::RenderWindow& window);
	void reset_files();
	void set_values();
private:
	sf::Text user_head, avg_t, high_t, time_t, avg_text, high_text, time_h_text,  time_m_text, time_s_text, reset_text, rapid_t, rapid_text;
	sf::RectangleShape reset_box;
	sf::Font font;
	float highest_wpm, time_val, temp, word_val, avg_val, rapid_high;
	int total, hour, min, sec;

};

#endif