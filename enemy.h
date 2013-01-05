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

    float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }

private:
    float health, maxHealth;


};
