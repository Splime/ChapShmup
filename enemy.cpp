#include "enemy.h"


Enemy::Enemy() {
    vx = vy = 0;
	ax = ay = 0;
	max_vx = max_vy = MAX_SPEED;
	screenConstrained = false;
	maxHealth = health = 10; //TEMPORARY!

}


Enemy::~Enemy() {

}

void Enemy::update(float secondsPassed) {


    GameObject::update(secondsPassed);
}

void Enemy::damage(float hurt) {
    if (hurt > 0)
        health -= hurt;
    if (health <= 0)
        dead = true;
}
