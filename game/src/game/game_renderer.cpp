#include "game_renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "core/game.hpp"
#include "defs.hpp"
#include "core/input.hpp"

void GameRenderer::onInit(){
	background = game->resources->get<TextureResource>("resources/images/background.png");

	batcher = SpriteBatcher::create("resources/shaders/vertex_shader.gl", "resources/shaders/fragment_shader.gl");
	camera = std::shared_ptr<Camera>(new Camera);

	cameraBody.setY(-10.0f);
	cameraBody.setWidth(20.0f);
	cameraBody.setHeight(20.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GameRenderer::onRender(float delta){
	renderBackground();
	renderObjects(delta);
}

void GameRenderer::renderBackground() {
	batcher->setProjection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f));
	batcher->setView(glm::mat4(1));

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(-10, WORLD_BOTTOM, 0));

	TextureRegion background(this->background->texture, 0, 0, 1, 1);
	batcher->begin();
	batcher->draw(&background, CAMERA_WIDTH, CAMERA_HEIGHT, transform);
	batcher->end();
}

void GameRenderer::renderObjects(float delta) {
	const auto& objects = gameLogics->getObjects();

	if (objects.size() == 0) return;

	auto player = gameLogics->getPlayer();
	camera->setTranslation(-player->getBody().getX(), 0, 0);
	camera->setOrtho(-10, 10, -10, 10);

	cameraBody.setX(player->getBody().getX() - 10.0f);

	batcher->setProjection(camera->projection);
	batcher->setView(camera->view);

	batcher->begin();

	for (const auto& object : objects) {
		GameObject* objectPtr = object.get();
		if (objectPtr == player.get()) continue;
		renderObject(objectPtr, delta);
	}

	renderObject(gameLogics->getPlayer().get(), delta);

	batcher->end();
}

void GameRenderer::renderObject(GameObject* object, float delta) {
	ObjectBody& body = object->getBody();
	ObjectSprite& sprite = object->getSprite();

	if (!isVisible(body)) return;

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(body.getX(), body.getY(), 0.0f));
	transform *= sprite.getTransform();

	batcher->draw(&sprite.getFrame(delta), sprite.getWidth(), sprite.getHeight(), transform);
}

void GameRenderer::onDestroy(){

}

bool GameRenderer::isVisible(const ObjectBody& body) {
	return cameraBody.testCollision(body);
}

//UIRenderer ======================================

void UIRenderer::onInit() {
	Input::registerListener(this);

	auto lifeRes = game->resources->get<TextureResource>("resources/images/objects.png");
	auto crystalRes = game->resources->get<TextureResource>("resources/images/objects.png");

	life = std::shared_ptr<TextureRegion>(new TextureRegion(lifeRes->texture, (2 * 146.0f) / 512.0f, 110.0 / 256.0f, (3 * 146.0f) / 512.0f, 1.0f));
	crystal = std::shared_ptr<TextureRegion>(new TextureRegion(crystalRes->texture, 146.0f / 512.0f, 110.0f / 256.0f, (2 * 146.0f) / 512.0f, 1.0f));

	batcher = SpriteBatcher::create("resources/shaders/vertex_shader.gl", "resources/shaders/fragment_shader.gl");
	
	playerLife = gameLogics->getPlayer()->getLife().getLife();
	playerCrystals = gameLogics->getPlayer()->getCrystals().getCrystals();

	createFont();
}

void UIRenderer::createFont() {
	auto fontRes = game->resources->get<TextureResource>("resources/images/font.png");

	BitmapFont::CharacterSet charset;

	charset['0'] = { 417, 9, 38, 52 };
	charset['1'] = { 6, 10, 36, 50 };
	charset['2'] = { 50, 9, 37, 51 };
	charset['3'] = { 97, 9, 37, 52 };
	charset['4'] = { 139, 10, 41, 50 };
	charset['5'] = { 187, 10, 37, 51 };
	charset['6'] = { 233, 9, 38, 52 };
	charset['7'] = { 279, 10, 37, 50 };
	charset['8'] = { 324, 10, 32, 52 };
	charset['9'] = { 370, 9, 37, 52 };

	font = std::shared_ptr<BitmapFont>(new BitmapFont(fontRes->texture, charset));
	fontTex = std::shared_ptr<TextureRegion>(new TextureRegion(fontRes->texture, 0, 0, 1, 1));

	lifeText = std::shared_ptr<Text>(new Text(font));
	crystalsText = std::shared_ptr<Text>(new Text(font));

	lifeText->setText(std::to_string(playerLife));
	crystalsText->setText(std::to_string(playerCrystals));
}

void UIRenderer::onUpdate(float delta) {
	int currentLife = gameLogics->getPlayer()->getLife().getLife();
	if (currentLife != playerLife) {
		playerLife = currentLife;
		lifeText->setText(std::to_string(playerLife));
	}

	int currentCrystals = gameLogics->getPlayer()->getCrystals().getCrystals();
	if (currentCrystals != playerCrystals) {
		playerCrystals = currentCrystals;
		crystalsText->setText(std::to_string(playerCrystals));
	}
}

void UIRenderer::onRender(float delta) {
	glm::vec3 translation(1.0f, 1.0f, 0.0f);

	auto batcherView = glm::translate(glm::mat4(1), glm::vec3(-320.0f, -320.0f, 0.0f));

	auto lifeTransform = glm::translate(glm::mat4(1), glm::vec3(10.0f, 10.0f, 0.0f));
	auto lifeTextTransform = glm::translate(glm::mat4(1), glm::vec3(50.0f, 10.0f, 0.0f));
	
	auto crystalTransform = glm::translate(glm::mat4(1), glm::vec3(100.0f, 10.0f, 0.0f));
	auto crystalTextTransform = glm::translate(glm::mat4(1), glm::vec3(150.0f, 10.0f, 0.0));

	batcher->setProjection(glm::ortho(-320.0f, 320.0f, -320.0f, 320.0f));
	batcher->setView(batcherView);

	batcher->begin();

	//life
	batcher->draw(life.get(), 32, 32, lifeTransform);
	batcher->draw(
		fontTex.get(),
		lifeText->getVertices(),
		lifeText->getIndices(),
		lifeTextTransform);

	//crystals
	batcher->draw(crystal.get(), 32, 32, crystalTransform);
	batcher->draw(
		fontTex.get(),
		crystalsText->getVertices(),
		crystalsText->getIndices(),
		crystalTextTransform);

	batcher->end();
}

void UIRenderer::onDestroy() {
	Input::unregisterListener(this);
}


bool UIRenderer::onKeyDown(int key, bool repeat, int mods) {
	if (gameLogics->getState() != GameLogics::PLAYING) {
		gameLogics->nextState();
		return true;
	}
	return false;
}