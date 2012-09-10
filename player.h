#pragma once
#include "chap_header.h"
#include "gameObject.h"

class Player :
	public GameObject
{
public:
	Player(void);
	virtual ~Player(void);

	void linkBullets(list<GameObject>* bulls);
	virtual void update(float secondsPassed);

private:
	list<GameObject>* bullets;
	float timeSinceShot;

};

