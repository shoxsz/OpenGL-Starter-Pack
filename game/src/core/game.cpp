#include "game.hpp"

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "input.hpp"
#include "helpers/random.hpp"
#include "resource/resource_system.hpp"

#include <chrono>
#include <iostream>

#define NOW (std::chrono::system_clock::now())

void Game::run(GameListener* listener) {
	std::chrono::duration<double> deltasec;

	if (!init())
		return;

	listener->onInit();

	while (running) {
		auto last = NOW;
		deltasec = NOW - last;

		glClear(GL_COLOR_BUFFER_BIT);

		listener->onUpdate(deltasec.count());
		listener->onRender(deltasec.count());

		glfwSwapBuffers(window);
		glfwPollEvents();

		//std::cout << deltasec.count() << std::endl;
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