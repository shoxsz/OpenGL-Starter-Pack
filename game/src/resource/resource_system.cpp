#include "resource_system.hpp"

#include "graphics/bitmap.hpp"

void Resources::registerLoader(ResourceLoader* loader) {
	loaders.push_back(std::shared_ptr<ResourceLoader>(loader));
}

void Resources::unregisterLoader(ResourceLoader* loader) {
	for (auto it = loaders.begin(); it != loaders.end(); ++it) {
		if ((*it).get() == loader) {
			loaders.erase(it);
			return;
		}
	}
}

bool Resources::load(const std::string& resource) {
	if (!isLoaded(resource)) {
		for (auto& loader : loaders) {
			if (loader->accept(resource)) {
				Resource* res = loader->load(resource);
				if (res != nullptr) {
					resources[resource] = std::shared_ptr<Resource>(res);
					return true;
				}
			}
		}
	}

	return false;
}

void Resources::unload(const std::string& resource) {
	if (isLoaded(resource)) {
		resources.erase(resource);
	}
}

bool Resources::isLoaded(const std::string& resource) {
	return resources.find(resource) != resources.end();
}