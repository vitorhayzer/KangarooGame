/*
 * infoBar.cpp
 *
 *  Created on: 4 de out. de 2024
 *      Author: vitor
 */
#include "infoBar.hpp"

using namespace sf;

InfoBar::InfoBar() {
	if (!font.loadFromFile("fonts/Pingsan.ttf")) {
		std::cerr << "Unable to open \"fonts/Pingsan.ttf\"" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	infoBar[0].setFont(font);
	infoBar[0].setFillColor(Color { 0xDADA91FF }); // branco
	infoBar[0].setString("Points:");
	infoBar[0].setPosition(Vector2f(10, 25));

	infoBar[1].setFont(font);
	infoBar[1].setFillColor(Color { 0xDADA91FF }); // branco
	infoBar[1].setString("Level:");
	infoBar[1].setPosition(Vector2f(180, 25));

	infoBar[2].setFont(font);
	infoBar[2].setFillColor(Color { 0xDADA91FF }); // branco
	infoBar[2].setString("Lives:");
	infoBar[2].setPosition(Vector2f(330, 25));
}

InfoBar::~InfoBar() {
}

void InfoBar::draw(RenderWindow *window) {
	for (int i = 0; i < IBmaxNumbersOfItems; i++) {
		window->draw(infoBar[i]);
	}
}

void InfoBar::InfoBarUpdate(int lives, int points, int level) {
	Lives = lives;
	Points = points;
	Level = level;

	infoBar[0].setString("Points: " + toString(Points));
	infoBar[1].setString("Level: " + toString(Level));
	infoBar[2].setString("Lives: " + toString(Lives));
}

std::string InfoBar::toString(int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}




//bool Menu::start(){
//
//	while(window.isOpen()){
//		Event event;
//
//		while(window.pollEvent(event)){
//
//			switch(event.type){
//			case Event::KeyReleased:
//				switch(event.key.code){
//				case Keyboard::Escape:
//					window.close();
//					break;
//				case Keyboard::Up :
//					moveUp();
//					break;
//				case Keyboard::Down:
//					moveDown();
//					break;
//				case Keyboard::Return:
//					switch(getPressedItem()){
//					case 0:
//						return true;
//						break;
//					case 1:
//						window.close();
//						break;
//					}
//					break;
//				}
//				break;
//				case Event::Closed:
//					window.close();
//					break;
//			}
//		}
//
//		window.clear();
//		window.draw(sprite);
//		draw(window);
//		window.display();
//	}
//	return false;
//}









//InfoBar::InfoBar(const sf::Font& font) {
//
//    livesText.setFont(font);
//    pointsText.setFont(font);
//    levelText.setFont(font);
//
//    livesText.setCharacterSize(24);
//    pointsText.setCharacterSize(24);
//    levelText.setCharacterSize(24);
//
//    livesText.setFillColor(sf::Color::White);
//    pointsText.setFillColor(sf::Color::White);
//    levelText.setFillColor(sf::Color::White);
//
//    livesText.setPosition(10, 10);
//    pointsText.setPosition(10, 40);
//    levelText.setPosition(10, 70);
//}
//
//void InfoBar::update(int lives, int points, int level) {
//    livesText.setString("Lives: " + toString(lives));
//    pointsText.setString("Points: " + toString(points));
//    levelText.setString("Level: " + toString(level));
//}
//
//void InfoBar::draw(sf::RenderWindow& window) {
//    window.draw(livesText);
//    window.draw(pointsText);
//    window.draw(levelText);
//}
//
//template<typename T>
//std::string InfoBar::toString(const T& value) {
//    std::ostringstream oss;
//    oss << value;
//    return oss.str();
//}




