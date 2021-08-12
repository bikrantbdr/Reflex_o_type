#ifndef CLASSIC_H
#define CLASSIC_H

#include "SFML/Graphics.hpp"
#include<string>
#include <sstream>
class Classic
{
public:
	Classic();
	~Classic();
	void classic_run();
	void classic_draw(sf::RenderWindow& window);
	void check_color();         //accuracy
	void set_active_sentence(); //get a sentence from file to display
	void set_text_string();     //set active sentences's font, string, color and position
	void check_letter(sf::Event& event); 		//check if the letter is right
	void write_accuracy_on_file();
	void timer_start();
	void timer_stop();
private:
	std::vector<float> alpha_values;
	std::vector<std::string> sentences;
	std::string line, active_sentence;
	int active_letter_index, letter_correct, words_in_sentence;
	sf::Text classic_head, alpha_text[26], active_text[200], underscope, wpm_accuracy_text, wpm_value;
	sf::Font font;
	sf::Clock clock;
	float width, height, gap, alph_val, wpm, prev_wpm, highest_wpm;
	sf::RectangleShape container_a, container_b, alpha[26];
};

#endif
