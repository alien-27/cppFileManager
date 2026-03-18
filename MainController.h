#pragma once

#include "File.h"

#include <filesystem>
#include <vector>

class MainController {
public:
	std::vector<File> getFiles(std::string path);
	int setSelect(int s, int min, int max);
};

