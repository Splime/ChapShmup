#include "game.h"


Game::Game(void) {
	p.linkBullets(&bullets);
	p.loadTexture(PLAYER_TEXTURE);
	p.setPosition(400, 500);

	sf::Sprite sidebar1(SIDEBAR_TEXTURE_L);
	sf::Sprite sidebar2(SIDEBAR_TEXTURE_R);
	sidebar2.setPosition(GAME_ZONE_X + GAME_ZONE_WIDTH, 0);
	guiElements.push_back(sidebar1);
	guiElements.push_back(sidebar2);

	sf::Text healthDisplay = createText("Hull Strength: ", 24, sf::Color::Green);
	healthDisplay.setPosition(8, 500);
	healthNumberDisplay = createText("00", 32, sf::Color::Green);
	healthNumberDisplay.setPosition(8, healthDisplay.getPosition().y + healthDisplay.getGlobalBounds().height + 8);

	sf::Text navigationLabel = createText("Elgoog Navigation", 18, sf::Color::Green);
	navigationLabel.setPosition(1052, 8);

	guiTexts.push_back(healthDisplay);
	guiTexts.push_back(navigationLabel);
	//guiTexts.push_back(healthNumberDisplay);

	bg1.setTexture(BACKGROUND_TEXTURE);
	bg2.setTexture(BACKGROUND_TEXTURE);
	bg3.setTexture(BACKGROUND_TEXTURE);
	bg1.move(GAME_ZONE_X, 0);
	bg2.move(GAME_ZONE_X, -GAME_ZONE_HEIGHT);
	bg3.move(GAME_ZONE_X, -GAME_ZONE_HEIGHT*2);

	//loadLevel(TEST_LEVEL); //Removed, start always gets called and start calls this

	gameTime = 0.0;
	gameOver = false;
}


Game::~Game(void){

}


void Game::start() {
    bullets.clear();
    enemyBullets.clear();
    enemies.clear();
    spawns.clear();
    p.setPosition(400, 500);
    p.heal(-1);

	loadLevel(TEST_LEVEL);

	gameTime = 0.0;
	gameOver = false;
}

void Game::draw(sf::RenderWindow& window) {
	//Draw the background
	window.draw(bg1);
	window.draw(bg2);
	window.draw(bg3);
	//Draw the bullets
	for (GameObject& b : bullets)
		b.draw(window);
    for (GameObject& b : enemyBullets)
		b.draw(window);
	//Draw enemies
	for (Enemy& e : enemies)
		e.draw(window);
	//Draw the player
	p.draw(window);

	//Draw GUI Elements
	for (sf::Sprite& spr : guiElements)
		window.draw(spr);
    for (sf::Text& txt : guiTexts)
		window.draw(txt);
    window.draw(healthNumberDisplay);
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
			e.linkBullets(&enemyBullets);
			enemies.push_back(e);
			itr = spawns.erase(itr);
		}
		//The list is ordered, so break if it's not spawn time yet
		else
			break;
	}
	//Update the bullets
	for (GameObject& b : bullets)
		b.update(secondsPassed);
    for (GameObject& b : enemyBullets)
		b.update(secondsPassed);
	//Update enemies
	for (Enemy& e : enemies)
		e.update(secondsPassed);
    //Update the healthNumberDisplay
    stringstream ss;
    ss << p.getHealth();
    string healthNum;
    ss >> healthNum;
    healthNumberDisplay.setString(healthNum);
	//Check for bullet collisions
	for(Enemy& e : enemies) {
		for (GameObject& b : bullets) {
			if (e.rectCollide(b)) {
				b.kill();
				e.damage(p.getBulletDamage());
			}
		}
	}
	//What about collisions with enemy bullets?
    for (GameObject& b : enemyBullets)
    {
        if (b.rectCollide(p)) {
            b.kill();
            p.damage(BULLET_DAMAGE);
        }
    }
	//Or enemies themselves crashing?
    for (Enemy& e : enemies) {
        if (e.rectCollide(p)) {
            p.damage(CRASH_DAMAGE);
            e.kill();
        }
    }
	//Sweep for out of bounds bullets
	for (GameObject& b : bullets) {
		if (b.getX() + b.getWidth() < -GAME_ZONE_PADDING || b.getX() > WINDOW_WIDTH + GAME_ZONE_PADDING
			|| b.getY() + b.getHeight() < -GAME_ZONE_PADDING || b.getY() > WINDOW_HEIGHT + GAME_ZONE_PADDING)
			b.kill();
	}
	for (GameObject& b : enemyBullets) {
		if (b.getX() + b.getWidth() < -GAME_ZONE_PADDING || b.getX() > WINDOW_WIDTH + GAME_ZONE_PADDING
			|| b.getY() + b.getHeight() < -GAME_ZONE_PADDING || b.getY() > WINDOW_HEIGHT + GAME_ZONE_PADDING)
			b.kill();
	}
	//Sweep for out of bounds enemies
    for (Enemy& e : enemies) {
		if (e.getX() + e.getWidth() < -GAME_ZONE_PADDING || e.getX() > WINDOW_WIDTH + GAME_ZONE_PADDING
			|| e.getY() + e.getHeight() < -GAME_ZONE_PADDING || e.getY() > WINDOW_HEIGHT + GAME_ZONE_PADDING)
			e.kill();
	}
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
    for (list<GameObject>::iterator itr = enemyBullets.begin(); itr != enemyBullets.end(); ) {
        if (itr->isDead())
            itr = enemyBullets.erase(itr);
        else
            itr++;
    }
	//Update the player
	p.update(secondsPassed);

	//End of level?
	if (gameTime > levelLength)
        gameOver = true;
}

void Game::loadLevel(string filename) {
	ifstream level;
	if (EXTERNAL_FILE_MODE)
		level.open((PROJECT_DIRECTORY + filename).c_str());
	else
		level.open(filename.c_str());
	if (!level.is_open())
		return;
    level >> levelLength;
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
