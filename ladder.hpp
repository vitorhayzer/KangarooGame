#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Ladder : public Platform{
public:

	bool halfSolid;

	Ladder();

	Ladder(Vector2f position, Vector2f blockSize)
		: Platform(position, blockSize)
	{
		if(!texture.loadFromFile("spritesheets/tileset.png")){
			std::cerr << "Unable to open \"spritesheets/tileset.png\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		block.setFillColor(Color::Transparent);
		block.setTexture(&texture);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		halfSolid = false;
	}
};

#endif /* LADDER_HPP_ */
