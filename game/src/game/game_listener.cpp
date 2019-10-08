#include "game_listener.hpp"

#include "resource/resource_system.hpp"
#include "resource/texture_loader.hpp"
#include "core/input.hpp"

GameListener* setup(){
	return new MyGameListener();
}

void MyGameListener::onInit(){
	Input::registerListener(this);

	//init resources
	game->resources->registerLoader(new TextureLoader);
	game->resources->load("resources/images/background.png");
	game->resources->load("resources/images/objects.png");
	game->resources->load("resources/images/font.png");

	logics = std::shared_ptr<GameLogics>(new GameLogics);
	renderer = std::shared_ptr<GameRenderer>(new GameRenderer(logics));
	uiRenderer = std::shared_ptr<UIRenderer>(new UIRenderer(logics));

	logics->onInit();
	renderer->onInit();
	uiRenderer->onInit();

	glClearColor(1, 0, 0, 1);
}

void MyGameListener::onFinish(){
	uiRenderer->onDestroy();
	renderer->onDestroy();
	logics->onDestroy();
}

void MyGameListener::onUpdate(float delta){
	logics->onUpdate(delta);
	renderer->onUpdate(delta);
	uiRenderer->onUpdate(delta);
}

void MyGameListener::onRender(float delta){
	renderer->onRender(delta);
	uiRenderer->onRender(delta);
}

bool MyGameListener::onWindowClose() {
	game->stop();
	return true;
}

bool MyGameListener::onWindowResize(int width, int height) {
	glViewport(0, 0, width, height);
	return true;
}