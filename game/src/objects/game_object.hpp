#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include "object_components.hpp"
#include "core/input_listener.hpp"

class GameObject{
public:
	friend class GameLogics;

	virtual ~GameObject(){}

	virtual void onInit(){}
	virtual void onUpdate(float delta) = 0;
	virtual void onDestroy() {}

	ObjectBody& getBody() { return body; }
	ObjectSprite& getSprite() { return sprite; }

protected:
	GameLogics* logics;

	ObjectBody body;
	ObjectSprite sprite;
};

class Player : public GameObject, public InputListener{
public:
	virtual void onInit() override;
	virtual void onUpdate(float delta) override;
	virtual void onDestroy() override;

	virtual bool onKeyDown(int key, bool repeat, int mods) override;

	void hit();

	ObjectLife& getLife() { return life; }
	ObjectCrystals& getCrystals() { return crystals; }

private:
	ObjectLife life;
	ObjectCrystals crystals;

	const float gravity = -9.8f;
	const float mass = 1.5f;
	float yImpulse = 0.0f;
	float ySpeed = 0.0f;
};

class CollectableObject : public GameObject{
public:
	CollectableObject(std::shared_ptr<Player> player): player(player){}
	virtual ~CollectableObject(){}
	
	virtual void onInit() override;
	virtual void onUpdate(float delta) override;

	virtual void onCollect() = 0;
protected:
	bool rotate = true;
	bool collected = false;
	std::shared_ptr<Player> player;
};

class Life : public CollectableObject{
public:
	Life(std::shared_ptr<Player> player): CollectableObject(player) {}

	virtual void onInit() override;
	virtual void onCollect() override;
private:
	const int lifeBonus = 1;
};

class Crystal : public CollectableObject{
public:
	enum CrystalBonus{
		NORMAL = 1,
		SUPER = 2,
		SUPER_SUPER = 4
	};

	Crystal(std::shared_ptr<Player> player, CrystalBonus bonus);

	virtual void onInit() override;

	void setBonus(CrystalBonus type);
	CrystalBonus getBonus() const { return bonus; }

	virtual void onCollect() override;

private:
	CrystalBonus bonus;
};

class Obstacle : public CollectableObject{
public:
	enum ObstacleDamage{
		NORMAL = 1,
		BAD = 2,
		BAD_BAD = 3
	};

	Obstacle(std::shared_ptr<Player> player, ObstacleDamage damage);

	virtual void onInit() override;

	void setDamage(ObstacleDamage damage);
	ObstacleDamage getDamage() const { return damage; }

	virtual void onCollect() override;

private:
	ObstacleDamage damage;
};

#endif