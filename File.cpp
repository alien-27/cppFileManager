#include "File.h"

File::File(fs::directory_entry p) {
	this->name = p.path().filename().stem().string();
	this->path = p.path().string();

	auto ftime = fs::last_write_time(p.path()); // Get the date modified
	auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
	this->dateMod = std::chrono::system_clock::to_time_t(sctp);

	if (p.is_directory()) { // If this is a folder, get the number of items in the folder
		int fileSize = 0;
		for (const auto& entry : fs::directory_iterator(p.path())) { fileSize++; }
		this->size = fileSize;
	}
	else { // else, get the files size
		this->size = (int)p.file_size();
	}

	this->isFolder = p.is_directory();

	if (isFolder) {
		this->extension = "/";
	} else {
		this->extension = p.path().extension().string();
	}
}

std::string File::getName() const { return name; }
std::string File::getPath() const { return path; }
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
#ifdef _WIN32
	char buffer[26];

	if (ctime_s(buffer, sizeof(buffer), &dateMod) == 0) {
		return std::string(buffer);
	}
#else
	return std::ctime(&dateMod);
#endif

	return "?";
}