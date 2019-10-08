#include "texture.hpp"

Texture::~Texture(){
	glDeleteTextures(1, &id);
	id = 0;
}

void Texture::create(){
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
}

void Texture::setMagFiltering(GLenum filter){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setMinFiltering(GLenum filter){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setWrappingS(GLenum wrap){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void Texture::setWrappingT(GLenum wrap){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::createMipMaps(){
	bind();
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::setUnit(GLuint unit){
	this->unit = unit;
}

void Texture::bind(){
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::loadRGBAUByte(GLuint width, GLuint height, const unsigned char* data, GLuint mipmapLevel){
	this->w = width;
	this->h = height;
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, float u, float v, float u2, float v2):
	texture(texture),
	u(u),
	v(v),
	u2(u2),
	v2(v2)
{}