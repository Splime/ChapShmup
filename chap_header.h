
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//#include "game.h"
//#include "gameObject.h"

#pragma once
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::ifstream;

extern string windowName;
extern sf::RenderWindow mainWindow;

extern int WINDOW_WIDTH, WINDOW_HEIGHT;

extern int GAME_ZONE_X, GAME_ZONE_Y, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT;

extern string GAME_MODE;

//Player Variables
extern float PLAYER_ACCEL;
extern float PLAYER_DECEL;
extern float PLAYER_SPEED;
extern float MAX_SPEED;
extern bool INVERTED_Y_AXIS;

extern float BULLET_SPEED;
extern float RELOAD_TIME;
extern float BACKGROUND_SPEED;
extern float MAX_HEALTH;
extern float BULLET_DAMAGE;
extern float CRASH_DAMAGE;

//File Loading Info
extern string PROJECT_DIRECTORY;
extern bool EXTERNAL_FILE_MODE;

//Graphics files
extern string PLAYER_IMAGE;
extern string SPLASH_IMAGE;
extern string BULLET_IMAGE;
extern string ENEMY_IMAGE;
extern string SIDEBAR_IMAGE;
extern string BACKGROUND_IMAGE;

extern string PLAY_BUTTON_IMAGE;
extern string QUIT_BUTTON_IMAGE;
extern string SETTINGS_BUTTON_IMAGE;

//Textures that get reused a lot:
extern sf::Texture PLAYER_TEXTURE;
extern sf::Texture BULLET_TEXTURE;
extern sf::Texture ENEMY_TEXTURE;
extern sf::Texture SIDEBAR_TEXTURE;
extern sf::Texture BACKGROUND_TEXTURE;

extern sf::Texture PLAY_BUTTON_TEXTURE;
extern sf::Texture QUIT_BUTTON_TEXTURE;
extern sf::Texture SETTINGS_BUTTON_TEXTURE;

//Level Data
extern string TEST_LEVEL;
