/**
 * Chap Shmup v0.1.5
 */

#include "chap_header.h"
#include "game.h"
#include "gameObject.h"
#include "textButton.h"

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
    TextButton playButton("Play Game", 64, sf::Color::Green);
    playButton.setSelectedColor(sf::Color::Red);
    playButton.text.setPosition(WINDOW_WIDTH/2 - playButton.text.getGlobalBounds().width/2, 260);
	//Settings Button
	TextButton settingsButton("Settings", 64, sf::Color::Green);
	settingsButton.setSelectedColor(sf::Color::Red);
    settingsButton.text.setPosition(WINDOW_WIDTH/2 - settingsButton.text.getGlobalBounds().width/2, 360);
	//Quit Button
	TextButton quitButton("Quit Game", 64, sf::Color::Green);
	quitButton.setSelectedColor(sf::Color::Red);
    quitButton.text.setPosition(WINDOW_WIDTH/2 - quitButton.text.getGlobalBounds().width/2, 460);
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
					if (mouseWithin(playButton.text)) {
						GAME_MODE = "Play Game";
						theGame.start();
					}
					else if (mouseWithin(settingsButton.text)) {
						GAME_MODE = "Settings";
					}
					else if (mouseWithin(quitButton.text)) {
						mainWindow.close();
					}
				}
			}
		}
		//GAME_MODE: Main Menu
		if (GAME_MODE == "Main Menu") {
		    //Updating
		    playButton.update(elapsedTime.asSeconds());
		    settingsButton.update(elapsedTime.asSeconds());
		    quitButton.update(elapsedTime.asSeconds());

		    //Drawing
			mainWindow.clear();
			playButton.draw(mainWindow);
			settingsButton.draw(mainWindow);
			quitButton.draw(mainWindow);
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


