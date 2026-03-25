#pragma once

#include <string>
#include <vector>

class searchView {
public:
	void printHeader(std::string title);
	void printOptions(int minSize, int maxSize, std::vector<std::string> validExtensions, bool recursive);
};

