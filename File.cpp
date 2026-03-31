#include "File.h"

#include <algorithm>
#include <cctype>
#include <unordered_set>

File::File(fs::directory_entry p) {
	this->name = p.path().filename().stem().string();
	this->path = p.path().string();

	try {
		auto ftime = fs::last_write_time(p.path()); // Get the date modified
		auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
		this->dateMod = std::chrono::system_clock::to_time_t(sctp);
	} catch (const std::filesystem::filesystem_error& e) {
		//view.showError(e.what());
		auto now = std::chrono::system_clock::now();
		this->dateMod = std::chrono::system_clock::to_time_t(now);
	}

	try {
		if (p.is_directory()) { // If this is a folder, get the number of items in the folder
			int fileSize = 0;

			for (const auto& entry : fs::directory_iterator(p.path())) { fileSize++; }
			this->size = fileSize;
		}
		else { // else, get the files size
			int fileSize = (int)p.file_size();
			if (fileSize < 0) {
				this->size = 0;
			} else {
				this->size = fileSize;
			}
		}
	} catch (const std::filesystem::filesystem_error& e) {
		//return e.what();
		this->size = 0;
	}

	this->isFolder = p.is_directory();

	if (isFolder) {
		this->extension = "/";
		this->type = "Folder";
	} else {
		std::string ext = p.path().extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

		this->extension = ext;

		// get file type
		std::unordered_set<std::string> text = { ".txt", ".text", ".md", ".csv", ".xml", ".json", ".log" };
		std::unordered_set<std::string> document = { ".pdf", ".docx", ".pptx", ".xlsx", ".odt", ".pages" };
		std::unordered_set<std::string> code = { ".sln", ".cpp", ".cs", ".css", ".h", ".c", ".py", ".html", ".htm", ".css", ".js", ".php", ".lua", ".java", ".sql", ".rb", ".rs", ".go", ".sh", ".ps1", ".yml", ".yaml", ".bat"};
		std::unordered_set<std::string> graphic = { ".png", ".jpeg", ".jpg", ".webp", ".svg", ".eps", ".gif", ".tiff", ".mpeg", ".bmp", ".raw", ".ai", ".psd", ".xcf", ".kra", ".indd", ".heic"};
		std::unordered_set<std::string> model = { ".obj", ".fbx", ".stl", ".gltf", ".glb", ".usdz", ".step", ".stp", ".blend", ".3mf", ".max", ".sldprt", ".dwg"};
		std::unordered_set<std::string> video = { ".mp4", ".avi", ".mov", ".mkv", ".wmv", ".webm"};
		std::unordered_set<std::string> audio = { ".mp3", ".wav", ".acc", ".ogg", ".flac", ".aac", ".m4a", ".aiff", ".alac", ".wma"};
		std::unordered_set<std::string> archive = { ".zip", ".rar", ".7z", ".tar", ".gzip"};
		std::unordered_set<std::string> application = { ".exe", ".app", ".apk", ".msi"};

		if (text.count(extension)) {
			this->type = "Text";
		} else if (document.count(extension)) {
			this->type = "Document";
		} else if (code.count(extension)) {
			this->type = "Code";
		} else if (graphic.count(extension)) {
			this->type = "Graphic";
		} else if (model.count(extension)) {
			this->type = "Model";
		} else if (video.count(extension)) {
			this->type = "Video";
		} else if (audio.count(extension)) {
			this->type = "Audio";
		} else if (archive.count(extension)) {
			this->type = "Archive";
		} else if (application.count(extension)) {
			this->type = "Application";
		} else {
			this->type = "File";
		}
	}
}

std::string File::getName() const { return name; }
std::string File::getPath() const { return path; }
std::string File::getType() const { return type; }
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