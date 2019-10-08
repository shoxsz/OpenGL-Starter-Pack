#include "input.hpp"

#include <glfw/glfw3.h>

GLFWwindow* Input::window = nullptr;
std::unique_ptr<InputDispatcher> Input::dispatcher = nullptr;

bool Input::isKeyDown(int key){
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isKeyJustPressed(int key){
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isButtonPressed(int button){
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<int, int> Input::mousePosition(){
	return std::make_pair(0, 0);
}

void Input::registerListener(InputListener* listener) {
	dispatcher->registerListener(listener);
}

void Input::unregisterListener(InputListener* listener) {
	dispatcher->unregisterListener(listener);
}

void Input::init(GLFWwindow* window) {
	Input::window = window;
	dispatcher = std::unique_ptr<InputDispatcher>(new InputDispatcher());

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetWindowCloseCallback(window, windowCloseCallback);
	glfwSetWindowFocusCallback(window, windowFocusChangedCallback);
	glfwSetWindowIconifyCallback(window, windowIconifyCallback);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
}

//GLFW callbacks

void Input::keyCallback(GLFWwindow* window, int key, int scamcode, int state, int mods) {
	if (state == GLFW_PRESS || state == GLFW_REPEAT) {
		dispatcher->onKeyDown(key, state == GLFW_REPEAT, mods);
	}
	else {
		dispatcher->onKeyUp(key, mods);
	}
}

void Input::cursorCallback(GLFWwindow* window, double x, double y) {
	dispatcher->onMouseMove(x, y);
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int state, int mods) {
	if (state == GLFW_PRESS) {
		dispatcher->onMouseButtonDown(button, mods);
	}
	else {
		dispatcher->onMouseButtonUp(button, mods);
	}
}

void Input::windowCloseCallback(GLFWwindow* window) {
	dispatcher->onWindowClose();
}

void Input::windowFocusChangedCallback(GLFWwindow* window, int focused) {
	dispatcher->onWindowFocusChange(focused == GLFW_TRUE);
}

void Input::windowIconifyCallback(GLFWwindow* window, int iconified) {
	dispatcher->onWindowInconify(iconified == GLFW_TRUE);
}

void Input::windowResizeCallback(GLFWwindow* window, int width, int height) {
	dispatcher->onWindowResize(width, height);
}