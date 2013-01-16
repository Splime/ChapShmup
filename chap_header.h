
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#pragma once
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::ifstream;
using std::vector;
using std::stringstream;

extern string windowName;
extern sf::RenderWindow mainWindow;

extern int WINDOW_WIDTH, WINDOW_HEIGHT;

extern int GAME_ZONE_X, GAME_ZONE_Y, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT, GAME_ZONE_PADDING;

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
extern float ENEMY_MAX_HEALTH;
extern float ENEMY_RELOAD_TIME;
extern float ENEMY_BULLET_SPEED;

//File Loading Info
extern string PROJECT_DIRECTORY;
extern bool EXTERNAL_FILE_MODE;

//Graphics files
extern string PLAYER_IMAGE;
extern string SPLASH_IMAGE;
extern string BULLET_IMAGE;
extern string ENEMY_BULLET_IMAGE;
extern string ENEMY_IMAGE;
extern string SIDEBAR_IMAGE_L, SIDEBAR_IMAGE_R;
extern string BACKGROUND_IMAGE;

extern string EARTH_IMAGE;

//Textures that get reused a lot:
extern sf::Texture PLAYER_TEXTURE;
extern sf::Texture BULLET_TEXTURE;
extern sf::Texture ENEMY_BULLET_TEXTURE;
extern sf::Texture ENEMY_TEXTURE;
extern sf::Texture SIDEBAR_TEXTURE_L, SIDEBAR_TEXTURE_R;
extern sf::Texture BACKGROUND_TEXTURE;

extern sf::Texture EARTH_TEXTURE;

//Font stuff
extern string FONT_FILE_1;
extern sf::Font FONT_1;
extern string FONT_FILE_2;
extern sf::Font FONT_2;

//Level Data
extern string TEST_LEVEL;

//Functions
void loadGlobalTextures();
void loadGlobalFonts();
bool mouseWithin(sf::Sprite spr);
bool mouseWithin(sf::Text tex);
sf::Text createText(string txt, int charSize, sf::Color color);
sf::Text createText(string txt, int charSize, sf::Color color, sf::Font& font);
