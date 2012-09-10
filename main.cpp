/**
 * Chap Shmup v0.1
 * 07/10/2012
 */

#include "chap_header.h"
#include "game.h"
#include "gameObject.h"

void loadGlobalTextures();
bool clickWithin(sf::Sprite spr);

int main() {
	//Load up our textures
	loadGlobalTextures();

	//Load up the Game
	mainWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), windowName);
	Game theGame;

	//Frame Clock
	sf::Clock frameClock;
	frameClock.restart();

	//Menu Stuff - Temporary
	sf::Texture splashTex;
	if (EXTERNAL_FILE_MODE)
		splashTex.loadFromFile(PROJECT_DIRECTORY + SPLASH_IMAGE);
	else
		splashTex.loadFromFile(SPLASH_IMAGE);
	sf::Sprite splashBox(splashTex);
	sf::Sprite playButton(PLAY_BUTTON_TEXTURE);
	playButton.setPosition(640-160, 160);
	sf::Sprite settingsButton(SETTINGS_BUTTON_TEXTURE);
	settingsButton.setPosition(640-160, 360);
	sf::Sprite quitButton(QUIT_BUTTON_TEXTURE);
	quitButton.setPosition(640-160, 560);

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
					if (clickWithin(playButton)) {
						GAME_MODE = "Play Game";
					}
					else if (clickWithin(settingsButton)) {
						GAME_MODE = "Settings";
					}
					else if (clickWithin(quitButton)) {
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
			mainWindow.display();
		}
		//GAME_MODE: Play Game
		if (GAME_MODE == "Play Game") {
			//Updating
			theGame.update(elapsedTime.asSeconds());

			//Drawing
			mainWindow.clear();
			theGame.draw(mainWindow);
			mainWindow.display();
		}
		//GAME_MODE: Settings
		if (GAME_MODE == "Settings") {
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
		SIDEBAR_TEXTURE.loadFromFile(PROJECT_DIRECTORY + SIDEBAR_IMAGE);
		BACKGROUND_TEXTURE.loadFromFile(PROJECT_DIRECTORY + BACKGROUND_IMAGE);

		PLAY_BUTTON_TEXTURE.loadFromFile(PROJECT_DIRECTORY + PLAY_BUTTON_IMAGE);
		SETTINGS_BUTTON_TEXTURE.loadFromFile(PROJECT_DIRECTORY + SETTINGS_BUTTON_IMAGE);
		QUIT_BUTTON_TEXTURE.loadFromFile(PROJECT_DIRECTORY + QUIT_BUTTON_IMAGE);
	}
	else
	{
		BULLET_TEXTURE.loadFromFile(BULLET_IMAGE);
		PLAYER_TEXTURE.loadFromFile(PLAYER_IMAGE);
		ENEMY_TEXTURE.loadFromFile(ENEMY_IMAGE);
		SIDEBAR_TEXTURE.loadFromFile(SIDEBAR_IMAGE);
		BACKGROUND_TEXTURE.loadFromFile(BACKGROUND_IMAGE);

		PLAY_BUTTON_TEXTURE.loadFromFile(PLAY_BUTTON_IMAGE);
		SETTINGS_BUTTON_TEXTURE.loadFromFile(SETTINGS_BUTTON_IMAGE);
		QUIT_BUTTON_TEXTURE.loadFromFile(QUIT_BUTTON_IMAGE);
	}
}

bool clickWithin(sf::Sprite spr) {
	int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > spr.getPosition().x && x < spr.getPosition().x + spr.getGlobalBounds().width
		&& x > spr.getPosition().y && y < spr.getPosition().y + spr.getGlobalBounds().height;
}