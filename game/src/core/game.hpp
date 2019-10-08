#ifndef _GAME_HPP_
#define _GAME_HPP_

struct GLFWwindow;

class GameListener{
public:
	virtual void onInit() = 0;
	virtual void onFinish() = 0;

	virtual void onUpdate(float delta) = 0;
	virtual void onRender(float delta) = 0;
};

class Game{
public:
	Game(){}

	void run(GameListener* listener);
	void stop();

	const GLFWwindow* getWindow() const { return window; }

	class Resources* resources;

private:
	bool init();
	void deInit();

	GLFWwindow* window = nullptr;
	bool running = false;
};

extern Game* game;

#endif