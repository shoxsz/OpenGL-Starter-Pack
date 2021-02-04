#include "game.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "input.hpp"
#include "helpers/random.hpp"
#include "resource/resource_system.hpp"

#include <chrono>

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now().time_since_epoch()))

void Game::run(GameListener* listener) {
	std::chrono::duration<double> deltasec;

	if (!init())
		return;

	listener->onInit();

	auto start = NOW;
	while (running) {
		auto end = NOW;
		float deltasec = (end - start).count() / 1000.0f;
		start = end;

		glClear(GL_COLOR_BUFFER_BIT);

		listener->onUpdate(deltasec);
		listener->onRender(deltasec);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	listener->onFinish();
	deInit();
}

void Game::stop() {
	running = false;
}

bool Game::init() {
	if (!glfwInit()) {
		return false;
	}

	window = glfwCreateWindow(800, 640, "Game", nullptr, nullptr);

	if (window == nullptr) {
		return false;
	}

	glfwMakeContextCurrent(window);

	GLenum glew = glewInit();
	if (glew != GLEW_OK) {
		return false;
	}

	Random::init();
	Input::init(window);

	resources = new Resources();

	running = true;
	return true;
}

void Game::deInit(){
	running = false;
	delete resources;
	glfwDestroyWindow(window);
	glfwTerminate();
}