#ifndef _FILES_HPP_
#define _FILES_HPP_

#include <string>

class Files{
public:
	static bool loadContents(const std::string& fileName, std::string& contents);
};

#endif