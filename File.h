#pragma once

#include <string>

class File {
	private:
		std::string name;
		std::string path;
		std::string extension;
		int size;
		bool isFolder;
	public:
		File(std::string name, std::string extension, int size, bool isFolder);

		std::string getName() const;
		std::string getExtension() const;
		int getSize() const;
		bool getIsFolder() const;
		std::string getIsFolderStr() const;

		std::string getNameWithExtension() const;

		std::string toString();
};

