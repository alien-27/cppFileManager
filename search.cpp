#include "search.h"

#include <iostream>

search::search() {
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
            case 49: // [1] Set Minimum Size

                break;
            case 50: // [2] Set Maximum Size

                break;
            case 51: // [3] Search for specific file extensions

                break;
            case 52: // [4] Search for specific file types

                break;
            case 53: // [5] Toggle Recursive Search
                recursive = !recursive;
                break;
            case enterChar: // [Enter] Confirm
                input.clearScreen();
                return;
                break;
            default:
                break;
        }
    } while (true);
}

std::vector<File> search::doSearch(fs::path p) {
    std::vector<File> newList;

    for (const auto& p : fs::directory_iterator(p)) {
        if (p.is_directory()) {
            if (recursive) {
                std::vector<File> newList2 = doSearch(p.path());

                for (File f : newList2) {
                    newList.push_back(f);
                }
            }
        }

        if (p.path().filename().string().find(query) != std::string::npos) {
            bool push = true;

            File temp = File(p);

            if (!temp.getIsFolder()) {
                if (temp.getSize() < minSize) {
                    push = false;
                }
                if (temp.getSize() > maxSize && maxSize > minSize) {
                    push = false;
                }

                // Check if filetype is valid
                if (!validExtensions.empty()) {
                    auto ft = find(validExtensions.begin(), validExtensions.end(), temp.getExtension());

                    if (ft == validExtensions.end()) {
                        push = false;
                    }
                }
            }
                
            if (push) newList.push_back(temp);
        }
    }

    return newList;
}