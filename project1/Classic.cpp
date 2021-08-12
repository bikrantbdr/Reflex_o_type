#include "Classic.h"
#include "Keyboard.h"
#include<iostream>
#include<fstream>
Classic::Classic() {
	width = 1200;
	height = 900;
	int a_width = 950, a_height = 85, a_start = 100;
	int b_width = 950, b_height = 150;
	int alp_width = 30, alp_height = 30;
	gap = 30;

	//load text files
	std::ifstream  classic_text("data/textfiles/classic_text.txt");
	if (!classic_text)
	{
		std::cout << "File can not opened" << std::endl;
		exit(0);
	}

	while (getline(classic_text, line))
	{
		//std::cout<<line<<std::endl;
		sentences.push_back(line);
	}
	classic_text.close();

	if (!font.loadFromFile("data/font/arial1.ttf"))
	{
		// handle error
	}

	//load alpha_values from files
	std::ifstream  alpha_file("data/textfiles/alphabet_values.txt");
	if (!alpha_file)
	{
		std::cout << "File can not opened" << std::endl;
		exit(0);
	}

	for (int i = 0; i < 26; i++)
	{
		alpha_file >> alph_val;
		alpha_values.push_back(alph_val);
	}

	classic_head.setFont(font);
	classic_head.setFillColor(sf::Color(43, 234, 40));
	classic_head.setString("CLASSIC");
	classic_head.setPosition(sf::Vector2f((width / 2 - 50), 10));

	//container a
	container_a.setSize(sf::Vector2f(a_width, a_height));
	container_a.setFillColor(sf::Color(13, 13, 13));
	container_a.setPosition((1200 - a_width) / 2, a_start);

	//container b
	container_b.setSize(sf::Vector2f(b_width, b_height));
	container_b.setFillColor(sf::Color(50, 50, 50));
	container_b.setPosition((1200 - b_width) / 2, container_a.getPosition().y + container_a.getSize().y + gap + 50);

	//alphabets
	alpha[0].setSize(sf::Vector2f(alp_width, alp_height));
	alpha[0].setFillColor(sf::Color(55, 55, 55));
	alpha[0].setPosition(container_a.getPosition().x + 20, container_a.getPosition().y + 40);

	for (int i = 1; i < 26; i++) {
		alpha[i].setSize(sf::Vector2f(alp_width, alp_height));
		alpha[i].setFillColor(sf::Color(55, 55, 55));
		alpha[i].setPosition(alpha[i - 1].getPosition().x + alpha[i - 1].getSize().x + 5, alpha[i - 1].getPosition().y);
	}

	//text display of wps and accuracy
	wpm_accuracy_text.setFont(font);
	wpm_accuracy_text.setFillColor(sf::Color(190, 190, 190));
	wpm_accuracy_text.setString("WPM:\t\t\t\t");
	wpm_accuracy_text.setPosition(container_a.getPosition().x + 20, container_a.getPosition().y + 3);

	//wps value set
	wpm_value.setFont(font);
	wpm_value.setFillColor(sf::Color(190, 190, 190));
	wpm_value.setString("0");
	wpm_value.setPosition(container_a.getPosition().x + 120, container_a.getPosition().y + 3);

	//alphabet text
	for (int i = 0; i < 26; i++) {
		alpha_text[i].setFont(font);
		alpha_text[i].setFillColor(sf::Color(0, 0, 0));
		alpha_text[i].setString(static_cast<char>(i + 65));
		alpha_text[i].setPosition(alpha[i].getPosition().x + 5, alpha[i].getPosition().y - 2);
	}
	//exception
	alpha_text[8].setPosition(alpha[8].getPosition().x + 10, alpha[8].getPosition().y - 2);
	alpha_text[22].setPosition(alpha[22].getPosition().x + 1, alpha[22].getPosition().y - 2);
	alpha_text[12].setPosition(alpha[12].getPosition().x + 3, alpha[12].getPosition().y - 2);



	//initialize sentence
	this->set_active_sentence();
	this->set_text_string();
	wpm = 0;

	//underscope
	underscope.setFont(font);
	underscope.setFillColor(sf::Color(241, 235, 60));
	underscope.setString("_");
	underscope.setPosition(active_text[active_letter_index].getPosition().x, active_text[active_letter_index].getPosition().y + 3);
}
Classic::~Classic() {
	//nothing
}

void Classic::classic_run() {

	//keyboard init
	Self_Keyboard key(container_b.getPosition().y + container_b.getSize().y + gap + 50);

	sf::RenderWindow classic_window(sf::VideoMode(width, height), "Classic", sf::Style::None);
	while (classic_window.isOpen())
	{
		sf::Event event;

		while (classic_window.pollEvent(event))
		{
			//checking letter is correct or not
			this->check_letter(event);

			switch (event.type)
			{
			case sf::Event::KeyPressed:
				//keyboard pressed
				if(event.key.code != sf::Keyboard::Escape)
				key.key_pressed(key.keyindex(event.key.code));
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					this->write_accuracy_on_file();
					classic_window.close();
					break;
				}
				//keyboard released		
				key.key_released(key.keyindex(event.key.code));
				break;
			}

		}


		check_color();
		classic_window.clear(sf::Color(25, 25, 25));
		this->classic_draw(classic_window);
		//keyboard draw
		key.keyboard_draw(classic_window);
		classic_window.display();

	}

}

void Classic::classic_draw(sf::RenderWindow& classic_window) {
	classic_window.draw(classic_head);
	classic_window.draw(container_a);
	classic_window.draw(container_b);
	classic_window.draw(underscope);
	classic_window.draw(wpm_accuracy_text);
	classic_window.draw(wpm_value);
	for (int i = 0; i < 26; i++) {
		classic_window.draw(alpha[i]);
		classic_window.draw(alpha_text[i]);
	}
	for (int i = 0; i < active_sentence.size(); i++) {
		classic_window.draw(active_text[i]);
	}

}


void Classic::check_color() {
	for (int i = 0; i < 26; i++) {
		//std::cout<<alpha_values[i];
		if (alpha_values[i] >4.5 && alpha_values[i] <5.5) {
			alpha[i].setFillColor(sf::Color(136, 130, 130));
		}
		if (alpha_values[i] >= 5.5 && alpha_values[i] < 6) {
			alpha[i].setFillColor(sf::Color(26, 72, 45));
		}
		else if (alpha_values[i] >= 6 && alpha_values[i] < 7) {
			alpha[i].setFillColor(sf::Color(35, 96, 60));
		}
		else if (alpha_values[i] >= 7 && alpha_values[i] < 8) {
			alpha[i].setFillColor(sf::Color(5, 123, 54));
		}
		else if (alpha_values[i] >= 8 && alpha_values[i] < 9) {
			alpha[i].setFillColor(sf::Color(37, 179, 93));
		}
		else if (alpha_values[i] >= 9 && alpha_values[i] <= 10) {
			alpha[i].setFillColor(sf::Color(14, 218, 97));
		}
		//negative marking
		else if (alpha_values[i] <= 4.5 && alpha_values[i]>4) {
			alpha[i].setFillColor(sf::Color(144, 18, 14));
		}
		else if (alpha_values[i] <= 4 && alpha_values[i] > 3) {
			alpha[i].setFillColor(sf::Color(176, 24, 19));
		}
		else if (alpha_values[i] <= 3 && alpha_values[i] > 2) {
			alpha[i].setFillColor(sf::Color(205, 43, 28));
		}
		else if (alpha_values[i] <= 2 && alpha_values[i] > 1) {
			alpha[i].setFillColor(sf::Color(231, 61, 55));
		}
		else if (alpha_values[i] <= 1 && alpha_values[i] >= 0) {
			alpha[i].setFillColor(sf::Color(244, 35, 29));
		}

	}

}


void Classic::set_active_sentence() {
	words_in_sentence = 1;
	srand(time(0));
	int random = rand() % sentences.size();
	active_sentence = sentences[random];
	sentences.erase(sentences.begin() + random);

	for (int i = 0; i < active_sentence.size(); i++) {
		if (active_sentence.compare(i, 1, " ") == 0) {
			words_in_sentence++;
		}
	}
}


void Classic::set_text_string() {
	active_letter_index = 0;
	letter_correct = 0;
	for (int i = 0; i < active_sentence.size(); i++) {
		active_text[i].setFont(font);
		active_text[i].setFillColor(sf::Color(210, 210, 210));
	}

	//0 index
	active_text[0].setPosition(container_b.getPosition().x + 40, container_b.getPosition().y + 10);
	active_text[0].setString(active_sentence[0]);

	for (int i = 1; i < active_sentence.size(); i++) {

		active_text[i].setString(active_sentence[i]);			//set string
		active_text[i].setPosition(active_text[i - 1].getPosition().x + 17, active_text[i - 1].getPosition().y); // common spacing	for lowercase
		//common spacing for uppercase
		if (isupper(active_sentence[i - 1])) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 20, active_text[i - 1].getPosition().y);
		}

		//exceptions

		if (!active_sentence.compare(i - 1, 1, " ") && active_text[i - 1].getPosition().x >= 950) {
			active_text[i].setPosition(container_b.getPosition().x + 40, active_text[i - 1].getPosition().y + 30);
		}
		else if (!active_sentence.compare(i - 1, 1, "i")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 10, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "'")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 10, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "f")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 11, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "j")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 10, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "l")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 9, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "m")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 25, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "r")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 13, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "t")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 12, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "w")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 24, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "F")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 18, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "G")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 22, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "I")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 10, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "J")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 16, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "L")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 18, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "M")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 24, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "O")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 23, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "Q")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 23, active_text[i - 1].getPosition().y);
		}
		else if (!active_sentence.compare(i - 1, 1, "W")) {
			active_text[i].setPosition(active_text[i - 1].getPosition().x + 30, active_text[i - 1].getPosition().y);
		}

	}
}


void Classic::check_letter(sf::Event& event) {
	if (event.type == sf::Event::TextEntered && event.text.unicode != 27) {

		int a = active_sentence[active_letter_index];		//ascii values of text entered
		//std::cout<<event.text.unicode<<std::endl;
		if (a >= 97 && a <= 122) {
			a -= 97;
		}
		if (a >= 65 && a <= 90) {
			a -= 65;
		}


		if (active_sentence[active_letter_index] == static_cast<char>(event.text.unicode) && letter_correct == 0) {

			active_text[active_letter_index].setFillColor(sf::Color(40, 230, 40));
			active_letter_index++;
			letter_correct = 0;

			//update accuracy of letters
			if (a >= 0 && a < 26 && alpha_values[a] < 10) {
				alpha_values[a] += 1/(alpha_values[a]*2);
			}

			if (active_letter_index == active_sentence.size()) {
				this->timer_stop();
				this->set_active_sentence();
				this->set_text_string();
			}
			//start timer
			if (active_letter_index - 1 == 0) {
				this->timer_start();
			}

		}
		else if (active_sentence[active_letter_index] == static_cast<char>(event.text.unicode) && letter_correct > 0) {
			active_letter_index++;
			letter_correct = 0;

			//update accuracy of letters
			if (a >= 0 && a < 26 && alpha_values[a] < 10) {
				alpha_values[a] += 1 / (alpha_values[a] * 1.5);
			}

			if (active_letter_index == active_sentence.size()) {
				this->timer_stop();
				this->set_active_sentence();
				this->set_text_string();

			}
			//start timer
			if (active_letter_index - 1 == 0) {
				this->timer_start();
			}
		}
		else {
			active_text[active_letter_index].setFillColor(sf::Color(240, 60, 60));
			letter_correct++;

			//update accuracy of letters
			if (a >= 0 && a < 26 && alpha_values[a]>0) {
				alpha_values[a] -= 0.04* alpha_values[a];
			}
		}
	}
	underscope.setPosition(active_text[active_letter_index].getPosition().x, active_text[active_letter_index].getPosition().y + 3);
}

void Classic::write_accuracy_on_file() {
	std::ofstream outfile("data/textfiles/alphabet_values.txt");
	for (int i = 0; i < 26; i++) {
		outfile << alpha_values[i] << std::endl;
	}
	outfile.close();
}

void Classic::timer_start() {
	clock.restart();
}

void Classic::timer_stop() {
	prev_wpm = wpm;
	std::stringstream wpm_s;
	float time = clock.getElapsedTime().asSeconds();
	wpm = (words_in_sentence / time) * 60;
	wpm_s << wpm;
	if (wpm > prev_wpm) {
		wpm_value.setFillColor(sf::Color(86, 198, 46));
		wpm_value.setString(wpm_s.str());
	}
	else if (wpm < prev_wpm) {
		wpm_value.setFillColor(sf::Color(161, 45, 35));
		wpm_value.setString(wpm_s.str());
	}
	else {
		wpm_value.setFillColor(sf::Color(190, 190, 190));
		wpm_value.setString(wpm_s.str());
	}
	clock.restart();

	std::fstream time_file("data/textfiles/time.txt", std::ios::app);
	time_file << time << std::endl;
	time_file.close();

	std::fstream word_file("data/textfiles/word.txt", std::ios::app);
	word_file << words_in_sentence << std::endl;
	word_file.close();


	std::fstream high_file("data/textfiles/highest.txt", std::ios::in);
	high_file >> highest_wpm;
	high_file.close();

	std::fstream high_file_out("data/textfiles/highest.txt", std::ios::out);
	if (wpm > highest_wpm) {
		high_file_out << wpm;
	}
	high_file_out.close();


}
