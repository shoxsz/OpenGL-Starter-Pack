#include "sprite.hpp"

Sprite::Sprite(std::vector<TextureRegion> frames, float fps) {
	this->frames = frames;
	setFps(fps);
}

TextureRegion& Sprite::getFrame(float deltaTime) {
	unsigned int frameIdx = (int)(deltaTime / fps) % frames.size();
	return frames[frameIdx];
}

void Sprite::setFps(float fps) {
	this->fps = fps;
}