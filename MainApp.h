#pragma once

#include "File.h"
#include "MainView.h"

#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

class MainApp
{
	private:
		MainView view;

		std::vector<File> fileList;
		int selected;
		std::string curPath = fs::current_path().string();;

		std::vector<File> getFiles(std::string path);
		void changeSelect(int a);
	public:
		MainApp();
};

