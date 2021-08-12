#include "User.h"
#include<iostream>

User::User() {
	time_val = 0;
	word_val = 0;
	int a_width = 300, a_height = 50, a_start = 300;
	temp = 0;
	if (!font.loadFromFile("data/font/arial3.ttf"))
	{
		// handle error
	}
	float width = 1200, height = 900;
	//std::cout << "user\n";
	user_head.setFont(font);
	user_head.setFillColor(sf::Color(43, 234, 40));
	user_head.setString("USER");
	user_head.setPosition(sf::Vector2f((width / 2 - 50), 10));


	avg_t.setFont(font);
	avg_t.setFillColor(sf::Color(141, 210, 104));
	avg_t.setString("Avg  WPM :");
	avg_t.setPosition(sf::Vector2f(50, 100));

	high_t.setFont(font);
	high_t.setFillColor(sf::Color(141, 210, 104));
	high_t.setString("Highest WPM :");
	high_t.setPosition(sf::Vector2f(50, 150));

	time_t.setFont(font);
	time_t.setFillColor(sf::Color(141, 210, 104));
	time_t.setString("Total time spent :\t\t\t hr\t    min\t   sec");
	time_t.setPosition(sf::Vector2f(50, 200));

	rapid_t.setFont(font);
	rapid_t.setFillColor(sf::Color(141, 210, 104));
	rapid_t.setString("Rapid HighScore :");
	rapid_t.setPosition(sf::Vector2f(50, 250));


	//reset box
	reset_box.setSize(sf::Vector2f(a_width, a_height));
	reset_box.setFillColor(sf::Color(141, 210, 104));
	reset_box.setPosition((1200 - a_width) / 2, a_start);

	//reset text
	
	reset_text.setFont(font);
	reset_text.setFillColor(sf::Color(128,0,0));
	reset_text.setString("Press Enter to Reset");
	reset_text.setPosition(reset_box.getPosition().x + (reset_box.getSize().x / 2) - 135, reset_box.getPosition().y + (reset_box.getSize().y / 2) - 20);

	this->set_values();
}
User::~User() {
	//nothing
}

void User::user_run() {
	sf::RenderWindow user_window(sf::VideoMode(1200, 900), "user", sf::Style::None);
	while (user_window.isOpen())
	{
		sf::Event event;

		while (user_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					user_window.close();
					break;

				case sf::Keyboard::Return:
					this->reset_files();
					break;
				}
			}

		}
		user_window.clear(sf::Color(13, 13, 13));

		this->user_draw(user_window);

		user_window.display();
	}
}


void User::user_draw(sf::RenderWindow& user_window) {
	user_window.draw(user_head);
	user_window.draw(avg_t);
	user_window.draw(high_t);
	user_window.draw(time_t);
	user_window.draw(high_text);
	user_window.draw(avg_text);
	user_window.draw(time_h_text);
	user_window.draw(time_m_text);
	user_window.draw(time_s_text);
	user_window.draw(reset_box);
	user_window.draw(reset_text);
	user_window.draw(rapid_t);
	user_window.draw(rapid_text);
}

void User::reset_files() {
	int res = 0;
	std::fstream high_file_out("data/textfiles/highest.txt", std::ios::out);
	high_file_out << res;
	high_file_out.close();

	std::fstream time_file_out("data/textfiles/time.txt", std::ios::out);
	time_file_out << res;
	time_file_out.close();

	std::fstream word_file_out("data/textfiles/word.txt", std::ios::out);
	word_file_out << res;
	word_file_out.close();

	std::fstream rapid_highest("data/textfiles/rapid_highest.txt", std::ios::out);
	rapid_highest << res;
	rapid_highest.close();

	res = 5;
	std::fstream accuracy_file_out("data/textfiles/alphabet_values.txt", std::ios::out);
	for (int i = 0; i < 26; i++) {
		accuracy_file_out << res << std::endl;
	}
	accuracy_file_out.close();

	this->set_values();

}

void User::set_values() {

	std::stringstream wpm_s, avg_s, time_hr_s, time_min_s, time_sec_s, rapid_s;
	time_val = 0;

	//average
	std::fstream time_file("data/textfiles/time.txt", std::ios::in);
	while (!time_file.eof()) {
		time_file >> temp;
		time_val += temp;
	}
	time_file.close();

	std::fstream word_file("data/textfiles/word.txt", std::ios::in);
	while (!word_file.eof()) {
		word_file >> temp;
		word_val += temp;
	}
	word_file.close();
	if (time_val != 0) {
		avg_val = (word_val / time_val) * 60;
	}
	else {
		avg_val = 0;
	}

	avg_s << avg_val;
	avg_text.setFont(font);
	avg_text.setFillColor(sf::Color(141, 210, 104));
	avg_text.setString(avg_s.str());
	avg_text.setPosition(sf::Vector2f(360, avg_t.getPosition().y));



	//highest
	std::fstream high_file("data/textfiles/highest.txt", std::ios::in);
	high_file >> highest_wpm;
	high_file.close();

	wpm_s << highest_wpm;
	high_text.setFont(font);
	high_text.setFillColor(sf::Color(141, 210, 104));
	high_text.setString(wpm_s.str());
	high_text.setPosition(sf::Vector2f(360, high_t.getPosition().y));

	//total time spent
	total = time_val;
	hour = (total / 3600);
	time_hr_s << hour;

	total = total - hour*3600;
	min = total / 60;
	time_min_s << min;

	total =total - min * 60;
	sec = total;
	time_sec_s << sec;


	time_h_text.setFont(font);
	time_h_text.setFillColor(sf::Color(141, 210, 104));
	time_h_text.setString(time_hr_s.str());
	time_h_text.setPosition(sf::Vector2f(360, time_t.getPosition().y));

	time_m_text.setFont(font);
	time_m_text.setFillColor(sf::Color(141, 210, 104));
	time_m_text.setString(time_min_s.str());
	time_m_text.setPosition(sf::Vector2f(time_h_text.getPosition().x+80, time_t.getPosition().y));


	time_s_text.setFont(font);
	time_s_text.setFillColor(sf::Color(141, 210, 104));
	time_s_text.setString(time_sec_s.str());
	time_s_text.setPosition(sf::Vector2f(time_m_text.getPosition().x + 100, time_t.getPosition().y));

	//rapid highscore
	std::fstream rapid_high_file("data/textfiles/rapid_highest.txt", std::ios::in);
	rapid_high_file >> rapid_high;
	rapid_high_file.close();

	rapid_s << rapid_high;
	rapid_text.setFont(font);
	rapid_text.setFillColor(sf::Color(141, 210, 104));
	rapid_text.setString(rapid_s.str());
	rapid_text.setPosition(sf::Vector2f(360, rapid_t.getPosition().y));




}