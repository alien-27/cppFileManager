#include "Encrypt.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

Encrypt::Encrypt() {}

/// <summary>
/// Takes an unencrypted text file and returns the encrypted contents of it
/// </summary>
/// <param name="path">The chosen filepath</param>
/// <param name="key">The encryption key</param>
/// <returns>The encrypted contents of a file</returns>
std::string Encrypt::encrypt(std::string path, std::string key) { 
	std::string returnStr = "";
	std::ifstream file(path);

	if (!file.is_open()) { // If the file won't open...
		return ""; // Stop here.
	}

	std::string line;
	while (std::getline(file, line)) { // For every line...
		//std::istringstream iss(line);

		std::string newStr = "";
		for (int i = 0; i < line.length(); i++) { // For every character in the line...
			// Shuffle the character
			char keyChar = key[i % key.length()];
			char curChar = line[i] + (keyChar ^ 2);

			newStr += curChar; // Add encrypted char to string
		}

        returnStr += newStr + "\n"; // Add string to total.
    }

	return returnStr;
}

/// <summary>
/// Takes an encrypted file and returns the decrypted contents of it
/// </summary>
/// <param name="path">The chosen filepath</param>
/// <param name="key">The encryption key</param>
/// <returns>The decrypted contents of a file</returns>
std::string Encrypt::decrypt(std::string path, std::string key) {
	std::string returnStr = "";
	std::ifstream file(path);

	if (!file.is_open()) { // If the file won't open...
		return ""; // Stop here.
	}

	std::string line;
	while (std::getline(file, line)) { // For every line...
		//std::istringstream iss(line);

		std::string newStr = "";
		for (int i = 0; i < line.length(); i++) { // For every character in the line...
			// Unshuffle the character. This is basically the reverse of the above function
			char keyChar = key[i % key.length()];
			char curChar = line[i] - (keyChar ^ 2);

			newStr += curChar; // Add decrypted char to string
		}

        returnStr += newStr + "\n"; // Add string to total.
    }

	return returnStr;
}