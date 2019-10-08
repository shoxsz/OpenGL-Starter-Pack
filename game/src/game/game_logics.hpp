#ifndef _GAME_LOGICS_HPP_
#define _GAME_LOGICS_HPP_

#include <vector>
#include <list>
#include <memory>
#include <utility>

#include "objects/game_object.hpp"

class IGameLogics {
public:
	virtual void onInit() = 0;
	virtual void onUpdate(float delta) = 0;
	virtual void onDestroy() = 0;
};

class GameLogics : public IGameLogics {
public:
	enum State {
		READY = 0,
		PLAYING,
		FINISHED
	};

	virtual void onInit() override;
	virtual void onUpdate(float delta) override;
	virtual void onDestroy() override;

	void nextState();

	void addGameObject(GameObject* object);
	void removeGameObject(GameObject* object);

	const std::list<std::shared_ptr<GameObject>>& getObjects() const { return objects; }

	std::shared_ptr<Player> getPlayer() const { return player; }
	State getState() const { return state; }

private:
	void updateObjects(float delta);
	void generateObstacles();

	float createObstacle(float x);
	void createLife(float x);

	void removePending();

	std::shared_ptr<Player> player;
	std::list<std::shared_ptr<GameObject>> objects;
	std::vector<GameObject*> toRemove;

	State state;
	
	//obstacles rectangle
	const float rectWidth = 50.0f;
	const float rectDist = 10.0f;
	const float obstacleDistance = 10.0f;
	float nextPos = 0.0f;

	//obstacle gen data
	const float gapSize = 3.0f;
	const float lifeGapDist = 5.0f;
	const float lifeChance = 0.2f;
};

#endif