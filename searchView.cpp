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
              << "[4]     Search for specific file types (n bytes)" << std::endl
              << "[5]     Toggle Recursive Search (" << (recursive ? "TRUE" : "FALSE") << ")" << std::endl
              << "[Enter] Confirm" << std::endl;
}