#include "searchView.h"

#include <iostream>

void searchView::printHeader(std::string title) {
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";
}

void searchView::printOptions(int minSize, int maxSize, std::vector<std::string> validExtensions, bool recursive) {
    std::string extStr = "";

    for (std::string s : validExtensions) {
        extStr += s + ", ";
    }

    std::cout << "[1]     Set Minimum Size (" << minSize << " bytes)" << std::endl
              << "[2]     Set Maximum Size (" << maxSize << " bytes)" << std::endl
              << "[3]     Search for specific file extensions [" << extStr << "]" << std::endl
              << "[4]     Search for specific file types [adding later]" << std::endl
              << "[5]     Toggle Recursive Search (" << (recursive ? "TRUE" : "FALSE") << ")" << std::endl
              << "[Enter] Confirm" << std::endl;
}

int searchView::getIntFromInput(std::string msg, int min, int max) {
	do {
		try {
			printHeader(msg);
			std::string num = "";
			std::getline(std::cin, num); // Get input

			if (stoi(num) < min || (stoi(num) > max && max != 0)) { // If out of range..
				throw std::out_of_range("Out of Range"); // Throw error
			}

			return stoi(num); // Return input
		}
		catch (const std::exception& e) {
			std::cerr << "\033[31mERROR: " << e.what() << "\033[0m" << std::endl;
		}
	} while (true);
}

std::string searchView::getExtensionFromInput() {
	printHeader("Enter an extension you want to search for (formatted '.txt'):");
	std::string ext = "";
	std::getline(std::cin, ext); // Get input
	return ext;
}