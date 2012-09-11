#include "game.h"


Game::Game(void) {
	p.linkBullets(&bullets);
	p.loadTexture(PLAYER_TEXTURE);
	p.setPosition(400, 500);

	sf::Sprite sidebar1(SIDEBAR_TEXTURE);
	sf::Sprite sidebar2(SIDEBAR_TEXTURE);
	sidebar2.setPosition(GAME_ZONE_X + GAME_ZONE_WIDTH, 0);
	guiElements.push_back(sidebar1);
	guiElements.push_back(sidebar2);

	bg1.setTexture(BACKGROUND_TEXTURE);
	bg2.setTexture(BACKGROUND_TEXTURE);
	bg3.setTexture(BACKGROUND_TEXTURE);
	bg1.move(GAME_ZONE_X, 0);
	bg2.move(GAME_ZONE_X, -GAME_ZONE_HEIGHT);
	bg3.move(GAME_ZONE_X, -GAME_ZONE_HEIGHT*2);

	loadLevel(TEST_LEVEL);

	gameTime = 0.0;
}


Game::~Game(void){

}


void Game::draw(sf::RenderWindow& window) {
	//Draw the background
	window.draw(bg1);
	window.draw(bg2);
	window.draw(bg3);
	//Draw the bullets
	for (list<GameObject>::iterator itr = bullets.begin(); itr != bullets.end(); itr++)
		itr->draw(window);
	//Draw enemies
	for (list<Enemy>::iterator itr = enemies.begin(); itr != enemies.end(); itr++)
		itr->draw(window);
	//Draw the player
	p.draw(window);

	//Draw GUI Elements
	for (list<sf::Sprite>::iterator itr = guiElements.begin(); itr != guiElements.end(); itr++)
		window.draw(*itr);
}


void Game::update(float secondsPassed) {
	gameTime += (double) secondsPassed;
	//Update the background
	bg1.move(0, BACKGROUND_SPEED*secondsPassed);
	bg2.move(0, BACKGROUND_SPEED*secondsPassed);
	bg3.move(0, BACKGROUND_SPEED*secondsPassed);
	if (bg1.getPosition().y > GAME_ZONE_Y + GAME_ZONE_HEIGHT)
		bg1.move(0, -GAME_ZONE_HEIGHT*3);
	if (bg2.getPosition().y > GAME_ZONE_Y + GAME_ZONE_HEIGHT)
		bg2.move(0, -GAME_ZONE_HEIGHT*3);
	if (bg3.getPosition().y > GAME_ZONE_Y + GAME_ZONE_HEIGHT)
		bg3.move(0, -GAME_ZONE_HEIGHT*3);
	//Deal with new spawns
	for (list<SpawnData>::iterator itr = spawns.begin(); itr != spawns.end(); ) {
		if (itr->spawnTime < gameTime) {
			//Add an enemy
			Enemy e;
			e.loadTexture(ENEMY_TEXTURE);
			e.setPosition(itr->x + GAME_ZONE_X, itr->y);
			e.setVelocity(itr->vx, itr->vy);
			enemies.push_back(e);
			itr = spawns.erase(itr);
		}
		//The list is ordered, so break if it's not spawn time yet
		else
			break;
	}
	//Update the bullets
	for (list<GameObject>::iterator itr = bullets.begin(); itr != bullets.end(); itr++)
		itr->update(secondsPassed);
	//Update enemies
	for (list<Enemy>::iterator itr = enemies.begin(); itr != enemies.end(); itr++)
		itr->update(secondsPassed);
	//Check for bullet collisions
	for(list<Enemy>::iterator eitr = enemies.begin(); eitr != enemies.end(); eitr++) {
		for (list<GameObject>::iterator itr = bullets.begin(); itr != bullets.end(); itr++) {
			if (eitr->rectCollide(*itr)) {
				itr->kill();
				//Do something with the enemy here
				eitr->damage(p.getBulletDamage());
				break;
			}
		}
	}
	//What about collisions with enemy bullets?

	//Or enemies themselves crashing?
    for (list<Enemy>::iterator itr = enemies.begin(); itr != enemies.end(); itr++) {
        if (itr->rectCollide(p)) {
            p.damage(CRASH_DAMAGE);
            itr->kill();
        }
    }
	//Sweep for out of bounds bullets
	for (list<GameObject>::iterator itr = bullets.begin(); itr != bullets.end(); itr++) {
		if (itr->getX() + itr->getWidth() < 0 || itr->getX() > WINDOW_WIDTH
			|| itr->getY() + itr->getHeight() < 0 || itr->getY() > WINDOW_HEIGHT)
			itr->kill();
	}
	//Sweep for out of bounds enemies

	//Garbage Collection!
    for(list<Enemy>::iterator eitr = enemies.begin(); eitr != enemies.end(); ) {
        if(eitr->isDead())
            eitr = enemies.erase(eitr);
        else
            eitr++;
    }
    for (list<GameObject>::iterator itr = bullets.begin(); itr != bullets.end(); ) {
        if (itr->isDead())
            itr = bullets.erase(itr);
        else
            itr++;
    }

	//Update the player
	p.update(secondsPassed);
}

void Game::loadLevel(string filename) {
	ifstream level;
	if (EXTERNAL_FILE_MODE)
		level.open((PROJECT_DIRECTORY + filename).c_str());
	else
		level.open(filename.c_str());
	if (!level.is_open())
		return;
	while (!level.eof()) {
		SpawnData entry;
		level >> entry.spawnTime;
		level >> entry.x;
		level >> entry.y;
		level >> entry.vx;
		level >> entry.vy;
		spawns.push_back(entry);
	}
	level.close();
}
