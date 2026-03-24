#include "search.h"

#include <iostream>

search::search() {
    view.printHeader("Enter your search query:");
    std::getline(std::cin, query);

    do {
        int charInput = input.getch();

        switch (charInput) { // Get inputs
            case 49:
                return;
                break;
            case 50:
                return;
                break;
            case 51:
                return;
                break;
            case 52:
                return;
                break;
            case 53:
                return;
                break;
            case 54: // Confirm
                return;
                break;
            default:
                break;
        }
    } while (true);
}

std::vector<File> search::doSearch(fs::path p) {
    std::vector<File> newList;

    for (const auto& p : fs::recursive_directory_iterator(p)) {
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