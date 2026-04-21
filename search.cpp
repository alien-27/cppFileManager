#include "search.h"

#include <iostream>

search::search() { }

/// <summary>
/// Executes the search
/// </summary>
/// <param name="p">The current filepath</param>
/// <returns>A list of files the user searched for.</returns>
std::vector<File> search::doSearch(fs::path p) {
    // Ask user for search query.
    view.printHeader("Enter your search query (case sensitive):");
    std::getline(std::cin, query);

#ifdef _WIN32
    int const enterChar = 13;
#else
    int const enterChar = 10;
#endif

    do { // Repeat this until enter is pressed
        // Clear scren
        input.clearScreen();
#ifdef _WIN32
        view.emptyScreen();
        input.clearScreen();
#endif
        // Display search options
        view.printHeader("Search options for: '" + query + "'");
        view.printOptions(minSize, maxSize, validExtensions, validTypes, recursive);

        // Get inputs
        int charInput = input.getch();

        switch (charInput) {
            case 49: minSize = view.getIntFromInput("Enter New Minimum Size (in bytes): ", 0, maxSize); break;
            case 50: maxSize = view.getIntFromInput("Enter New Maximum Size (in bytes): ", minSize, 0); break;
            case 51: addExtension(); break;
            case 52: addType(); break;
            case 53: recursive = !recursive; break; // Toggle recursive search
            case enterChar: return ctr.executeSearch(p, query, minSize, maxSize, validExtensions, validTypes, recursive); // [Enter] Confirm
            default: view.showError("Invalid Input"); break;
        }
    } while (true);
}

/// <summary>
/// Add extension to extensions list.
/// </summary>
void search::addExtension() {
    // Ask user
    view.printHeader("Enter an extension you want to search for (formatted '.txt'):");

    do {
        // Get input from user
        std::string inp = view.getInput();
        bool push = true; // If this should be added to the list

        // Don't add if the input is already in the list
        for (std::string t : validTypes) {
            if (t == inp) {
                view.showError("Input already in list!");
                push = false;
            }
        }

        // Don't add if the input is invalid
        if (inp[0] != '.') {
            view.showError("Input must have a '.' at the start.");
            push = false;
        }

        // If this should be added, add it.
        if (push) {
            validExtensions.push_back(inp);
            return;
        }
    } while (true);
}

/// <summary>
/// Add filetype to filetype list.
/// </summary>
void search::addType() {
    // Ask user
    view.printHeader("Enter a file type you want to search for (Text, Audio etc.):");

    do {
        // Get input from user
        std::string inp = view.getInput();
        bool push = true; // If this should be added to the list

        // Don't add if the input is already in the list
        for (std::string t : validTypes) {
            if (t == inp) {
                view.showError("Input already in list!");
                push = false;
            }
        }

        // Don't add if the input is invalid
        if (!ctr.isValidType(inp)) {
            view.showError("Invalid Input");
            push = false;
        }

        // If this should be added, add it.
        if (push) {
            validTypes.push_back(inp);
            return;
        }
    } while (true);
}