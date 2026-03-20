#pragma once

#include "File.h"
#include "Input.h"
#include "MainView.h"
#include "MainController.h"

#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

class MainApp
{
	private:
		MainView view;
		MainController ctrl;
		Input input;

		std::vector<File> fileList;
		int selected;
		std::string curPath = fs::current_path().string();
		bool isSearch = false; // if the current list of files is a search result

		void back();
		void enter();
	public:
		MainApp();
};

