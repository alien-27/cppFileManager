#pragma once

#include "File.h"

#include <iostream>
#include <vector>

class MainView {
private:
	void setColour(bool selected);
public:
	void displayFiles(std::vector<File> f, int selected);
};

