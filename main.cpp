/**
 * Chap Shmup v0.1.5
 */

#include "chap_header.h"
#include "game.h"
#include "gameObject.h"

void loadGlobalTextures();
void loadGlobalFonts();
bool mouseWithin(sf::Sprite spr);
bool mouseWithin(sf::Text tex);

int main() {
	//Load up our textures
	loadGlobalTextures();

	//Load Our Font
	loadGlobalFonts();

	//Load up the Game
	mainWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), windowName);
	Game theGame;

	//Frame Clock
	sf::Clock frameClock;
	frameClock.restart();

	//Menu Stuff - TODO, make separate class?
	sf::Texture splashTex;
	if (EXTERNAL_FILE_MODE)
		splashTex.loadFromFile(PROJECT_DIRECTORY + SPLASH_IMAGE);
	else
		splashTex.loadFromFile(SPLASH_IMAGE);
	sf::Sprite splashBox(splashTex);
	//Play Button
	sf::Text playButton("Play Game");
	playButton.setFont(FONT_1);
	playButton.setCharacterSize(64);
	playButton.setColor(sf::Color::Green);
	playButton.setPosition(WINDOW_WIDTH/2 - playButton.getGlobalBounds().width/2, 260);
	//Settings Button
	sf::Text settingsButton("Settings");
	settingsButton.setFont(FONT_1);
	settingsButton.setCharacterSize(64);
	settingsButton.setColor(sf::Color::Green);
	settingsButton.setPosition(WINDOW_WIDTH/2 - settingsButton.getGlobalBounds().width/2, 360);
	//Quit Button
	sf::Text quitButton("Quit Game");
	quitButton.setFont(FONT_1);
	quitButton.setCharacterSize(64);
	quitButton.setColor(sf::Color::Green);
	quitButton.setPosition(WINDOW_WIDTH/2 - quitButton.getGlobalBounds().width/2, 460);
	//Logo
	sf::Text logo("Chap Shmup");
	logo.setFont(FONT_1);
	logo.setCharacterSize(96);
	logo.setColor(sf::Color::Green);
	logo.setPosition(WINDOW_WIDTH/2 - logo.getGlobalBounds().width/2, 16);

	//Run the window
	while (mainWindow.isOpen()) {
		//Get elapsed time
		sf::Time elapsedTime = frameClock.restart();
		sf::Event e;
		while(mainWindow.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				mainWindow.close();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
				mainWindow.close();
			}
			if (e.type == sf::Event::MouseButtonPressed) {
				if (GAME_MODE == "Main Menu") {
					//Buttons!
					if (mouseWithin(playButton)) {
						GAME_MODE = "Play Game";
						theGame.start();
					}
					else if (mouseWithin(settingsButton)) {
						GAME_MODE = "Settings";
					}
					else if (mouseWithin(quitButton)) {
						mainWindow.close();
					}
				}
			}
		}
		//GAME_MODE: Main Menu
		if (GAME_MODE == "Main Menu") {
			mainWindow.clear();
			mainWindow.draw(playButton);
			mainWindow.draw(settingsButton);
			mainWindow.draw(quitButton);
			mainWindow.draw(logo);
			mainWindow.display();
		}
		//GAME_MODE: Play Game
		else if (GAME_MODE == "Play Game") {
			//Updating
			theGame.update(elapsedTime.asSeconds());

			//Drawing
			mainWindow.clear();
			theGame.draw(mainWindow);
			mainWindow.display();

			//Game ended?
			if (theGame.isLevelOver())
                GAME_MODE = "Main Menu";
		}
		//GAME_MODE: Settings
		else if (GAME_MODE == "Settings") {
			mainWindow.clear();
			mainWindow.draw(splashBox);
			mainWindow.display();
		}

		//Try to keep approx 60 fps
		sf::Time timeToPause = sf::milliseconds(16) - frameClock.getElapsedTime();
		sf::sleep(timeToPause);
	}

	//Terminate
	//system("pause");
	return EXIT_SUCCESS;
}

void loadGlobalTextures()
{
	if (EXTERNAL_FILE_MODE)
	{
		BULLET_TEXTURE.loadFromFile(PROJECT_DIRECTORY + BULLET_IMAGE);
		PLAYER_TEXTURE.loadFromFile(PROJECT_DIRECTORY + PLAYER_IMAGE);
		ENEMY_TEXTURE.loadFromFile(PROJECT_DIRECTORY + ENEMY_IMAGE);
		SIDEBAR_TEXTURE_L.loadFromFile(PROJECT_DIRECTORY + SIDEBAR_IMAGE_L);
		SIDEBAR_TEXTURE_R.loadFromFile(PROJECT_DIRECTORY + SIDEBAR_IMAGE_R);
		BACKGROUND_TEXTURE.loadFromFile(PROJECT_DIRECTORY + BACKGROUND_IMAGE);
	}
	else
	{
		BULLET_TEXTURE.loadFromFile(BULLET_IMAGE);
		PLAYER_TEXTURE.loadFromFile(PLAYER_IMAGE);
		ENEMY_TEXTURE.loadFromFile(ENEMY_IMAGE);
		SIDEBAR_TEXTURE_L.loadFromFile(SIDEBAR_IMAGE_L);
		SIDEBAR_TEXTURE_R.loadFromFile(SIDEBAR_IMAGE_R);
		BACKGROUND_TEXTURE.loadFromFile(BACKGROUND_IMAGE);
	}
}

void loadGlobalFonts() {
    if (EXTERNAL_FILE_MODE)
	{
	    FONT_1.loadFromFile(PROJECT_DIRECTORY + FONT_FILE_1);
	}
	else{
        FONT_1.loadFromFile(FONT_FILE_1);
	}
}

bool mouseWithin(sf::Sprite spr) {
	int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > spr.getPosition().x && x < spr.getPosition().x + spr.getGlobalBounds().width
		&& x > spr.getPosition().y && y < spr.getPosition().y + spr.getGlobalBounds().height;
}

bool mouseWithin(sf::Text tex) {
	int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > tex.getPosition().x && x < tex.getPosition().x + tex.getGlobalBounds().width
		&& x > tex.getPosition().y && y < tex.getPosition().y + tex.getGlobalBounds().height;
}
