#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Platform{
public:
	Vector2f position;
	RectangleShape block;
	const int BLOCK_SIZE = 12;
	bool solid;

	Texture texture;
	Sprite sprite;

	Platform(Vector2f position, Vector2f blockSize){
		loadTexture("spritesheets/tileset.png");
		this->position = position;
		this->block.setPosition(this->position);
		this->block.setSize(blockSize);
		solid = true;
		block.setFillColor(Color::Transparent);
		block.setTexture(&texture);
		sprite.setTexture(texture);
		sprite.setPosition(position);
	}

	void setTexture(const Texture& texture){
		block.setTexture(&texture);
	}

	void loadTexture(std::string filename){
		if (!texture.loadFromFile(filename)){
			cout << "Failed to load texture from " << filename << std::endl;
		}
		block.setTexture(&texture);
	}

	void assignTexture(char type) {
	    IntRect texture_rect;
	    texture_rect.width = BLOCK_SIZE;
	    texture_rect.height = BLOCK_SIZE;

	    switch (type) {
	        // tree trunks
	        case 'T':
	            texture_rect.top = BLOCK_SIZE * 3;
	            texture_rect.left = 0;
	            break;
	        case 't':
	            texture_rect.top = BLOCK_SIZE * 3;
	            texture_rect.left = BLOCK_SIZE;
	            break;
	        case 'C':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = 0;
	            break;
	        case 'c':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = BLOCK_SIZE;
	            break;
	        case 'D':
	            texture_rect.top = BLOCK_SIZE * 3;
	            texture_rect.left = BLOCK_SIZE * 3;
	            break;
	        case 'd':
	            texture_rect.top = BLOCK_SIZE * 3;
	            texture_rect.left = BLOCK_SIZE * 4;
	            break;

	        // main leaf texture
	        case 'L':
	            texture_rect.top = BLOCK_SIZE * 2;
	            texture_rect.left = BLOCK_SIZE * 16;
	            break;

	        // no background leaves
	        case '1':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = BLOCK_SIZE * 14;
	            break;
	        case '2':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = BLOCK_SIZE * 16;
	            break;
	        case '3':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = BLOCK_SIZE * 18;
	            break;
	        case '4':
	            texture_rect.top = BLOCK_SIZE * 2;
	            texture_rect.left = BLOCK_SIZE * 14;
	            break;

	        // leaves + trees
	        case '@':
	            texture_rect.top = BLOCK_SIZE * 4;
	            texture_rect.left = BLOCK_SIZE * 28;
	            break;
	        case '&':
	            texture_rect.top = 0;
	            texture_rect.left = BLOCK_SIZE * 26;
	            break;
	        case '*':
	            texture_rect.top = 0;
	            texture_rect.left = BLOCK_SIZE * 28;
	            break;
	        case '(':
	            texture_rect.top = 0;
	            texture_rect.left = BLOCK_SIZE * 30;
	            break;

	        // ladders
	        case 'v':
	            texture_rect.top = BLOCK_SIZE * 2;
	            texture_rect.left = BLOCK_SIZE;
	            break;
	        case 'V':
	            texture_rect.top = BLOCK_SIZE * 2;
	            texture_rect.left = 0;
	            break;

	        // suspended platforms
	        case 's':
	            texture_rect.top = BLOCK_SIZE * 5;
	            texture_rect.left = BLOCK_SIZE * 2;
	            solid = false;
	            break;
	        case 'l':
	            texture_rect.top = BLOCK_SIZE * 6;
	            texture_rect.left = BLOCK_SIZE * 2;
	            solid = false;
	            break;
	        case 'm':
	            texture_rect.top = BLOCK_SIZE * 6;
	            texture_rect.left = BLOCK_SIZE * 3;
	            break;
	        case 'r':
	            texture_rect.top = BLOCK_SIZE * 6;
	            texture_rect.left = BLOCK_SIZE * 4;
	            break;

	        // interface barrier
	        case 'I':
	            texture_rect.top = 0;
	            texture_rect.left = BLOCK_SIZE * 3;
	            break;

	        case 'b':
	            texture_rect.top = 0;
	            texture_rect.left = BLOCK_SIZE;
	            break;
	        case '-':
	            break;
	    }

	    block.setTextureRect(texture_rect);
	    sprite.setTextureRect(texture_rect);
	}

	void draw(RenderWindow* window){
		sprite.setScale(2.0f, 2.0f);
		window->draw(sprite);
	}

	RectangleShape getBody(){
		return block;
	}

	FloatRect getBounds() const{
		return block.getGlobalBounds();
	}
};

#endif // PLATFORM_H
