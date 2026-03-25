#pragma once

#include <string>

class Clipboard {
	private:
		std::string copiedFilepath;
		bool cutting = false;
	public:
		void copy(std::string p, bool c);
		void paste();
};

