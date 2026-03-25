#include "search.h"

#include <iostream>

search::search() {

}

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
        view.printHeader("Search options for: '" + query + "'");
        view.printOptions(minSize, maxSize, validExtensions, recursive);

        int charInput = input.getch();

        switch (charInput) { // Get inputs
            case 49: minSize = view.getIntFromInput("Enter New Minimum Size (in bytes): ", 0, maxSize); break;
            case 50: maxSize = view.getIntFromInput("Enter New Maximum Size (in bytes): ", minSize, 0); break;
            case 51: validExtensions.push_back(view.getExtensionFromInput()); break;
            case 52: // [4] Search for specific file types

                break;
            case 53: recursive = !recursive; break;
            case enterChar: // [Enter] Confirm
                return ctr.executeSearch(p, query, minSize, maxSize, validExtensions, recursive);
            default: break;
        }
    } while (true);
}