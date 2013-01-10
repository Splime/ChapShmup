/**
 * Game: Represents a single level
 * (A bit of a misleading name, due to changing scope of the game)
 */

#pragma once
#include "chap_header.h"
#include "gameObject.h"
#include "player.h"
#include "enemy.h"

struct SpawnData;

class Game
{
public:
	Game(void);
	~Game(void);

    void start();
	void draw(sf::RenderWindow& window);
	void update(float secondsPassed);
	void loadLevel(string filename);

	bool isLevelOver() { return gameOver; }


private:
	Player p;
	list<GameObject> bullets;
	list<GameObject> enemyBullets;
	list<SpawnData> spawns;
	list<Enemy> enemies;
	list<GameObject> miscObjects;
	vector<sf::Sprite> guiElements;
	vector<sf::Text> guiTexts;
	sf::Text healthNumberDisplay;
	sf::Sprite bg1, bg2, bg3; //Background images
	sf::RectangleShape distanceBar;
	sf::Vector2f distBarStart;
	sf::Vector2f distBarMaxSize;

	double gameTime;
	double levelLength;
	bool gameOver;
};

struct SpawnData {
    string spawnType;
	float spawnTime;
	int x;
	int y;
	float vx;
	float vy;
};
