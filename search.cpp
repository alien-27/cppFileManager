#include "search.h"

#include <algorithm>
#include <iostream>
#include <vector>

search::search() {
	std::cout << "enter query: ";
	std::cin >> query;
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
            File temp = File(p);

            bool push = true;

            if (!temp.getIsFolder()) {
                if (temp.getSize() < minSize) {
                    push = false;
                }
                if (temp.getSize() > maxSize && maxSize > minSize) {
                    push = false;
                }

                // Check if filetype is valid
                if (!validExtensions.empty()) {
                    auto ft = std::find(validExtensions.begin(), validExtensions.end(), temp.getExtension());

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