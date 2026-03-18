#pragma once

#include <chrono>
#include <string>

using namespace std::chrono_literals;

class File {
	private:
		std::string name;
		std::string path;
		std::string extension;
		int size;
		std::time_t dateMod;
		bool isFolder;
	public:
		File(std::string name, std::string extension, int size, std::time_t dateMod, bool isFolder);

		std::string getName() const;
		std::string getExtension() const;
		int getSize() const;
		std::time_t getDateMod() const;
		bool getIsFolder() const;
		std::string getIsFolderStr() const;
		std::string getDateModStr() const;

		std::string getNameWithExtension() const;
};

