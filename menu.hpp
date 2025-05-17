#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Menu{
public:
	Menu();
	~Menu();

	bool start();
	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem(){return selectedItemIndex;}
	RenderWindow* getPointWindow(){return &window;}

	// private:
	int const static maxNumbersOfItems = 3;
	int selectedItemIndex;
	Font font;
	Text menu[maxNumbersOfItems];
	Texture texture;
	RenderWindow window;
	Sprite sprite;
};

#endif /* MENU_HPP_ */
