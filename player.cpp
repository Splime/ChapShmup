#include "player.h"


Player::Player() {
	vx = vy = 0;
	ax = ay = 0;
	max_vx = max_vy = PLAYER_SPEED;
	screenConstrained = true;
	bullets = NULL;
	timeSinceShot = RELOAD_TIME;
	maxHealth = MAX_HEALTH;
	health = maxHealth;
	bulletDamage = BULLET_DAMAGE;

	flame1.setTexture(FLAME_TEXTURE);
	flame2.setTexture(FLAME_TEXTURE);
	flameL.setTexture(FLAME_TEXTURE);
	flameL.setRotation(90.0);
	flameR.setTexture(FLAME_TEXTURE);
	flameR.setRotation(-90.0);
}


Player::~Player(void) {

}


void Player::linkBullets(list<GameObject>* bulls) {
	bullets = bulls;
}

void Player::update(float secondsPassed) {
	//Deal with controls
	bool left, right, up, down;
	left = right = up = down = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		right = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		left = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (INVERTED_Y_AXIS)
			down = true;
		else
			up = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (INVERTED_Y_AXIS)
			up = true;
		else
			down = true;
	}

	float xcomp = 0.0;
	float ycomp = 0.0;

	if (left && !right)
		xcomp = -PLAYER_ACCEL;
	if (right && !left)
		xcomp = PLAYER_ACCEL;
	if (up && !down)
		ycomp = -PLAYER_ACCEL;
	if (down && !up)
		ycomp = PLAYER_ACCEL;

	//Slow ship down if no keys pressed
	if (!left && !right) {
		if (vx > secondsPassed*PLAYER_DECEL) {
			xcomp = -PLAYER_DECEL;
		}
		else if (vx < -secondsPassed*PLAYER_DECEL) {
			xcomp = PLAYER_DECEL;
		}
		else
			vx = 0;
	}
	if (!up && !down) {
		if (vy > secondsPassed*PLAYER_DECEL) {
			ycomp = -PLAYER_DECEL;
		}
		else if (vy < -secondsPassed*PLAYER_DECEL) {
			ycomp = PLAYER_DECEL;
		}
		else
			vy = 0;
	}

	setAcceleration(xcomp, ycomp);

	//Next up, bullets!
	timeSinceShot += secondsPassed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& timeSinceShot > RELOAD_TIME) {
		//Spawn a bullet!
		GameObject b;
		b.loadTexture(BULLET_TEXTURE);
		b.setPosition(px + getWidth()/2 - b.getWidth()/2, py + 12);
		b.setVelocity(0, -BULLET_SPEED);
		bullets->push_back(b);
		timeSinceShot = 0.0;
	}

	GameObject::update(secondsPassed);
}

void Player::draw(sf::RenderWindow& window)
{
    //Update flame position
    float flame_y = sprite.getPosition().y + sprite.getGlobalBounds().height;
    float flame_x1 = sprite.getPosition().x + sprite.getGlobalBounds().width/2 - flame1.getGlobalBounds().width/2 - 6;
    float flame_x2 = sprite.getPosition().x + sprite.getGlobalBounds().width/2 - flame2.getGlobalBounds().width/2 + 6;
    flame1.setPosition(flame_x1, flame_y);
    flame2.setPosition(flame_x2, flame_y);

    float sideFlame_yR = sprite.getPosition().y + sprite.getGlobalBounds().height + flameL.getGlobalBounds().height - 16;
    float sideFlame_yL = sprite.getPosition().y + sprite.getGlobalBounds().height - 16;
    float flame_xL = sprite.getPosition().x - flameL.getGlobalBounds().width + flameL.getGlobalBounds().width + 4;
    float flame_xR = sprite.getPosition().x + sprite.getGlobalBounds().width - 4;
    flameL.setPosition(flame_xL, sideFlame_yL);
    flameR.setPosition(flame_xR, sideFlame_yR);

    //Draw flames
    if (ay < 0)
    {
        window.draw(flame1);
        window.draw(flame2);
    }
    if (ax > 0)
        window.draw(flameL);
    if (ax < 0)
        window.draw(flameR);
    GameObject::draw(window);
}

void Player::damage(float hurt) {
    if (hurt > 0)
        health -= hurt;
}

void Player::heal(float healer) {
    if (healer < 0)
        health = maxHealth;
    else if (health + healer < maxHealth)
        health += healer;
    else
        health = maxHealth;
}
