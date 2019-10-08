#include "files.hpp"

#include <fstream>

bool Files::loadContents(const std::string& fileName, std::string& contents){
	std::string line;
	std::ifstream fileStream(fileName);

	if (!fileStream.is_open()) {
		return false;
	}

	contents.clear();
	while (std::getline(fileStream, line)) {
		contents += line + "\n";
	}

	return true;
} 