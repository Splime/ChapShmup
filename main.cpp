/**
 * Chap Shmup v0.1.5a
 */

#include "chap_header.h"
#include "game.h"
#include "gameObject.h"
#include "textButton.h"

int main() {
    //RNG
    srand((unsigned int)time(NULL));

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
	//New Game
	TextButton newGameButton("New Game", 64, sf::Color::Green);
    newGameButton.setSelectedColor(sf::Color::Red);
    newGameButton.text.setPosition(WINDOW_WIDTH/2 - newGameButton.text.getGlobalBounds().width/2, 160);
	//Load Game
	TextButton loadGameButton("Load Game", 64, sf::Color::Green);
    loadGameButton.setSelectedColor(sf::Color::Red);
    loadGameButton.text.setPosition(WINDOW_WIDTH/2 - loadGameButton.text.getGlobalBounds().width/2, 260);
	//Instant Play
    TextButton playButton("Instant Play", 64, sf::Color::Green);
    playButton.setSelectedColor(sf::Color::Red);
    playButton.text.setPosition(WINDOW_WIDTH/2 - playButton.text.getGlobalBounds().width/2, 360);
	//Settings Button
	TextButton settingsButton("Settings", 64, sf::Color::Green);
	settingsButton.setSelectedColor(sf::Color::Red);
    settingsButton.text.setPosition(WINDOW_WIDTH/2 - settingsButton.text.getGlobalBounds().width/2, 460);
	//Quit Button
	TextButton quitButton("Quit Game", 64, sf::Color::Green);
	quitButton.setSelectedColor(sf::Color::Red);
    quitButton.text.setPosition(WINDOW_WIDTH/2 - quitButton.text.getGlobalBounds().width/2, 560);
	//Logo
	sf::Text logo = createText("Chap Shmup", 96, sf::Color::Green, FONT_2);
	logo.setPosition(WINDOW_WIDTH/2 - logo.getGlobalBounds().width/2, 16);

	//Settings Screen
	//Title
	sf::Text settingsTitle = createText("Settings", 96, sf::Color::Green, FONT_2);
	settingsTitle.setPosition(WINDOW_WIDTH/2 - settingsTitle.getGlobalBounds().width/2, 16);
	//TODO
	//Actual Settings
	//Back
	TextButton backButton("Back", 64, sf::Color::Green);
	backButton.setSelectedColor(sf::Color::Red);
    backButton.text.setPosition(WINDOW_WIDTH/2 - backButton.text.getGlobalBounds().width/2, 560);

    //New Game Screen
    //Title
    sf::Text newGameTitle = createText("2:13 AM, 21 December, 2712", 64, sf::Color::Green);
	newGameTitle.setPosition(WINDOW_WIDTH/2 - newGameTitle.getGlobalBounds().width/2, 16);
	//Story Blurb

	//Character Input
	sf::Text charInputText = createText("Character Info:", 32, sf::Color::Green);
	charInputText.setPosition(3*WINDOW_WIDTH/4 - charInputText.getGlobalBounds().width/2, 160);
	sf::Text nameInputText = createText("Your Name:", 32, sf::Color::Green);
	nameInputText.setPosition(3*WINDOW_WIDTH/4 - nameInputText.getGlobalBounds().width, 260);
	//Next Button
	TextButton nextButton("Next", 32, sf::Color::Green);
	nextButton.setSelectedColor(sf::Color::Red);
    nextButton.text.setPosition(WINDOW_WIDTH/2 - nextButton.text.getGlobalBounds().width/2, 560);

	//Run the window
	while (mainWindow.isOpen()) {
		//Get elapsed time
		sf::Time elapsedTime = frameClock.restart();
		sf::Event e;
		while(mainWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
            {
				mainWindow.close();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                if (GAME_MODE == "Main Menu")
                {
                    mainWindow.close();
                }
                else
                {
                    GAME_MODE = "Main Menu";
                }
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (GAME_MODE == "Main Menu")
				{
					//Buttons!
					if (mouseWithin(newGameButton.text))
					{
						GAME_MODE = "New Game";
					}
					else if (mouseWithin(loadGameButton.text))
					{
						GAME_MODE = "Load Game";
					}
					else if (mouseWithin(playButton.text))
					{
						GAME_MODE = "Play Level";
						theGame.start();
					}
					else if (mouseWithin(settingsButton.text))
					{
						GAME_MODE = "Settings";
					}
					else if (mouseWithin(quitButton.text))
					{
						mainWindow.close();
					}
				}
				else if (GAME_MODE == "Settings")
                {
                    if (mouseWithin(backButton.text))
					{
						GAME_MODE = "Main Menu";
					}
                }
                else if (GAME_MODE == "New Game")
                {
                    if (mouseWithin((nextButton.text)))
                    {
                        GAME_MODE = "Play Level";
						theGame.start();
                    }
                }
			}
		}
		//GAME_MODE: Main Menu
		if (GAME_MODE == "Main Menu")
        {
		    //Updating
		    playButton.update(elapsedTime.asSeconds());
		    settingsButton.update(elapsedTime.asSeconds());
		    quitButton.update(elapsedTime.asSeconds());
		    newGameButton.update(elapsedTime.asSeconds());
		    loadGameButton.update(elapsedTime.asSeconds());

		    //Drawing
			mainWindow.clear();
			playButton.draw(mainWindow);
			settingsButton.draw(mainWindow);
			quitButton.draw(mainWindow);
			loadGameButton.draw(mainWindow);
			newGameButton.draw(mainWindow);
			mainWindow.draw(logo);
			mainWindow.display();
		}
		//GAME_MODE: Play Game
		else if (GAME_MODE == "Play Level")
        {
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
		else if (GAME_MODE == "Settings")
        {
            //Updating
            backButton.update(elapsedTime.asSeconds());

            //Drawing
			mainWindow.clear();
			mainWindow.draw(settingsTitle);
			backButton.draw(mainWindow);
			mainWindow.display();
		}
		else if (GAME_MODE == "New Game")
        {
            //Update
            nextButton.update(elapsedTime.asSeconds());

            //Draw
            mainWindow.clear();
            mainWindow.draw(newGameTitle);
            mainWindow.draw(charInputText);
            mainWindow.draw(nameInputText);
            nextButton.draw(mainWindow);
            mainWindow.display();
        }
        else if (GAME_MODE == "Load Game")
        {
            //Update


            //Draw
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


