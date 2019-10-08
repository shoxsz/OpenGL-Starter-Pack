#include "texture_loader.hpp"

#include "graphics/bitmap.hpp"

bool TextureLoader::accept(const std::string& resource){
	std::string ext = resource.substr(resource.size() - 3);

	return ext == "png";
}

Resource* TextureLoader::load(const std::string& resource){
	TextureResource* textureRes = new TextureResource();

	std::unique_ptr<Bitmap> bitmap = Bitmap::createFromFile(resource);

	if (bitmap == nullptr) {
		return nullptr;
	}

	textureRes->texture = std::shared_ptr<Texture>(new Texture());
	textureRes->texture->create();
	textureRes->texture->bind();
	textureRes->texture->setMinFiltering(GL_LINEAR);
	textureRes->texture->setMagFiltering(GL_LINEAR);
	textureRes->texture->setWrappingS(GL_CLAMP);
	textureRes->texture->setWrappingT(GL_CLAMP);
	textureRes->texture->loadRGBAUByte(bitmap->getWidth(), bitmap->getHeight(), bitmap->getData());

	GLenum error = glGetError();

	return textureRes;
}