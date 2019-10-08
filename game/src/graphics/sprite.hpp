#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "texture.hpp"

#include <vector>
#include <memory>

class Sprite {
public:
	Sprite(std::vector<TextureRegion> frames, float fps);

	TextureRegion& getFrame(float deltaTime);

	void setFps(float fps);

	float getFps() const {
		return fps;
	}

private:
	std::vector<TextureRegion> frames;
	float fps;
};

#endif