#include "menu.hpp"

using namespace sf;

Menu::Menu(){
	if(!font.loadFromFile("fonts/Pingsan.ttf")){
		std::cerr << "Unable to open \"fonts/Pingsan.ttf\"" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if(!texture.loadFromFile("spritesheets/menu.png")){
		std::cerr << "Unable to open \"spritesheets/menu.png\"" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	window.create(VideoMode(480.f, 552.f), "Rescue The Kangaroo!");
	window.setMouseCursorVisible(false);

	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	menu[0].setFont(font);
	menu[0].setFillColor(Color{0xDA4824FF}); //red
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(480 / 2, 552 / 3 * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color{0xDADA91FF}); //white
	menu[1].setString("Exit");
	menu[1].setPosition(Vector2f(480 / 2, (552 / 3) * 2.3));

	selectedItemIndex = 0;

	//		menu[2].setFont(font);
	//		menu[2].setColor(sf::Color::White);
	//		menu[2].setString("Exit");
	//		menu[2].setPosition(sf::Vector2f(width / 2, height / 4 * 3));
}

bool Menu::start(){

	while(window.isOpen()){
		Event event;

		while(window.pollEvent(event)){

			switch(event.type){
			case Event::KeyReleased:
				switch(event.key.code){
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::Up :
					moveUp();
					break;
				case Keyboard::Down:
					moveDown();
					break;
				case Keyboard::Return:
					switch(getPressedItem()){
					case 0:
						return true;
						break;
					case 1:
						window.close();
						break;
					}
					break;
				}
				break;
				case Event::Closed:
					window.close();
					break;
			}
		}

		window.clear();
		window.draw(sprite);
		draw(window);
		window.display();
	}
	return false;
}

Menu::~Menu(){
}

void Menu::draw(RenderWindow &window){
	for(int i = 0; i < maxNumbersOfItems; i++){
		window.draw(menu[i]);
	}
}

void Menu::moveUp(){
	if(selectedItemIndex - 1 >= 0){
		menu[selectedItemIndex].setColor(Color{0xDADA91FF});
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(Color{0xDA4824FF});
	}
}

void Menu::moveDown(){
	if(selectedItemIndex + 1 < maxNumbersOfItems){
		menu[selectedItemIndex].setColor(Color{0xDADA91FF});
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(Color{0xDA4824FF});
	}
}
