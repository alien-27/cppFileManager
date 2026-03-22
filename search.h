#pragma once

#include "File.h"

#include <string>
#include <vector>

class search {
private:
	std::string query;

	int minSize = 0;
	int maxSize = 0;
	std::vector<std::string> validExtensions = {};
	bool recursive = true;
public:
	search();
	std::vector<File> doSearch(fs::path p);
};

