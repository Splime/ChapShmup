#include "enemy.h"


Enemy::Enemy() {
    vx = vy = 0;
	ax = ay = 0;
	max_vx = max_vy = MAX_SPEED;
	screenConstrained = false;
	maxHealth = health = ENEMY_MAX_HEALTH;
	timeSinceShot = ((rand()%100)*ENEMY_RELOAD_TIME)/100.0;
    bullets = NULL;
    shootsBullets = true;
    reloadTime = ENEMY_RELOAD_TIME;
}


Enemy::~Enemy() {

}

void Enemy::linkBullets(list<GameObject>* bulls) {
	bullets = bulls;
}

void Enemy::update(float secondsPassed) {
    //Bullets!
    if (shootsBullets)
    {
        timeSinceShot += secondsPassed;
        if ( timeSinceShot > reloadTime && py > 0) {
            //Spawn a bullet!
            GameObject b;
            b.loadTexture(ENEMY_BULLET_TEXTURE);
            b.setPosition(px + getWidth()/2 - b.getWidth()/2, py + getHeight());
            b.setVelocity(0, ENEMY_BULLET_SPEED);
            bullets->push_back(b);
            timeSinceShot = 0.0 + (rand()%10)/100.0;
        }
    }

    GameObject::update(secondsPassed);
}

void Enemy::damage(float hurt) {
    if (hurt > 0)
        health -= hurt;
    if (health <= 0)
        dead = true;
}
