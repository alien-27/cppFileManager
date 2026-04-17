#include "TextEditorController.h"

#include <fstream>

std::vector<std::string> TextEditorController::readFromFile(std::string filePath) {
    std::vector<std::string> fileData;

    std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
        while (std::getline(file, line)) { // For every line...
            fileData.push_back(line);
        }
	}

    return fileData;
}

bool TextEditorController::saveToFile(std::string filePath, std::vector<std::string> contents) {
    std::ofstream destinationFile(filePath);

    for (std::string line : contents) {
        destinationFile << line << std::endl;
    }
    
    destinationFile.close();

    return true;
}