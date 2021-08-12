#include"keyboard.h"
#include<iostream>
#include <string>
//------------------------------------------keyboard--------------------------------------
Self_Keyboard::Self_Keyboard(float keyboard_start) {
	float keyboard_width = 1100, keyboard_height = 275, keyx = 43, keyy = 43, gap = 3;
	if (!keyfont.loadFromFile("data/font/times.ttf"))
	{
		std::cout << "font not loaded";
	}

	std::string keyletter[85] = {
			"~\n`" ,"1","2","3","4","5","6","7","8","9","0","-","=","Back",
			"Tab", "Q", "W","E","R","T","Y", "U","I", "O","P","[","]","\\",
			"Caps","A","S","D","F","G","H","J","K","L",";","'","Enter",
			"Shift","Z","X","C","V","B","N","M",",",".","/","Shift",
			"Ctrl","Alt","Space","Alt","Ctrl",
			"Insert","Home","Pg\nup","Del","End","Pg\ndn",
			"","","","",
			"Num","/","*","-",
			"7","8","9","+",
			"4","5","6",
			"1","2","3","Ent",
			"0","."
	};

	container.setSize(sf::Vector2f(keyboard_width, keyboard_height));
	container.setFillColor(sf::Color(73, 68, 68));
	container.setPosition((1200 - keyboard_width) / 2, keyboard_start);

	int a = 0;
	key[a].setSize(sf::Vector2f(keyx, keyy));
	key[a].setFillColor(sf::Color(54, 54, 54));
	key[a].setPosition(container.getPosition().x + 20, container.getPosition().y + 20);

	letter[0].setFont(keyfont);
	letter[0].setCharacterSize(24);
	letter[0].setFillColor(sf::Color(125, 112, 117));
	letter[0].setString(keyletter[0]);
	letter[0].setPosition(key[0].getPosition().x, key[0].getPosition().y);


	for (int i = 1; i <= 84; i++) {
		key[i].setSize(sf::Vector2f(keyx, keyy));
		key[i].setFillColor(sf::Color(54, 54, 54));
		//coloring
		if (i == 13 || i == 14 || i == 28 || i == 40 || i == 41 || i == 52 || i == 53 || i == 54 || i == 56 || i == 57) {
			key[i].setFillColor(sf::Color(41, 41, 41));
		}

		//different size of keys
//backspace
		if (i == 13) {
			key[i].setSize(sf::Vector2f(keyx * 2, keyy));
		}
		//tab
		if (i == 14) {
			key[i].setSize(sf::Vector2f(keyx * 1.5, keyy));
		}
		//frontslash
		if (i == 27) {
			key[i].setSize(sf::Vector2f(keyx * 1.5, keyy));
		}
		//capslock
		if (i == 28) {
			key[i].setSize(sf::Vector2f(keyx * 1.8, keyy));
		}
		//enter
		if (i == 40) {
			key[i].setSize(sf::Vector2f(keyx * 2.3 - 1.5, keyy));
		}
		//lshift
		if (i == 41) {
			key[i].setSize(sf::Vector2f(keyx * 2.3, keyy));
		}
		//rshift
		if (i == 52) {
			key[i].setSize(sf::Vector2f(keyx * 2.8 + 1.5, keyy));
		}
		//ctrl and alt
		if (i == 53 || i == 54 || i == 56 || i == 57) {
			key[i].setSize(sf::Vector2f(keyx * 1.5, keyy));
		}
		//space
		if (i == 55) {
			key[i].setSize(sf::Vector2f(keyx * 9 + gap * 9, keyy));
		}
		//numpad plus + and enter
		if (i == 75 || i == 82) {
			key[i].setSize(sf::Vector2f(keyx, keyy * 2 + gap));
		}
		//numpad 0
		if (i == 83) {
			key[i].setSize(sf::Vector2f(keyx * 2 + gap, keyy));
		}


		//set position
		key[i].setPosition(key[i - 1].getPosition().x + key[i - 1].getSize().x + gap, key[i - 1].getPosition().y);

		//newrow in basic keys
		if (i == 14 || i == 28 || i == 41 || i == 53) {
			key[i].setPosition(key[0].getPosition().x, key[i - 1].getPosition().y + key[i - 1].getSize().y + gap);
		}
		//special keys
		if (i == 58) {
			key[i].setPosition(key[13].getPosition().x + key[13].getSize().x + 20, container.getPosition().y + 20);
		}
		if (i == 61) {
			key[i].setPosition(key[27].getPosition().x + key[27].getSize().x + 20, key[i - 1].getPosition().y + key[i - 1].getSize().y + gap);
		}

		//arrow keys
		if (i == 64) {
			key[i].setPosition(key[52].getPosition().x + key[52].getSize().x + 20 + gap + keyx, key[i - 1].getPosition().y + key[i - 1].getSize().y + gap * 2 + keyy);
		}
		if (i == 65) {
			key[i].setPosition(key[57].getPosition().x + key[57].getSize().x + 20, key[i - 1].getPosition().y + key[i - 1].getSize().y + gap);
		}

		//numpad
		if (i == 68) {
			key[i].setPosition(key[60].getPosition().x + key[60].getSize().x + 20, container.getPosition().y + 20);
		}
		if (i == 72 || i == 76 || i == 79 || i == 83) {
			key[i].setPosition(key[60].getPosition().x + key[60].getSize().x + 20, key[i - 1].getPosition().y + keyy + gap);
		}


		//letters
		letter[i].setFont(keyfont);
		letter[i].setCharacterSize(22);
		letter[i].setFillColor(sf::Color(125, 122, 117));
		letter[i].setString(keyletter[i]);
		letter[i].setPosition(key[i].getPosition().x + key[i].getSize().x / 2 - letter[i].getCharacterSize() / 2, key[i].getPosition().y + key[i].getSize().y / 2 - letter[i].getCharacterSize() / 2 - 2);

		if (i == 13 || i == 14 || i == 27 || i == 28 || i == 40 || i == 41 || i == 52 || i == 53 || i == 54 || i == 55 || i == 56 || i == 57 || i == 82) {
			letter[i].setPosition(key[i].getPosition().x + (key[i].getSize().x / 2) - (keyletter[i].length() - 1) * letter[i].getCharacterSize() / 2 + 10, key[i].getPosition().y + key[i].getSize().y / 2 - letter[i].getCharacterSize() / 2);

		}
		if (i == 68 || i >= 58 && i <= 63) {
			letter[i].setCharacterSize(17);
			letter[i].setPosition(key[i].getPosition().x + key[i].getSize().x / 2 - letter[i].getCharacterSize() / 2 - 10, key[i].getPosition().y + key[i].getSize().y / 2 - letter[i].getCharacterSize() / 2);

		}
		if (i == 60 || i == 63) {
			letter[i].setCharacterSize(16);
			letter[i].setPosition(key[i].getPosition().x + key[i].getSize().x / 2 - letter[i].getCharacterSize() / 2 - 5, key[i].getPosition().y + 3);
		}
		letter[59].setCharacterSize(16);
		std::wstring a[4] = { L"\u2191",L"\u2190",L"\u2193",L"\u2192" };
		letter[64].setString(a[0]);
		letter[65].setString(a[1]);
		letter[66].setString(a[2]);
		letter[67].setString(a[3]);



	}



}
Self_Keyboard::~Self_Keyboard() {
	//nothing
}
int Self_Keyboard::keyindex(int code) {
	if (code == 54) {
		return 0;
	}
	if (code >= 27 && code <= 35) {
		return code - 26;
	}
	if (code == 26) {
		return 10;
	}
	if (code == 56) {
		return 11;
	}
	if (code == 55) {
		return 12;
	}
	if (code == 59) {
		return 13;
	}
	if (code == 60) {
		return 14;
	}
	if (code == 16) {
		return 15;
	}
	if (code == 22) {
		return 16;
	}
	if (code == 4) {
		return 17;
	}
	if (code == 17) {
		return 18;
	}
	if (code == 19) {
		return 19;
	}
	if (code == 24) {
		return 20;
	}
	if (code == 20) {
		return 21;
	}
	if (code == 8) {
		return 22;
	}
	if (code == 14) {
		return 23;
	}
	if (code == 15) {
		return 24;
	}
	if (code == 46) {
		return 25;
	}
	if (code == 47) {
		return 26;
	}
	if (code == 53) {
		return 27;
	}
	if (code == -1) {
		return 28;
	}
	if (code == 0) {
		return 29;
	}
	if (code == 18) {
		return 30;
	}
	if (code == 3) {
		return 31;
	}
	if (code == 5) {
		return 32;
	}
	if (code == 6) {
		return 33;
	}
	if (code == 7) {
		return 34;
	}
	if (code == 9) {
		return 35;
	}
	if (code == 10) {
		return 36;
	}
	if (code == 11) {
		return 37;
	}
	if (code == 48) {
		return 38;
	}
	if (code == 51) {
		return 39;
	}
	if (code == 58) {
		return 40;
	}
	if (code == 38) {
		return 41;
	}
	if (code == 25) {
		return 42;
	}
	if (code == 23) {
		return 43;
	}
	if (code == 2) {
		return 44;
	}
	if (code == 21) {
		return 45;
	}
	if (code == 1) {
		return 46;
	}
	if (code == 13) {
		return 47;
	}
	if (code == 12) {
		return 48;
	}
	if (code == 49) {
		return 49;
	}
	if (code == 50) {
		return 50;
	}
	if (code == 52) {
		return 51;
	}
	if (code == 42) {
		return 52;
	}
	if (code == 37) {
		return 53;
	}
	if (code == 39) {
		return 54;
	}
	if (code == 57) {
		return 55;
	}
	if (code == 43) {
		return 56;
	}
	if (code == 41) {
		return 57;
	}

	//arrow
	if (code == 73) {
		return 64;
	}
	if (code == 71) {
		return 65;
	}
	if (code == 74) {
		return 66;
	}
	if (code == 72) {
		return 67;
	}

	//numpad
	//numlock =555
	if (code == 555) {
		return 68;
	}
	if (code == 70) {
		return 69;
	}
	if (code == 69) {
		return 70;
	}
	if (code == 68) {
		return 71;
	}
	if (code == 82) {
		return 72;
	}
	if (code == 83) {
		return 73;
	}
	if (code == 84) {
		return 74;
	}
	if (code == 67) {
		return 75;
	}
	if (code == 79) {
		return 76;
	}
	if (code == 80) {
		return 77;
	}
	if (code == 81) {
		return 78;
	}
	if (code == 75) {
		return 83;
	}
	if (code == 76) {
		return 79;
	}
	if (code == 77) {
		return 80;
	}
	if (code == 78) {
		return 81;
	}
	if (code == 58) {
		return 40;
	}
	if (code == 66) {
		return 84;
	}
	else {
		return code;
	}

}

void Self_Keyboard::key_pressed(int index) {

	key[index].setFillColor(sf::Color(221, 221, 221));

}

void Self_Keyboard::key_released(int i) {

	key[i].setFillColor(sf::Color(54, 54, 54));
	//coloring
	if (i == 13 || i == 14 || i == 28 || i == 40 || i == 41 || i == 52 || i == 53 || i == 54 || i == 56 || i == 57) {
		key[i].setFillColor(sf::Color(41, 41, 41));
	}

}



void Self_Keyboard::keyboard_draw(sf::RenderWindow& window) {
	window.draw(container);
	for (int i = 0; i <= 84; i++) {
		window.draw(key[i]);
		window.draw(letter[i]);
	}

}