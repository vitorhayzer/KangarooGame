#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "platforms.hpp"
#include "ladder.hpp"

using namespace std;
using namespace sf;

class Movable{
protected:

	Vector2f position;
	Vector2f velocity;
	RectangleShape body;
	Vector2f bodySize;
	bool isGrounded;
	const int TILE_SIZE = 24;
	bool facing_left = false;

	Clock animation_clock;
	const float FRAME_DURATION = 0.125f;
	IntRect texture_rect = body.getTextureRect();

	Texture texture;
	Sprite sprite;

public:
	int lives;

	Movable();

	Movable(Vector2f position, Vector2f velocity, Vector2f bodySize, int lives){
		this->position = position;
		this->velocity = velocity;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
		this->bodySize = bodySize;
		isGrounded = false;
		this->lives = lives;
	}

	bool testCollision(RenderWindow *rWindow){ //with window

		position = body.getPosition();
		if((position.x + body.getSize().x) >= 480.f || position.x <= 0 || (position.y + body.getSize().y) >= 552 || position.y <= 0){
			cout << "não ta na janela" << endl;
			return true;
		}else{
			return false;
		}
	}

	bool testCollision(RectangleShape object){
		position = body.getPosition();
		if(body.getGlobalBounds().intersects(object.getGlobalBounds())){
			return true;
		}
		else{
			return false;
		}
	}

	void isFloating(vector<Platform*> platforms, vector<Ladder*> ladders){

		FloatRect testDummy = body.getGlobalBounds();
		testDummy.top += 5;
		int i = 0;
		if((testDummy.top + testDummy.height) <= 552){
			for(auto &platform : platforms)
				if(platform->getBody().getGlobalBounds().intersects(testDummy) && platform->solid)
					i++;
			for(auto &ladder : ladders)
				if((ladder->getBody().getGlobalBounds().intersects(testDummy)) && ladder->halfSolid)
					i++;

			if(i==0)
				isGrounded = false;
		}
	}

	float deltaTimeGetter(){
		static auto last_frame_time = chrono::steady_clock::now();
		auto current_frame_time = chrono::steady_clock::now();

		chrono::duration<float> delta = current_frame_time - last_frame_time;
		last_frame_time = current_frame_time;

		return delta.count();
	}

	void loadTexture(string filename){
		if (!texture.loadFromFile(filename)){
			std::cerr << "Unable to open \"audio/04-angel_island_zone-act_2.ogg\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		body.setTexture(&texture);
	}

	void changeSpriteTextures(){
		sprite.setPosition(position);

		texture_rect.width = TILE_SIZE;
		texture_rect.height = TILE_SIZE;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			texture_rect.top = 0;
			updateSpritesheetPosition(TILE_SIZE * 2);
		}
		else if(velocity.y < 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 5;
		}
		else if(velocity.y > 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 6;
		}
		else{
			texture_rect.left = 0;
			texture_rect.top = 0;
		}
		sprite.setTextureRect(texture_rect);
		sprite.setScale(facing_left ? -2.0f : 2.0f, 2.0f);
	}

	void setOriginMiddle(){
		Vector2f sizeBody = body.getSize();
		body.setOrigin(sizeBody.x / 2, sizeBody.y / 2);
	}

	bool updateSpritesheetPosition(int first_frame){
		int final_frame = first_frame + TILE_SIZE;

		if(animation_clock.getElapsedTime().asSeconds() > FRAME_DURATION){
			if(texture_rect.left == first_frame){
				texture_rect.left = final_frame;
			}
			else{
				texture_rect.left = first_frame;
			}

			animation_clock.restart();
			return true;
		}
		return false;
	}

	void setFacingLeft(bool left){
		facing_left = left;
	}

	void setVelocity(const Vector2f& velocity){
		this->velocity = velocity;
	}

	void setPosition(const Vector2f& position){
		this->position = position;
		body.setPosition(this->position);
	}

	void setScale(int x, int y){
		body.setScale(Vector2f(x,y));
	}

	void setTexture(Texture& texture){
		texture_rect.top = 0;
		texture_rect.left = 0;
		texture_rect.width = 12;
		texture_rect.height = 12;
		body.setTexture(&texture, true);
		body.setTextureRect(texture_rect);
		sprite.setTexture(texture);
		sprite.setTextureRect(texture_rect);
	}

	bool isFacingLeft(){
		return facing_left;
	}

	Vector2f getPosition(){
		return position;
	}

	Vector2f getVelocity(){
		return velocity;
	}

	RectangleShape getBody(){
		return body;
	}

	void draw(RenderWindow *window){
		if(facing_left == true){
			sprite.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width * 0.5), sprite.getPosition().y);
		}
		window->draw(sprite);
//		window->draw(body);
	}

	void update(RenderWindow *rWindow, float deltaTime){
		Vector2f movement(velocity.x * deltaTime, velocity.y * deltaTime);
		body.move(movement);
		position = body.getPosition();
		sprite.setPosition(position);
//		changeSpriteTextures();
		draw(rWindow);
	}
};
#endif /* MOVABLE_HPP_ */
