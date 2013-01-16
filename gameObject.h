#pragma once
#include "chap_header.h"
class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual void update(float timePassed);
	virtual void draw(sf::RenderWindow& window);

	void loadImageFile(string filename);
	void loadTexture(sf::Texture& tex);
	void setVelocity(float x, float y);
	void setAcceleration(float x, float y);
	void setPosition(float x, float y);
	void setTimer(float seconds);
	void kill() { dead = true; }

	float getX() { return px; }
	float getY() { return py; }
	int getWidth() { return sprite.getGlobalBounds().width; }
	int getHeight() { return sprite.getGlobalBounds().height; }
	bool isDead() { return dead; }
	bool rectCollide(GameObject& other); //Rectangular Collision

protected:
	sf::Texture texture;
	sf::Sprite sprite;
	float vx, vy; //Velocity, x and y components
	float max_vx, max_vy; //Max speed
	float ax, ay; //Acceleration, x and y components
	float px, py; //Position
	bool screenConstrained;

	bool timed;
	float timeLeft;

	bool dead;
};

