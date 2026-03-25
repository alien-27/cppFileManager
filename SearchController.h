#pragma once

#include "File.h"

#include <string>
#include <vector>

class SearchController
{
	private:

	public:
		SearchController();
		std::vector<File> executeSearch(fs::path p, std::string query, int minSize, int maxSize, std::vector<std::string> validExtensions, bool recursive);
};

