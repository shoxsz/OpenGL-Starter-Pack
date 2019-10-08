#include "game_object.hpp"

#include "core/input.hpp"
#include "core/game.hpp"
#include "resource/texture_loader.hpp"

#include "game/game_logics.hpp"
#include "game/defs.hpp"

#include <glm/gtc/matrix_transform.hpp>

//PLAYER
void Player::onInit(){
	GameObject::onInit();

	body.setWidth(1.0f);
	body.setHeight(1.0f);

	body.setX(0.0f);
	body.setY(0.0f);

	body.setSpeed(5);

	life.setLife(2);

	std::shared_ptr<TextureResource> texture = game->resources->get<TextureResource>("resources/images/objects.png");

	sprite.setSprite(std::shared_ptr<Sprite>(new Sprite({
		//TextureRegion(std::shared_ptr<Texture>(texture->texture), 0, 0.1f, 146.0f / 512.0f, 70.0f / 512.0f)
		TextureRegion(std::shared_ptr<Texture>(texture->texture), 0.0f, 186.0f / 256.0f, 146.0f / 512.0f, 1.0f)
	},
	10)));

	sprite.setWidth(2.0f);
	sprite.setHeight(1.5f);

	Input::registerListener(this);
}

void Player::onUpdate(float delta){
	float x = body.getX();
	float y = body.getY();

	ySpeed += (gravity * mass + yImpulse) * delta;

	if (ySpeed >= 5.0f) {
		yImpulse = 0.0f;
	}

	x += body.getSpeed() * delta;
	y += ySpeed * delta;

	if (y + body.getHeight() > WORLD_TOP) {
		y = WORLD_TOP - body.getHeight();
	}

	if (y <= WORLD_BOTTOM) {
		y = WORLD_BOTTOM;
	}

	body.setX(x);
	body.setY(y);

	/*
		5 = 45
		-5 = 0
	*/
	float radians = -3.0f + (5.0f + std::min(std::max(ySpeed, -5.0f), 5.0f)) * ((45.0f + 3) / 10.0f);
	if (getLife().getLife() == 0) {
		radians = -90.0f;
	}

	auto& transform = sprite.getTransform();
	transform = glm::translate(glm::mat4(1), glm::vec3(sprite.getWidth() / 2.0f, sprite.getHeight() / 2.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(radians), glm::vec3(0, 0, 1.0f));
	transform = glm::translate(transform, glm::vec3(-sprite.getWidth() / 2.0f, -sprite.getHeight() / 2.0f, 0.0f));
}

void Player::onDestroy() {
	Input::unregisterListener(this);
}

bool Player::onKeyDown(int key, bool repeat, int mods) {
	if (!repeat && key == GKEY_UP && life.getLife() > 0) {
		ySpeed = std::max(0.0f, ySpeed);
		yImpulse = -5 * gravity;
		return false;
	}

	return false;
}

void Player::hit() {
	life.addLife(-1);
	if (life.getLife() == 0) {
		body.setSpeed(0.0f);
	}
}

//COLLECTABLE
void CollectableObject::onInit() {
	collected = false;
}

void CollectableObject::onUpdate(float delta){
	if (!collected && player->getBody().testCollision(body) && player->getLife().getLife() > 0) {
		onCollect();
	}
	else if (player->getBody().getX() > body.getRight() && player->getBody().getSqrDistance(body) >= 1000.0f) {
		logics->removeGameObject(this);
	}

	if (rotate) {
		auto& transform = sprite.getTransform();
		transform = glm::translate(transform, glm::vec3(sprite.getWidth() / 2.0f, sprite.getHeight() / 2.0f, 0));
		transform = glm::rotate(transform, glm::radians(90 * delta), glm::vec3(0, 0, 1.0f));
		transform = glm::translate(transform, glm::vec3(-sprite.getWidth() / 2.0f, -sprite.getHeight() / 2.0f, 0));
	}
}

//LIFE
void Life::onInit() {
	CollectableObject::onInit();
	body.setWidth(1);
	body.setHeight(1);
	body.setSpeed(0);

	std::shared_ptr<TextureResource> tex = game->resources->get<TextureResource>("resources/images/objects.png");

	sprite.setSprite(std::shared_ptr<Sprite>(new Sprite(
		{
			TextureRegion(tex->texture, (2 * 146.0f) / 512.0f, 110.0 / 256.0f, (3 * 146.0f) / 512.0f, 1.0f)
		},
		1
	)));

	sprite.setWidth(1.0f);
	sprite.setHeight(1.0f);
}

void Life::onCollect() {
	player->getLife().addLife(lifeBonus);
	logics->removeGameObject(this);
}

//CRYSTAL
void Crystal::onInit() {
	CollectableObject::onInit();
	body.setWidth(1);
	body.setHeight(1);
	body.setSpeed(0);

	std::shared_ptr<TextureResource> tex = game->resources->get<TextureResource>("resources/images/objects.png");

	sprite.setSprite(std::shared_ptr<Sprite>(new Sprite(
		{
			TextureRegion(tex->texture, 146.0f / 512.0f, 110.0f / 256.0f, (2 * 146.0f) / 512.0f, 1.0f)
		},
		1
	)));
	sprite.setWidth(1.0f);
	sprite.setHeight(1.0f);
}

Crystal::Crystal(std::shared_ptr<Player> player, Crystal::CrystalBonus bonus) : CollectableObject(player){
	setBonus(bonus);
}

void Crystal::setBonus(Crystal::CrystalBonus bonus) {
	this->bonus = bonus;
}

void Crystal::onCollect() {
	player->getCrystals().addCrystals(1);
	logics->removeGameObject(this);
}

//OBSTACLE
void Obstacle::onInit() {
	CollectableObject::onInit();
	body.setWidth(1);
	body.setHeight(1);
	body.setSpeed(0);

	std::shared_ptr<TextureResource> tex = game->resources->get<TextureResource>("resources/images/objects.png");

	sprite.setSprite(std::shared_ptr<Sprite>(new Sprite(
		{
			TextureRegion(tex->texture, (3 * 147.0f) / 512.0f, 0.0f, 1.0f, 1.0f)
		},
		1
	)));
	body.setWidth(1);
	body.setHeight(1);

	rotate = false;
}

Obstacle::Obstacle(std::shared_ptr<Player> player, Obstacle::ObstacleDamage damage) : CollectableObject(player) {
	setDamage(damage);
}

void Obstacle::setDamage(Obstacle::ObstacleDamage damage) {
	this->damage = damage;
}

void Obstacle::onCollect() {
	player->hit();
	logics->removeGameObject(this);
}