#include "chap_header.h"

string windowName = "Chap Shmup";
sf::RenderWindow mainWindow;

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

int GAME_ZONE_X = 240;
int GAME_ZONE_Y = 0;
int GAME_ZONE_WIDTH = 800;
int GAME_ZONE_HEIGHT = 720;
int GAME_ZONE_PADDING = 240;

string GAME_MODE = "Main Menu";

float PLAYER_SPEED = 400.0;
float PLAYER_ACCEL = 2000.0;
float PLAYER_DECEL = 2000.0;
float MAX_SPEED = 1000000.0;
bool INVERTED_Y_AXIS = false;

float BULLET_SPEED = 800.0;
float RELOAD_TIME = 0.2;
float BACKGROUND_SPEED = 32.0;
float MAX_HEALTH = 100.0;
float BULLET_DAMAGE = 10.0;
float CRASH_DAMAGE = 20.0;
float ENEMY_MAX_HEALTH = 10.0;
float ENEMY_RELOAD_TIME = 1.0;
float ENEMY_BULLET_SPEED = 400.0;

string PROJECT_DIRECTORY = "C:/Users/gruarm/GitHub/ChapShmup/"; //Desktop
//string PROJECT_DIRECTORY = "D:/Documents/Projects/ChapShmup/"; //Laptop
bool EXTERNAL_FILE_MODE = true;

string PLAYER_IMAGE = "img/player.png";
string FLAME_IMAGE = "img/flame.png";
string SPLASH_IMAGE = "img/menu.png";
string BULLET_IMAGE = "img/bullet.png";
string ENEMY_BULLET_IMAGE = "img/enemy_bullet.png";
string ENEMY_IMAGE = "img/enemy.png";
string SIDEBAR_IMAGE_L = "img/sidebar_l.png";
string SIDEBAR_IMAGE_R = "img/sidebar_r.png";
string BACKGROUND_IMAGE = "img/game_bg.png";

string EARTH_IMAGE = "img/earth.png";

sf::Texture PLAYER_TEXTURE;
sf::Texture FLAME_TEXTURE;
sf::Texture BULLET_TEXTURE, ENEMY_BULLET_TEXTURE;
sf::Texture ENEMY_TEXTURE;
sf::Texture SIDEBAR_TEXTURE_L, SIDEBAR_TEXTURE_R;
sf::Texture BACKGROUND_TEXTURE;

sf::Texture EARTH_TEXTURE;

string FONT_FILE_1 = "font/LiquidCrystal-Normal.otf";
sf::Font FONT_1;
string FONT_FILE_2 = "font/transuranium.ttf";
sf::Font FONT_2;

string TEST_LEVEL = "data/test_lvl.txt";

//Global Functions
void loadGlobalTextures()
{
	if (EXTERNAL_FILE_MODE)
	{
		BULLET_TEXTURE.loadFromFile(PROJECT_DIRECTORY + BULLET_IMAGE);
		ENEMY_BULLET_TEXTURE.loadFromFile(PROJECT_DIRECTORY + ENEMY_BULLET_IMAGE);
		PLAYER_TEXTURE.loadFromFile(PROJECT_DIRECTORY + PLAYER_IMAGE);
		FLAME_TEXTURE.loadFromFile(PROJECT_DIRECTORY + FLAME_IMAGE);
		ENEMY_TEXTURE.loadFromFile(PROJECT_DIRECTORY + ENEMY_IMAGE);
		SIDEBAR_TEXTURE_L.loadFromFile(PROJECT_DIRECTORY + SIDEBAR_IMAGE_L);
		SIDEBAR_TEXTURE_R.loadFromFile(PROJECT_DIRECTORY + SIDEBAR_IMAGE_R);
		BACKGROUND_TEXTURE.loadFromFile(PROJECT_DIRECTORY + BACKGROUND_IMAGE);
		EARTH_TEXTURE.loadFromFile(PROJECT_DIRECTORY + EARTH_IMAGE);
	}
	else
	{
	    ENEMY_BULLET_TEXTURE.loadFromFile(ENEMY_BULLET_IMAGE);
		BULLET_TEXTURE.loadFromFile(BULLET_IMAGE);
		PLAYER_TEXTURE.loadFromFile(PLAYER_IMAGE);
		FLAME_TEXTURE.loadFromFile(FLAME_IMAGE);
		ENEMY_TEXTURE.loadFromFile(ENEMY_IMAGE);
		SIDEBAR_TEXTURE_L.loadFromFile(SIDEBAR_IMAGE_L);
		SIDEBAR_TEXTURE_R.loadFromFile(SIDEBAR_IMAGE_R);
		BACKGROUND_TEXTURE.loadFromFile(BACKGROUND_IMAGE);
		EARTH_TEXTURE.loadFromFile(EARTH_IMAGE);
	}
}

void loadGlobalFonts() {
    if (EXTERNAL_FILE_MODE)
	{
	    FONT_1.loadFromFile(PROJECT_DIRECTORY + FONT_FILE_1);
	    FONT_2.loadFromFile(PROJECT_DIRECTORY + FONT_FILE_2);
	}
	else{
        FONT_1.loadFromFile(FONT_FILE_1);
        FONT_2.loadFromFile(FONT_FILE_2);
	}
}

bool mouseWithin(sf::Sprite spr) {
	int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > spr.getPosition().x && x < spr.getPosition().x + spr.getGlobalBounds().width
		&& y > spr.getPosition().y && y < spr.getPosition().y + spr.getGlobalBounds().height;
}

bool mouseWithin(sf::Text tex) {
	int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > tex.getPosition().x && x < tex.getPosition().x + tex.getGlobalBounds().width
		&& y > tex.getPosition().y && y < tex.getPosition().y + tex.getGlobalBounds().height;
}

sf::Text createText(string txt, int charSize, sf::Color color, sf::Font& font) {
    sf::Text text;
    text.setString(txt);
    text.setCharacterSize(charSize);
    text.setColor(color);
    text.setFont(font);
    return text;
}

sf::Text createText(string txt, int charSize, sf::Color color) {
    return createText(txt, charSize, color, FONT_1);
}
