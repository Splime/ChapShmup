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

string PROJECT_DIRECTORY = "C:/Users/gruarm/Documents/Projects/ChapShmup/";
bool EXTERNAL_FILE_MODE = true;

string PLAYER_IMAGE = "img/rocket.png";
string SPLASH_IMAGE = "img/menu.png";
string BULLET_IMAGE = "img/bullet.png";
string ENEMY_IMAGE = "img/enemy.png";
string SIDEBAR_IMAGE_L = "img/sidebar_l.png";
string SIDEBAR_IMAGE_R = "img/sidebar_r.png";
string BACKGROUND_IMAGE = "img/game_bg.png";

string PLAY_BUTTON_IMAGE = "img/buttons/play.png";
string QUIT_BUTTON_IMAGE = "img/buttons/quit.png";
string SETTINGS_BUTTON_IMAGE = "img/buttons/settings.png";

sf::Texture PLAYER_TEXTURE;
sf::Texture BULLET_TEXTURE;
sf::Texture ENEMY_TEXTURE;
sf::Texture SIDEBAR_TEXTURE_L, SIDEBAR_TEXTURE_R;
sf::Texture BACKGROUND_TEXTURE;

sf::Texture PLAY_BUTTON_TEXTURE;
sf::Texture QUIT_BUTTON_TEXTURE;
sf::Texture SETTINGS_BUTTON_TEXTURE;

string FONT_FILE_1 = "font/neuropolitical rg.otf";
sf::Font FONT_1;

string TEST_LEVEL = "data/test_lvl.txt";
