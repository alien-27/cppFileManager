#include "TextEditorController.h"

#include <fstream>

/// <summary>
/// Reads the data from the file and puts it in a vector
/// </summary>
/// <param name="filePath">The path of the file</param>
/// <returns></returns>
std::vector<std::string> TextEditorController::readFromFile(std::string filePath) {
    std::vector<std::string> fileData;

    std::ifstream file(filePath); // Open file

	if (file.is_open()) {
		std::string line;
        while (std::getline(file, line)) { // For every line...
            std::string lineToAdd = "";
            for (char letter : line) {
                if (letter == '	') {
                    lineToAdd += "      ";
                }
                else {
                    lineToAdd += letter;
                }
            }

            fileData.push_back(lineToAdd); // Add it to the vector
        }
	}

    if (fileData.size() == 0) { // If the vector is empty...
        fileData.push_back(""); // Add an empty line
    }

    return fileData;
}

/// <summary>
/// Saves the vector to a file.
/// </summary>
/// <param name="filePath">The file to save to</param>
/// <param name="contents">The vector to be saved</param>
/// <returns>If the file was successfully saved to</returns>
bool TextEditorController::saveToFile(std::string filePath, std::vector<std::string> contents) {
    std::ofstream destinationFile(filePath); // Open file

    if (destinationFile.fail()) {
        return false; // Return false if file couldn't open
    }

    for (std::string line : contents) { // For every line...
        destinationFile << line << std::endl; // Save it to the file.
    }

    return true;
}