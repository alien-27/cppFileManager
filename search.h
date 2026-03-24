#pragma once

#include "File.h"
#include "Input.h"
#include "searchView.h"

#include<string>

class search {
private:
	Input input;
	std::string query;
	searchView view;

	int minSize = 0;
	int maxSize = 0;
	std::vector<std::string> validExtensions = {};
	bool recursive = true;
public:
	search();
	std::vector<File> doSearch(fs::path p);
};

