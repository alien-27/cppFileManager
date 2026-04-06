#pragma once

#include "File.h"
#include "Input.h"

#include <iostream>
#include <map>
#include <vector>

class MainView {
private:
	std::string setColour(bool selected);
	void printFooter(std::map<std::string, std::string> ctrls);
	Input input;

	std::string errMsg;

	std::map<std::string, std::string> folderCtrls = {
		{ "Enter", "Access" },
		{ "1", "Search" },
		{ "2", "Sort" },
		{ "3", "New" },
		{ "4", "Cut" },
		{ "5", "Copy" },
		{ "6", "Paste" },
		{ "7", "Rename" },
		{ "8", "Delete" },
		{ "9", "Encrypt" },
		{ "0", "End" }
	};

	std::map<std::string, std::string> fileCtrls = {
		{ "Enter", "Access" },
		{ "Backspace", "Back" }
	};
public:
	void displayFiles(std::vector<File> f, int selected);
	void printHeader(std::string title);
	void exitMessage();
	void showError(std::string msg);
	void emptyScreen();
	void printSortOptions();
	void displayDetails(File& f);
};

