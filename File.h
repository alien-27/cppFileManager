#pragma once

#include <chrono>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

using namespace std::chrono_literals;

class File {
	private:
		std::string name;
		std::string path;
		std::string type;
		std::string extension;
		int size;
		std::time_t dateMod;
		bool isFolder;
	public:
		File(fs::directory_entry p);

		std::string getName() const;
		std::string getPath() const;
		std::string getType() const;
		std::string getExtension() const;
		int getSize() const;
		std::time_t getDateMod() const;
		bool getIsFolder() const;
		std::string getIsFolderStr() const;
		std::string getDateModStr() const;

		std::string getNameWithExtension() const;
};

