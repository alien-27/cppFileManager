#include "TextFile.h"

#include <fstream>

namespace fs = std::filesystem;

TextFile::TextFile(fs::directory_entry p) : File(p) {
	//std::ifstream file(getPath());

	//if (file.fail()) { // If the file hasn't opened...
	//	lines = 0;
	//	return;
	//}

	//std::string line;
	//int l = 0;

	//while (std::getline(file, line)) { // For every line...
	//	l++; // Add 1 to count
	//}

	//lines = 45;
}

int TextFile::getLines() {
	std::ifstream file(getPath());

	if (file.fail()) { // If the file hasn't opened...
		return 0; // Return  lines
	}

	std::string line;
	int l = 0;

	while (std::getline(file, line)) { // For every line...
		l++; // Add 1 to count
	}

	return l;
}
