#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "opossum.hpp"
#include "platforms.hpp"
#include "ladder.hpp"
#include "infoBar.hpp"
#include <vector>

using namespace std;
using namespace sf;

class Game{
private:

	Vector2f windowSize;
	Vector2f position;
	Vector2f velocity;
	Vector2f size;
	Player player;
	int level;
	int points;
	InfoBar infoBar;
	RenderWindow * window;

	RectangleShape joey;

	float dificult;

	vector<Platform *> platforms;
	vector<Ladder *> ladders;
	vector<Enemy *> enemies;
	vector<Movable *> apples;
	vector<string> mapMatrix;

	Texture itemsTexture;
	Texture background_texture;
	Sprite background_sprite;

	Music game_theme;
	SoundBuffer enemyShootBuffer;
	Sound enemyShoot;

public:
	Game(RenderWindow* rWindow) :
		windowSize(480, 552),
		position(windowSize.x * 3 / 20, windowSize.y * 19 / 22),
		velocity(0.0f, 0.0f),
		size(48, 48),
		player(position, velocity, size),
		level(0),
		points(0),
		dificult(1.f)
	{
		window = rWindow;

		if(!background_texture.loadFromFile("spritesheets/background.png")){
			std::cerr << "Unable to open \"spritesheets/background.png\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		background_sprite.setTexture(background_texture);
		background_sprite.setScale(2.0f, 2.0f);

		if(!itemsTexture.loadFromFile("spritesheets/items.png")){
			std::cerr << "Unable to open \"spritesheets/items.png\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		defineMapMatrix();
		loadPlatforms();

		if(!game_theme.openFromFile("audio/04-angel_island_zone-act_2.ogg")){
			std::cerr << "Unable to open \"audio/04-angel_island_zone-act_2.ogg\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		if(!enemyShootBuffer.loadFromFile("audio/enemy_throw_S3K_65.wav")){
			std::cerr << "Unable to open \"audio/enemy_throw_S3K_65.wav\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		enemyShoot.setBuffer(enemyShootBuffer);

		joey.setTexture(&itemsTexture, true);
		joey.setSize(Vector2f(48.f,48.f));
		IntRect textureRect;
		textureRect.top = 72;
		textureRect.left = 24;
		textureRect.height = 24;
		textureRect.width = 24;
		joey.setTextureRect(textureRect);
	}

	void defineMapMatrix(){
		int map = level % 3;

		if(map == 0){
			mapMatrix = {
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"LLL3XXXXXXXXXXXX1LLL",
					"@@3XXXXXXXXXXXXXX1@@",
					"DdXXXXXXXXXXXXXXXXDd",
					"TtXXXYXXXXXJXXXXXXDd",
					"TcbbbbbbbbbbbbvvvbCt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"Tt>XXXXXXXXXXXVVVXTt",
					"Tcbvvvbbbbbbbbbb&***",
					"TtXVVVXXXXXXXXXX1LLL",
					"TtXVVVXXXXXXXXXXX1@@",
					"TtXVVVXXXXXXXXXXXXDd",
					"TtXVVVXXXXXXXXXX<XTt",
					"***(bbbbbbbbbbvvvbCt",
					"LLL3XXXXXXXXXXVVVXTt",
					"@@3XXXXXXXXXXXVVVXTt",
					"DdXXXXXXXXXXXXVVVXTt",
					"Tt>XXXXXXXXXXXVVVXTt",
					"--------------------"};
		}
		if(map == 1){
			mapMatrix = {
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"LLL3XXXXXXXXXXXX1LLL",
					"@@3XXXXXXXXXXXXXX1@@",
					"DdXXXXXXXXXXXXXXXXDd",
					"TtXXXYXXXXXJXXXXXXDd",
					"TcbbbbbbbbbbbbvvvbCt",
					"TtXXXXXXXsXsXXsXsXTt",
					"TtXXXXXXXsXsXXsXsXTt",
					"TtXXXXXXXsXsXXsXsXTt",
					"Tt>XXXXXXsXsXXlmrXTt",
					"TcbvvvXXXlmrXXXb&***",
					"TtXsXsXXXXXXXXXX1LLL",
					"TtXsXsXXXXXXXXXXX1@@",
					"TtXlmrXXXXXXXXXXXXDd",
					"TtXXXXXXXXXXXXXX<XTt",
					"***(bbbbbbbXXXvvvbCt",
					"LLL3XXXXXXXXXXsXsXTt",
					"@@3XXXXXXXXXXXsXsXTt",
					"DdXXXXXXXXXXXXlmrXTt",
					"TtX>XXXXXXXXXXXXXXXTt",
					"--------------------"};
		}
		if(map == 2){
			mapMatrix = {
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"IIIIIIIIIIIIIIIIIIII",
					"LLL3XXXXXXXXXXXX1LLL",
					"@@3XXXXXXXXXXXXXX1@@",
					"DdXXXXXXXXXXXXXXXXDd",
					"TtXXXYXXXXXJXXXXXXDd",
					"TcbvvvbbbbbbbbvvvbCt",
					"TtXVVVXXXXXXXXVVVXTt",
					"TtXVVVXXXXXXXXVVVXTt",
					"TtXVVVXXXXXXXXVVVXTt",
					"Tt>VVVXXXXXXXXVVVXTt",
					"Tcbbbbvvvbbbbbbb&***",
					"TtXXXXsXsXXXsXsX1LLL",
					"TtXXXXsXsXXXsXsXX1@@",
					"TtXXXXsXsXXXsXsXXXDd",
					"TtXXXXlmrXXXsXsXXXTt",
					"***(XXXXsXXXsXsbbbCt",
					"LLL3XXXXsXXXlmrXXXTt",
					"@@3XXXXXsXXXsXXXXXTt",
					"DdXXXXXXlmmmrXXXXXTt",
					"Tt>XXXXXXXXXXXXXXXTt",
					"--------------------"};
		}
	}

	void loadPlatforms(){
		for(size_t i = 0; i < mapMatrix.size(); ++i){
			for(size_t j = 0; j < 20; ++j){

				if(mapMatrix[i][j] == 'J'){
					joey.setPosition(Vector2f(j * 24, (i * 24) - 24));
				}
				else if(mapMatrix[i][j] != 'X' &&
						mapMatrix[i][j] != 'V' && mapMatrix[i][j] != 'v' && mapMatrix[i][j] != 's' &&
						!(mapMatrix[i][j] == 'Y' || mapMatrix[i][j] == '<' || mapMatrix[i][j] == '>')){
					Platform * platform = new Platform(Vector2f(j * 24, i * 24), Vector2f(24, 24));
					platform->assignTexture(mapMatrix[i][j]);
					platforms.push_back(platform);
				}
				else if(mapMatrix[i][j] == 'V' || mapMatrix[i][j] == 'v' || mapMatrix[i][j] == 's'){
					Ladder * ladder = new Ladder(Vector2f(j * 24, i * 24), Vector2f(24, 24));
					ladder->assignTexture(mapMatrix[i][j]);
					if(mapMatrix[i][j] == 'v')
						ladder->halfSolid = true;
					ladders.push_back(ladder);
				}
				else if(mapMatrix[i][j] == 'Y' || mapMatrix[i][j] == '<' || mapMatrix[i][j] == '>'){
					if(mapMatrix[i][j] == 'Y'){
						Enemy * enemy = new Enemy(Vector2f(j * 24.f, (i * 24.f) - 12.f - 12.f), Vector2f( 40.f, 0.f), Vector2f(36.f, 36.f), Vector2f(0.f, 2.f));
						enemies.push_back(enemy);
					}else if(mapMatrix[i][j] == '<'){
						Enemy* enemy = new Enemy(Vector2f(j * 24.f, (i * 24.f) - 12.f - 12.f), Vector2f(0.f, 0.f), Vector2f(36.f, 36.f), Vector2f(-4.f, 0.f));
						enemy->setFacingLeft(true);
						enemies.push_back(enemy);
					}else{
						Enemy * enemy = new Enemy(Vector2f(j * 24.f, (i * 24.f) - 12.f - 12.f), Vector2f( 0.f, 0.f), Vector2f(36.f, 36.f), Vector2f(4.f, 0.f));
						enemies.push_back(enemy);
					}
				}
			}
		}
	}

	void drawPlatforms(RenderWindow& window){
		for(auto& platform : platforms){
			platform->draw(&window);
		}
		for(auto& ladder : ladders){
			ladder->draw(&window);
		}
	}

	void drawEnemies(RenderWindow& window){
		for(auto& enemy : enemies){
			enemy->draw(&window);
		}
	}

	void drawApples(RenderWindow& window){
		for(auto& apple : apples){
			apple->draw(&window);
		}
	}

	void updateEnemies( float deltaTime, Clock* clock){
		for(auto& enemy : enemies){
			enemy->update(window, platforms, ladders, deltaTime);
		}

		for(unsigned int i = 0; i < enemies.size(); i++){
			if(enemies.at(i)->lives < 1){
				enemies.erase(enemies.begin() + i);
				points++;
			}
		}

		if((clock->getElapsedTime().asSeconds() > 0.25f) && enemies.size() > 0){
			clock->restart();
			std::srand((std::time(nullptr)));

			static random_device random_device;
			mt19937 random_number_generator(random_device());
			uniform_int_distribution<int> distribution(0, 5);

			int random_number = distribution(random_number_generator);
			int difficulty = (level / 3) + (level % 3);

			if(difficulty - random_number >= 0){
				uniform_int_distribution<int> dist2(0, enemies.size() - 1);
				int randNum = dist2(random_number_generator);
				apples.push_back(enemies.at(randNum)->shoot());
				apples.back()->setTexture(itemsTexture);
				enemyShoot.play();
			}
		}
	}

	void updateApples(float deltaTime){
		for(auto& apple : apples){
			apple->update(window, deltaTime);
		}
		for(unsigned int i = 0; i < apples.size(); i++){
			if(apples.at(i)->testCollision(window) || apples.at(i)->lives < 1)
				apples.erase(apples.begin() + i);
		}
	}


	void render(){
		window->clear();
		window->draw(background_sprite);
		infoBar.draw(window);
		drawPlatforms(*window);
		window->draw(joey);
		drawApples(*window);
		drawEnemies(*window);
		player.draw(window);

		window->display();
	}

	void updateLevel(){
		//Vector2f position = player.getPosition();
		if(joey.getGlobalBounds().intersects(player.getBody().getGlobalBounds())){
			player.setPosition(Vector2f(3 * 24, 19 * 24));

			player.isClimbing = false;
			player.tryingClimb = false;
			for(unsigned int i = 0; i < platforms.size(); i++){
				delete platforms.at(i);
			}
			platforms.clear();

			for(unsigned int i = 0; i < ladders.size(); i++){
				delete ladders.at(i);
			}
			ladders.clear();

			for(unsigned int i = 0; i < apples.size(); i++){
				delete apples.at(i);
			}
			apples.clear();

			for(unsigned int i = 0; i < enemies.size(); i++){
				delete enemies.at(i);
			}
			enemies.clear();

			level++;
			defineMapMatrix();
			loadPlatforms();
			dificult++;

			player.lives++;
			if(points >= enemies.size()){
				player.lives++;
			}
			points = 0;
		}
	}

	void run(){
		game_theme.setLoop(true);
		game_theme.play();
		Clock time;
		Clock randShoot;
		while(window->isOpen() && player.lives > 0){ //Loop de eventos
			Event event;
			Time deltaTime;
			deltaTime = time.restart();

			while (window->pollEvent(event)){
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
					window->close();
					exit(EXIT_SUCCESS);
				}

				if((event.type == Event::KeyReleased) && (event.key.code == Keyboard::M)){
					if(game_theme.getStatus() == sf::SoundSource::Status::Playing)
						game_theme.pause();
					else if(game_theme.getStatus() == sf::SoundSource::Status::Paused)
						game_theme.play();
				}
			}
			updateLevel();
			updateEnemies(deltaTime.asSeconds(), &randShoot);
			updateApples(deltaTime.asSeconds());
			player.player_update(window, platforms, ladders, enemies, apples, deltaTime.asSeconds());
			infoBar.InfoBarUpdate(player.lives, points, level );
			render();
		}
	}

	void finish(){
		for(unsigned int i = 0; i < platforms.size(); i++){
			delete platforms.at(i);
		}
		for(unsigned int i = 0; i < ladders.size(); i++){
			delete ladders.at(i);
		}
		for(unsigned int i = 0; i < enemies.size(); i++){
			delete enemies.at(i);
		}
		for(unsigned int i = 0; i < apples.size(); i++){
			delete apples.at(i);
		}
	}
};

#endif // GAME_H
