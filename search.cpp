#include "search.h"

#include <iostream>

search::search() { }

std::vector<File> search::doSearch(fs::path p) {
    view.printHeader("Enter your search query (case sensitive):");
    std::getline(std::cin, query);

#ifdef _WIN32
    int const enterChar = 13;
#else
    int const enterChar = 10;
#endif

    do {
        input.clearScreen();

#ifdef _WIN32
        view.emptyScreen();
        input.clearScreen();
#endif

        view.printHeader("Search options for: '" + query + "'");
        view.printOptions(minSize, maxSize, validExtensions, validTypes, recursive);

        int charInput = input.getch();

        switch (charInput) { // Get inputs
            case 49: minSize = view.getIntFromInput("Enter New Minimum Size (in bytes): ", 0, maxSize); break;
            case 50: maxSize = view.getIntFromInput("Enter New Maximum Size (in bytes): ", minSize, 0); break;
            case 51: addExtension(); break;
            case 52: addType(); break;
            case 53: recursive = !recursive; break;
            case enterChar: // [Enter] Confirm
                return ctr.executeSearch(p, query, minSize, maxSize, validExtensions, validTypes, recursive);
            default: break;
        }
    } while (true);
}

void search::addExtension() {
    view.printHeader("Enter an extension you want to search for (formatted '.txt'):");

    do {
        std::string inp = view.getInput();
        bool push = true;

        for (std::string t : validTypes) {
            if (t == inp) {
                view.showError("Input already in list!");
                push = false;
            }
        }

        if (inp[0] != '.') {
            view.showError("Input must have a '.' at the start.");
            push = false;
        }

        if (push) {
            validExtensions.push_back(inp);
            return;
        }
    } while (true);
}

void search::addType() {
    view.printHeader("Enter a file type you want to search for (Text, Audio etc.):");

    do {
        std::string inp = view.getInput();
        bool push = true;

        for (std::string t : validTypes) {
            if (t == inp) {
                view.showError("Input already in list!");
                push = false;
            }
        }

        if (!ctr.isValidType(inp)) {
            view.showError("Invalid Input");
            push = false;
        }

        if (push) {
            validTypes.push_back(inp);
            return;
        }
    } while (true);
}