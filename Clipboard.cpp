#include "Clipboard.h"

#include <filesystem>

namespace fs = std::filesystem;

/// <summary>
/// Stores a filepath to be pasted
/// </summary>
/// <param name="p">The Filepath</param>
/// <param name="c">If we want to cut the file</param>
void Clipboard::copy(std::string p, bool c) {
	cutting = c;
	copiedFilepath = p;
}

/// <summary>
/// Pastes the stored file into the current directory.
/// </summary>
void Clipboard::paste() {
	if (copiedFilepath == "") return; // Stop if there is bothing copied.
	if (!fs::exists(copiedFilepath)) return; // Stop if the copied file has been removed.

	fs::path p(copiedFilepath);

	std::string name = p.filename().stem().string();
	std::string extension = p.extension().string();

	if (fs::exists(name + extension)) { // If there is a file with this name in the directory...
		do {
			name += " (Copy)"; // Change the name
		} while (fs::exists(name + extension)); // Do this until there is no conflict
	}

	fs::copy(p, name + extension); // Copy the file

	if (cutting) { // If cutting...
		fs::remove(p); // ...Cut the file
	}

	copiedFilepath = ""; // Reset clipboard.
}