#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <chrono>
#include <Vector>

#include "movable.hpp"
#include "opossum.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Player: public Movable {
public:
	bool hasGloves = true;
	bool tryingCrouching;
	bool isCrouching;
	bool isPunching;
	bool tryingPunching;
	bool isClimbing;
	bool tryingClimb;
	bool bouncingFrame;

	SoundBuffer jump_buffer;
	Sound jump_sound;

	SoundBuffer punch_buffer;
	Sound punch_sound;

	SoundBuffer damageBuffer;
	Sound damageSound;

	SoundBuffer crouchBuffer;
	Sound crouchSound;

	Clock punch_clock;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize) :
		Movable(position, velocity, bodySize, 3) {
		loadTexture("spritesheets/kangaroo.png");
		sprite.setTexture(texture);
		body.setFillColor(Color::White);
		this->bodySize = bodySize;
		tryingCrouching = false;
		isCrouching = false;
		isPunching = false;
		tryingPunching = false;
		isClimbing = false;
		tryingClimb = false;
		bouncingFrame = false;

		jump_buffer.loadFromFile("audio/player_jump_S3K_62.wav");
		jump_sound.setBuffer(jump_buffer);

		punch_buffer.loadFromFile("audio/player_punch_S3K_4F.wav");
		punch_sound.setBuffer(punch_buffer);

		if(!damageBuffer.loadFromFile("audio/player_damage_S3K_6E.wav")){
			std::cerr << "Unable to open \"audio/player_damage_S3K_6E.wav\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		damageSound.setBuffer(damageBuffer);

		if(!crouchBuffer.loadFromFile("audio/player_crouch_S3K_3A.wav")){
			std::cerr << "Unable to open \"audio/player_crouch_S3K_3A.wav\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		crouchSound.setBuffer(crouchBuffer);
	}

	void changeSpriteTextures(){

		if(isClimbing){

			texture_rect.top = TILE_SIZE;

			if(updateSpritesheetPosition(TILE_SIZE * 4) && !bouncingFrame)
				bouncingFrame = true;

		}else if(!isCrouching && !isPunching){
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
		}
		sprite.setScale(facing_left ? -2.0f : 2.0f, 2.0f);
	}

	void changeHitBoxSize() {
		sprite.setPosition(body.getPosition());

		if(isClimbing && !bouncingFrame){
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 4;
			bouncingFrame = true;

		} else if(!tryingCrouching && isCrouching){

			texture_rect.width = TILE_SIZE;
			texture_rect.height = TILE_SIZE;

			body.setOrigin(0,bodySize.y / 2);
			body.setSize(Vector2f(bodySize.x,bodySize.y));
			body.setOrigin(0,0);
			body.setPosition(position.x, position.y - (bodySize.y/2));

			isCrouching = false;

		} else if (tryingCrouching && !isCrouching) {

			texture_rect.top = TILE_SIZE * 1.5;
			texture_rect.left = 0;
			texture_rect.height = TILE_SIZE / 2;

			body.setOrigin(0,bodySize.y / 2);
			body.setSize(Vector2f(bodySize.x,bodySize.y/2));
			body.setOrigin(0,body.getOrigin().y-body.getSize().y);
			body.setPosition(position.x, position.y + (body.getSize().y));

			isCrouching = true;

			crouchSound.play();

		} else if ((tryingPunching || isPunching) && !isCrouching) {
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 2;
			texture_rect.width = TILE_SIZE * 1.5;

			if(facing_left)
				sprite.setPosition(body.getPosition().x - TILE_SIZE, body.getPosition().y);
		}
		sprite.setTextureRect(texture_rect);
		position = body.getPosition();
	}

	void punch_timer() {
		if (isPunching) {
			velocity.x = 0;
			if (punch_clock.getElapsedTime().asSeconds()
					>= FRAME_DURATION * 2) {
				isPunching = false;
			}
		}
	}

	bool controls(RenderWindow *rWindow, float deltaTime) {
		tryingCrouching = false;

		if ((Keyboard::isKeyPressed(Keyboard::A)
				|| Keyboard::isKeyPressed(Keyboard::Left))) {
			velocity.x = TILE_SIZE * -6;
			facing_left = true;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)
				|| Keyboard::isKeyPressed(Keyboard::Right)) && !tryingCrouching) {
			velocity.x = TILE_SIZE * 6;
			facing_left = false;
		}

		//crouch
		if ((Keyboard::isKeyPressed(Keyboard::S)
				|| Keyboard::isKeyPressed(Keyboard::Down))) {
			velocity.x = 0;
			if(isGrounded){
				tryingCrouching = true;
			}
			else if(!isGrounded){
				velocity.y += TILE_SIZE * 6;
			}
		}

		//punch
		if ((Keyboard::isKeyPressed(Keyboard::RShift)
				|| Keyboard::isKeyPressed(Keyboard::LShift)) && !tryingCrouching
				&& !isPunching) {
			isPunching = true;
			punch_clock.restart();
			punch_sound.play();
		}

		punch_timer();

		//jump
		if ((Keyboard::isKeyPressed(sf::Keyboard::W)
				|| Keyboard::isKeyPressed(Keyboard::Up)
				|| Keyboard::isKeyPressed(Keyboard::Space)) && velocity.y == 0
				&& !tryingCrouching && isGrounded) {
			velocity.y += TILE_SIZE * -12;
			isGrounded = false;
			jump_sound.play();
		}

		if((Keyboard::isKeyPressed(Keyboard::E) || Keyboard::isKeyPressed(Keyboard::P)) && !tryingCrouching)
			tryingClimb = true;
		else
			tryingClimb = false;

		return true;
	}

	bool move(RenderWindow *rWindow, float deltaTime, vector<Platform*> platforms, vector<Ladder*> ladders){
		float gravity = 2.0f;

		isFloating(platforms, ladders);

		if(!isGrounded){
			velocity.y += gravity;
		}

		if(tryingClimb){
			bool collision = false;
			for(auto &Ladder : ladders){
				if(testCollision(Ladder->getBody())){
					isGrounded = false;
					isClimbing = true;
					collision = true;
				}
			}
			if(collision)
				velocity.y += -4.f;
			else
				isClimbing = false;
		}else{
			isClimbing = false;
		}

		body.move(0.f,velocity.y * deltaTime);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				if(testCollision(platform->getBody()) && platform->solid)
					cout << "colisao plataforma" << endl;
				while(testCollision(rWindow) || (testCollision(platform->getBody()) && platform->solid)){
					if(velocity.y >= 0.f){
						body.move(0.f,-1.f);
					}else{
						body.move(0.f,1.f);
					}
				}

				if(velocity.y >= 0.f)
					isGrounded = true;

				velocity.y = 0.f;
				position = body.getPosition();
			}
		}

		body.move(velocity.x * deltaTime,0.f);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				if(testCollision(platform->getBody()) && platform->solid)
					cout << "colisao plataforma" << endl;
				while(testCollision(rWindow) || (testCollision(platform->getBody()) && platform->solid)){
					if(velocity.x >= 0.f){
						body.move(-1.f,0.f);
					}else{
						body.move(1.f,0.f);
					}
				}
				position = body.getPosition();
			}
		}

		velocity.x = 0;
		return true;
	}

	void updateMovables(vector<Enemy*> enemies, vector<Movable*> apples){
		for(auto& apple : apples){
			if(testCollision(apple->getBody()) && !isPunching){
				lives--;
				apple->lives--;
				damageSound.play();
			}
		}

		for(auto& enemy : enemies){
			if(sprite.getGlobalBounds().intersects(enemy->getBody().getGlobalBounds()) && isPunching){
				enemy->lives--;
			}
		}
	}

	void player_update(RenderWindow *rWindow, vector<Platform*> platforms,vector<Ladder*> ladders, vector<Enemy*> enemies, vector<Movable*> apples, float deltaTime){

		controls(rWindow, deltaTime);
		changeSpriteTextures();
		move(rWindow, deltaTime, platforms, ladders);
		updateMovables(enemies,apples);
		changeHitBoxSize();
		draw(rWindow);
	}
};

#endif /* PLAYER_HPP_ */
