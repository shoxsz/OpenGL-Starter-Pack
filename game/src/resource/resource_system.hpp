#ifndef _RESOURCE_SYSTEM_HPP_
#define _RESOURCE_SYSTEM_HPP_

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "graphics/texture.hpp"

class Resource {
public:
	virtual ~Resource(){}
};

class ResourceLoader {
public:
	virtual ~ResourceLoader(){}

	virtual bool accept(const std::string& ext) = 0;
	virtual Resource* load(const std::string& resource) = 0;
};

class Resources{
public:
	void registerLoader(ResourceLoader* loader);
	void unregisterLoader(ResourceLoader* loader);

	bool load(const std::string& resource);
	void unload(const std::string& resource);

	template<class T>
	std::shared_ptr<T> get(const std::string& resource);

	bool isLoaded(const std::string& resource);

private:
	std::vector<std::shared_ptr<ResourceLoader>> loaders;
	std::map<std::string, std::shared_ptr<Resource>> resources;
};

template<class T>
std::shared_ptr<T> Resources::get(const std::string& resource) {
	auto find = resources.find(resource);

	if (find != resources.end()) {
		return std::dynamic_pointer_cast<T, Resource>(find->second);
	}

	return nullptr;
}

#endif