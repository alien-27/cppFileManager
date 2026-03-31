#pragma once

#include "File.h"

namespace fs = std::filesystem;

class TextFile : public File {
	private:
		int lines;
	public:
		TextFile(fs::directory_entry p);
		int getLines();
};
