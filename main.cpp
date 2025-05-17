#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "movable.hpp"
#include "player.HPP"
#include "game.hpp"
#include "menu.hpp"

using namespace std;
using namespace sf;

int main(){

	Menu menu;
	Game game1(menu.getPointWindow());

	if(menu.start())
		game1.run();

	cout << "Game close" << endl;
	return 0;
}
