#include "searchView.h"

#include <iostream>

/// <summary>
/// Displays a header with a title
/// </summary>
/// <param name="title">The title to be displayed</param>
void searchView::printHeader(std::string title) {
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";
}

/// <summary>
/// Display the search options.
/// </summary>
/// <param name="minSize">The minimum filesize</param>
/// <param name="maxSize">The maximum filesize</param>
/// <param name="validExtensions">A list of valid extensions (can be empty)</param>
/// <param name="validTypes">A list of valid filetypes (can be empty)</param>
/// <param name="recursive">Recursive Search</param>
void searchView::printOptions(int minSize, int maxSize, std::vector<std::string> validExtensions, std::vector<std::string> validTypes, bool recursive) {
	// Put all the extensions in a string
    std::string extStr = "";
    for (std::string s : validExtensions) { extStr += s + ", "; }

	// Put all the filetypes in a string
	std::string typStr = "";
	for (std::string s : validTypes) { typStr += s + ", "; }

	// Display options and wat they are currently set to
    std::cout << "[1]     Set Minimum Size (" << minSize << " bytes)" << std::endl
              << "[2]     Set Maximum Size (" << maxSize << " bytes)" << std::endl
              << "[3]     Search for specific file extensions [" << extStr << "]" << std::endl
              << "[4]     Search for specific file types [" << typStr << "]" << std::endl
              << "[5]     Toggle Recursive Search (" << (recursive ? "TRUE" : "FALSE") << ")" << std::endl
              << "[Enter] Confirm" << std::endl;
}

/// <summary>
/// Get a number input from the user
/// </summary>
/// <param name="msg">The message to display</param>
/// <param name="min">The minimum valid value</param>
/// <param name="max">The maximum valid value</param>
/// <returns>A number input from the user</returns>
int searchView::getIntFromInput(std::string msg, int min, int max) {
	do { // Repeat until we get a valid input
		try {
			printHeader(msg); // Display message
			std::string num = "";
			std::getline(std::cin, num); // Get input

			// Convert number to int
			int numInt = stoi(num);

			if (numInt < min || (numInt > max && max != 0)) { // If out of range..
				throw std::out_of_range("Out of Range"); // Throw error
			}

			return numInt; // Return input
		}
		catch (const std::exception& e) {
			std::cerr << "\033[31mERROR: " << e.what() << "\033[0m" << std::endl;
		}
	} while (true);
}

/// <summary>
/// Get a string input from the user
/// </summary>
/// <returns>A string input from the user</returns>
std::string searchView::getInput() {
	std::string ext = "";
	std::getline(std::cin, ext);
	return ext;
}

/// <summary>
/// Displays an error message
/// </summary>
/// <param name="e"></param>
void searchView::showError(std::string e) {
	std::cerr << "\033[31mERROR: " << e << "\033[0m" << std::endl;
}

/// <summary>
/// Clears the screen
/// </summary>
void searchView::emptyScreen() {
	for (int i = 0; i < 50; i++) {
		std::cout << std::string(120, ' ');
	}
}