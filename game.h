#pragma once
#include "chap_header.h"
#include "gameObject.h"
#include "player.h"

struct SpawnData;

class Game
{
public:
	Game(void);
	~Game(void);

	void draw(sf::RenderWindow& window);
	void update(float secondsPassed);
	void loadLevel(string filename);
	

private:
	Player p;
	list<GameObject> bullets;
	list<SpawnData> spawns;
	list<GameObject> enemies;
	list<sf::Sprite> guiElements;
	sf::Sprite bg1, bg2, bg3; //Background images

	double gameTime;
};

struct SpawnData {
	float spawnTime;
	int x;
	int y;
	float vx;
	float vy;
};
