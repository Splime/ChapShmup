#pragma once
#include "chap_header.h"
#include "gameObject.h"

class Player :
	public GameObject
{
public:
	Player(void);
	virtual ~Player(void);

	void linkBullets(list<GameObject>* bulls); //Gives the player access to the list of bullets
	virtual void update(float secondsPassed);
	void damage(float hurt);
	void heal(float healer);

	float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }
	float getBulletDamage() { return bulletDamage; }

private:
	list<GameObject>* bullets;
	float timeSinceShot;
	float maxHealth, health;
	float bulletDamage;

};

