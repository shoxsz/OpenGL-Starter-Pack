#include "game_logics.hpp"

#include "helpers/random.hpp"

void GameLogics::onInit() {
	player = std::shared_ptr<Player>(new Player);
	addGameObject(player.get());
	
	nextPos = 0.0f;

	state = READY;
}

void GameLogics::onUpdate(float delta) {
	if (state == PLAYING) {
		updateObjects(delta);
	}
	generateObstacles();
	removePending();
}

void GameLogics::onDestroy() {

}

void GameLogics::nextState() {
	if (state == READY) {
		state = PLAYING;
	}
	else if (state == PLAYING) {
		//kills the player
		while (player->getLife().getLife() > 0) {
			player->hit();
		}
	}
	else if (state == FINISHED) {
		state = READY;
	}
}

void GameLogics::addGameObject(GameObject* object) {
	object->logics = this;
	object->onInit();
	objects.push_back(std::shared_ptr<GameObject>(object));
}

void GameLogics::removeGameObject(GameObject* object) {
	toRemove.push_back(object);
}

void GameLogics::updateObjects(float delta) {
	for(auto it = objects.begin(); it != objects.end(); ++it){
		(*it)->onUpdate(delta);

		if (player->getLife().getLife() == 0) {
			this->nextState();
		}
	}
}

void GameLogics::generateObstacles() {
	float playerX = player->body.getRight();

	float left = playerX + rectDist;
	float right = left + rectWidth;

	if (nextPos < left) {
		nextPos = left;
	}

	while (nextPos <= right) {
		float x = createObstacle(nextPos);
		createLife(x);
		nextPos = x + obstacleDistance;
	}
}

float GameLogics::createObstacle(float x){
	float cut = Random::random(-6.0f, 6.0f);
	float halfGap = gapSize / 2.0f;

	Obstacle* top = new Obstacle(player, Obstacle::BAD);
	Obstacle* bottom = new Obstacle(player, Obstacle::BAD);

	addGameObject(top);
	addGameObject(bottom);

	top->getBody().setX(x);
	top->getBody().setY(cut + halfGap);
	top->getBody().setWidth(1);
	top->getBody().setHeight(10 - (cut + halfGap));
	top->getSprite().setWidth(1);
	top->getSprite().setHeight(10 - (cut + halfGap));

	bottom->getBody().setX(x);
	bottom->getBody().setY(-10);
	bottom->getBody().setWidth(1);
	bottom->getBody().setHeight((cut - halfGap) + 10);
	bottom->getSprite().setWidth(1);
	bottom->getSprite().setHeight((cut - halfGap) + 10);

	return top->body.getRight();
}

void GameLogics::createLife(float x) {
	float y = Random::random(-lifeGapDist, lifeGapDist);
	float type = Random::random(0, 1);

	CollectableObject* collectable;

	if (type <= lifeChance) {
		collectable = new Life(player);
		addGameObject(collectable);
		collectable->getBody().setWidth(0.5f);
		collectable->getBody().setHeight(0.5f);
		collectable->getSprite().setWidth(0.5f);
		collectable->getSprite().setHeight(0.5f);
	}
	else {
		collectable = new Crystal(player, Crystal::NORMAL);
		addGameObject(collectable);
		collectable->getBody().setWidth(2.0f);
		collectable->getBody().setHeight(2.0f);
		collectable->getSprite().setWidth(2.0f);
		collectable->getSprite().setHeight(2.0f);
	}

	collectable->getBody().setX(x + obstacleDistance / 2.0f - collectable->getSprite().getWidth() / 2.0f);
	collectable->getBody().setY(y);
}

void GameLogics::removePending(){
	for (GameObject* object : toRemove) {
		for (auto it = objects.begin(); it != objects.end(); ++it) {
			if ((*it).get() == object) {
				object->onDestroy();
				object->logics = nullptr;
				objects.erase(it);
				break;
			}
		}
	}
	toRemove.clear();
}