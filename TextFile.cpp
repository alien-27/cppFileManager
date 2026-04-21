#include "TextFile.h"

#include <fstream>

namespace fs = std::filesystem;

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
