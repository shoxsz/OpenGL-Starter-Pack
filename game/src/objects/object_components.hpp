#ifndef _OBJECT_COMPONENTS_HPP_
#define _OBJECT_COMPONENTS_HPP_

#include "graphics/sprite.hpp"

#include <memory>
#include <glm/glm.hpp>

class ObjectComponent {
public:
	virtual ~ObjectComponent(){}
};

class ObjectBody : public ObjectComponent{
public:
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	void setWidth(float width) { this->width = width; }
	void setHeight(float height) { this->height = height; }

	void setSpeed(float speed) { this->speed = speed; }

	float getX() const { return x; }
	float getY() const { return y; }

	float getRight() const { return x + width; }
	float getTop() const { return y + height; }

	float getWidth() const { return width; }
	float getHeight() const { return height; }

	float getCenterX() const { return x + (width / 2); }
	float getCenterY() const { return y + (height / 2); }

	float getSpeed() const { return speed; }

	bool testCollision(const ObjectBody& other) {
		if (other.x + other.width < x) return false;
		if (other.x > x + width) return false;
		if (other.y + other.height < y) return false;
		if (other.y > y + height) return false;
		return true;
	}

	float getSqrDistance(const ObjectBody& other) {
		float diffX = other.x - x;
		float diffY = other.y - y;
		return diffX * diffX + diffY * diffY;
	}

private:
	float x = 0, y = 0;
	float width = 1, height = 1;
	float speed = 0;
};

class ObjectSprite : public ObjectComponent {
public:
	TextureRegion& getFrame(float delta) {
		time += delta;
		return sprite->getFrame(time);
	}

	void setSprite(std::shared_ptr<Sprite> sprite) { this->sprite = sprite; }
	std::shared_ptr<Sprite> getSprite() const { return sprite; }

	void setWidth(float width) { this->width = width; }
	void setHeight(float height) { this->height = height; }

	float getWidth() const { return width; }
	float getHeight() const { return height; }

	glm::mat4& getTransform() { return transform; }

private:
	float time = 0.0f;
	float width = 1.0f, height = 1.0f;
	std::shared_ptr<Sprite> sprite;
	glm::mat4 transform = glm::mat4(1);
};

class ObjectLife : public ObjectComponent {
public:

	void setLife(int life) { this->life = life; }
	int getLife() const { return life; }

	void addLife(int life) { this->life += life; }

private:
	int life = 0;
};

class ObjectCrystals : public ObjectComponent {
public:

	void setCrystals(int crystals) { this->crystals = crystals; }
	int getCrystals() const { return crystals; }

	void addCrystals(int crystals) { this->crystals += crystals; }

private:
	int crystals = 0;
};

#endif