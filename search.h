#pragma once

#include "File.h"
#include "Input.h"
#include "searchView.h"
#include "SearchController.h"

#include <string>

class search {
	private:
		SearchController ctr;
		searchView view;
		Input input;

		std::string query;

		int minSize = 0;
		int maxSize = 0;
		std::vector<std::string> validExtensions = {};
		bool recursive = true;
	public:
		search();
		std::vector<File> doSearch(fs::path p);
};

