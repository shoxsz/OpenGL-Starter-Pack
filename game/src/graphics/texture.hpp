#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <gl/glew.h>
#include <memory>

class Texture{
public:
	friend class TextureRegion;

	Texture(const Texture& texture) = delete;
	Texture(Texture&& texture) = delete;

	Texture(){}
	~Texture();

	void create();

	void setMagFiltering(GLenum filter);
	void setMinFiltering(GLenum filter);
	void setWrappingS(GLenum wrap);
	void setWrappingT(GLenum wrap);

	void createMipMaps();

	void setUnit(GLuint unit);
	void bind();

	void loadRGBAUByte(GLuint width, GLuint height, const unsigned char* data, GLuint mipmapLevel = 0);

	float getWidth() const { return w; }
	float getHeight() const { return h; }

	GLuint getId() const { return id; }
	GLuint getUnit() const { return unit; }

private:
	GLuint id = 0;
	GLuint unit = 0;

	float w, h;
};

class TextureRegion{
public:
	TextureRegion(std::shared_ptr<Texture> texture, float u, float v, float u2, float v2);

	std::shared_ptr<Texture> texture;
	float u, v;
	float u2, v2;
};

#endif