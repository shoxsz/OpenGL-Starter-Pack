#ifndef _GAME_LISTENER_HPP_
#define _GAME_LISTENER_HPP_

#include "core/game.hpp"
#include "core/input_listener.hpp"

#include "game_renderer.hpp"
#include "game_logics.hpp"

class MyGameListener : public GameListener, public InputListener{
public:
	virtual void onInit() override;
	virtual void onFinish() override;

	virtual void onUpdate(float delta) override;
	virtual void onRender(float delta) override;

	virtual bool onWindowClose() override;
	virtual bool onWindowResize(int width, int height) override;

private:
	std::shared_ptr<GameLogics> logics;
	std::shared_ptr<GameRenderer> renderer;
	std::shared_ptr<UIRenderer> uiRenderer;
};

#endif