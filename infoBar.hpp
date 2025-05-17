/*
 * infoBar.hpp
 *
 *  Created on: 4 de out. de 2024
 *      Author: vitor
 */

#ifndef INFOBAR_HPP
#define INFOBAR_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class InfoBar {
public:
	InfoBar();
	~InfoBar();

	void draw(RenderWindow *window);
	void InfoBarUpdate(int lives, int points, int level);
	std::string toString(int value);

	int const static IBmaxNumbersOfItems = 3;
	int Level = 0, Points = 0, Lives = 0;
	Font font;
	Text infoBar[IBmaxNumbersOfItems];
	RenderWindow window;
};

#endif // INFOBAR_HPP



//#include <SFML/Graphics.hpp>
//#include <string>
//#include <sstream>
//#include "game.hpp"
//
//class InfoBar {
//public:
//    InfoBar(const sf::Font& font);
//
//    void update(int lives, int points, int level);
//    void draw(sf::RenderWindow& window);
//
//private:
//    sf::Text livesText;
//    sf::Text pointsText;
//    sf::Text levelText;
//
//    template<typename T>
//    std::string toString(const T& value);
//};
