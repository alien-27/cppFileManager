#pragma once

#include "File.h"

#include <iostream>
#include <vector>

class MainView {
private:
	std::string setColour(bool selected);
	void printFooter();
public:
	void displayFiles(std::vector<File> f, int selected);
	void printHeader(std::string title);
	void exitMessage();
};

