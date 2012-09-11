#include "gameObject.h"

GameObject::GameObject(void) {
	vx = vy = 0;
	ax = ay = 0;
	max_vx = max_vy = MAX_SPEED;
	screenConstrained = false;

	dead = false;
}

GameObject::~GameObject(void) {

}

void GameObject::update(float timePassed) {
	//Calculate new position based on v and a
	float deltax1 = px + vx*timePassed;
	float vx2 = vx + ax*timePassed;
	if (vx2 > max_vx)
		vx2 = max_vx;
	if (vx2 < -max_vx)
		vx2 = -max_vx;
	float deltax2 = px + vx2*timePassed;
	float x2 = (deltax1 + deltax2)/2.0;

	float deltay1 = py + vy*timePassed;
	float vy2 = vy + ay*timePassed;
	if (vy2 > max_vy)
		vy2 = max_vy;
	if (vy2 < -max_vy)
		vy2 = -max_vy;
	float deltay2 = py + vy2*timePassed;
	float y2 = (deltay1 + deltay2)/2.0;

	setPosition(x2, y2);

	//New velocity
	vx = vx2; vy = vy2;

	//Out of bounds? Fix it!
	if (screenConstrained) {
		if (px < GAME_ZONE_X) {
			px = GAME_ZONE_X;
			if (vx < 0)
				vx = 0;
			if (ax < 0)
				ax = 0;
		}
		if (py < GAME_ZONE_Y) {
			py = GAME_ZONE_Y;
			if (vy < 0)
				vy = 0;
			if (ay < 0)
				ay = 0;
		}
		if (px + sprite.getTextureRect().width > GAME_ZONE_X + GAME_ZONE_WIDTH) {
			px = GAME_ZONE_X + GAME_ZONE_WIDTH - sprite.getTextureRect().width;
			if (vx > 0)
				vx = 0;
			if (ax > 0)
				ax = 0;
		}
		if (py + sprite.getTextureRect().height > GAME_ZONE_Y + GAME_ZONE_HEIGHT) {
			py = GAME_ZONE_Y + GAME_ZONE_HEIGHT - sprite.getTextureRect().height;
			if (vy > 0)
				vy = 0;
			if (ay > 0)
				ay = 0;
		}

		setPosition(px, py);
	}
}

void GameObject::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void GameObject::loadImageFile(string filename) {
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
}

void GameObject::loadTexture(sf::Texture& tex) {
	sprite.setTexture(tex);
}

void GameObject::setVelocity(float x, float y) {
	vx = x;
	vy = y;
}

void GameObject::setAcceleration(float x, float y) {
	ax = x;
	ay = y;
}

void GameObject::setPosition(float x, float y) {
	px = x; py = y;
	sprite.setPosition((int)x, (int)y);
}

bool GameObject::rectCollide(GameObject& other) {
	return getX() < other.getX() + other.getWidth()
			&& getX() + getWidth() > other.getX()
			&& getY() < other.getY() + other.getHeight()
			&& getY() + getHeight() > other.getY();
}
