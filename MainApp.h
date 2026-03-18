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

		void back();
	public:
		MainApp();
};

