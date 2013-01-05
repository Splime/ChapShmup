#pragma once
#include "chap_header.h"
#include "gameObject.h"

class Enemy : public GameObject
{
public:
    Enemy();
    virtual ~Enemy();

    virtual void update(float secondsPassed);
    void damage(float hurt);
    void linkBullets(list<GameObject>* bulls); //Gives the enemy access to the list of bullets

    float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }

private:
    float health, maxHealth;
    list<GameObject>* bullets;
	float timeSinceShot;
	bool shootsBullets;
	float reloadTime;

};
