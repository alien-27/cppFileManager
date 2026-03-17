#include "File.h"

#include <string>

File::File(std::string name, std::string extension, int size, bool isFolder) {
	this->name = name;
	this->extension = extension;
	this->size = size;
	this->isFolder = isFolder;

	if (isFolder) this->extension = "/";
}

std::string File::getName() const { return name; }
std::string File::getExtension() const { return extension; }
int File::getSize() const { return size; }
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

std::string File::toString() {
	std::string returnString;

	if (isFolder) {
		returnString = "|- ";
	} else {
		returnString = "|  ";
	}

	returnString += name + " - " + std::to_string(size) + " bytes";

	return returnString;
}