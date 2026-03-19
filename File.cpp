#include "File.h"

#include <chrono>
#include <string>

using namespace std::chrono_literals;

File::File(std::string name, std::string extension, int size, std::time_t dateMod, bool isFolder) {
	this->name = name;
	this->extension = extension;
	this->size = size;
	this->dateMod = dateMod;
	this->isFolder = isFolder;

	if (isFolder) this->extension = "/";
}

std::string File::getName() const { return name; }
std::string File::getExtension() const { return extension; }
int File::getSize() const { return size; }
std::time_t File::getDateMod() const { return dateMod; };
bool File::getIsFolder() const { return isFolder; }

std::string File::getNameWithExtension() const {
	std::string n = name + extension;
	return n;
}

std::string File::getIsFolderStr() const {
	if (isFolder) {
		return "|- ";
	} else {
		return "|  ";
	}
}

std::string File::getDateModStr() const {
	//char buffer[26];

	//std::strftime(buffer, sizeof(buffer), "%A %c", std::localtime(&t)) to-do: try this?

	//if (ctime_s(buffer, sizeof(buffer), &dateMod) == 0) {
	//	return std::string(buffer);
	//}

	return std::ctime(&dateMod);

	return "?";
}