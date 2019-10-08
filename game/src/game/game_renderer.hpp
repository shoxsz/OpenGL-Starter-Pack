#ifndef _GAME_RENDERER_HPP_
#define _GAME_RENDERER_HPP_

#include "graphics/sprite_batcher.hpp"
#include "graphics/bitmap_font.hpp"
#include "graphics/camera.hpp"
#include "objects/game_object.hpp"
#include "game_logics.hpp"
#include "resource/texture_loader.hpp"

class Renderer{
public:
	virtual void onInit() = 0;
	virtual void onUpdate(float delta) = 0;
	virtual void onRender(float delta) = 0;
	virtual void onDestroy() = 0;
};

class GameRenderer : public Renderer{
public:
	GameRenderer(std::shared_ptr<GameLogics> gameLogics): gameLogics(gameLogics){}

	virtual void onInit() override;
	virtual void onUpdate(float delta) override {}
	virtual void onRender(float delta) override;
	virtual void onDestroy() override;
private:
	void renderBackground();
	void renderObjects(float delta);
	void renderObject(GameObject* object, float delta);
	bool isVisible(const ObjectBody& body);

	std::shared_ptr<TextureResource> background;

	std::shared_ptr<GameLogics> gameLogics;
	std::shared_ptr<SpriteBatcher> batcher;

	std::shared_ptr<Camera> camera;
	ObjectBody cameraBody;
};

class UIRenderer : public Renderer, public InputListener{
public:
	UIRenderer(std::shared_ptr<GameLogics> gameLogics): gameLogics(gameLogics){}

	virtual void onInit() override;
	virtual void onUpdate(float delta) override;
	virtual void onRender(float delta) override;
	virtual void onDestroy() override;

	virtual bool onKeyDown(int key, bool repeat, int mods) override;
private:

	void createFont();

	std::shared_ptr<GameLogics> gameLogics;
	std::shared_ptr<SpriteBatcher> batcher;

	std::shared_ptr<TextureRegion> life;
	std::shared_ptr<TextureRegion> crystal;

	std::shared_ptr<BitmapFont> font;
	std::shared_ptr<Text> lifeText;
	std::shared_ptr<Text> crystalsText;

	std::shared_ptr<TextureRegion> fontTex;

	int playerCrystals;
	int playerLife;
};

#endif