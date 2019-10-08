#ifndef _TEXTURE_LOADER_HPP_
#define _TEXTURE_LOADER_HPP_

#include "resource_system.hpp"

class TextureResource : public Resource{
public:
	std::shared_ptr<Texture> texture;
};

class TextureLoader : public ResourceLoader{
public:
	virtual bool accept(const std::string& resource) override;
	virtual Resource* load(const std::string& resource) override;
};

#endif