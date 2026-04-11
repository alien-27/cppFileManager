#include "Encrypt.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

Encrypt::Encrypt() {}

std::string Encrypt::encrypt(std::string path, std::string key) {
	std::string returnStr = "";
	std::ifstream file(path);

	if (!file.is_open()) { // If the file won't open...
		return ""; // Stop here.
	}

	std::string line;
	while (std::getline(file, line)) { // For every line...
		std::istringstream iss(line);

		std::string newStr = "";
		for (int i = 0; i < line.length(); i++) { // For every character in the line...
			char keyChar = key[i % key.length()];
			char curChar = line[i] + (keyChar ^ 2);

			newStr += curChar;
		}

        returnStr += newStr + "\n";
    }

	return returnStr;
}

std::string Encrypt::decrypt(std::string path, std::string key) {
	std::string returnStr = "";
	std::ifstream file(path);

	if (!file.is_open()) { // If the file won't open...
		return ""; // Stop here.
	}

	std::string line;
	while (std::getline(file, line)) { // For every line...
		std::istringstream iss(line);

		std::string newStr = "";
		for (int i = 0; i < line.length(); i++) { // For every character in the line...
			char keyChar = key[i % key.length()];
			char curChar = line[i] - (keyChar ^ 2);

			newStr += curChar;
		}

        returnStr += newStr + "\n";
    }

	return returnStr;
}