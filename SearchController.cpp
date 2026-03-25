#include "SearchController.h"

SearchController::SearchController() {

}

std::vector<File> SearchController::executeSearch(fs::path p, std::string query, int minSize, int maxSize, std::vector<std::string> validExtensions, bool recursive) {
    std::vector<File> newList;

    for (const auto& p : fs::directory_iterator(p)) {
        if (p.is_directory() && recursive) {
            std::vector<File> newList2 = executeSearch(p.path(), query, minSize, maxSize, validExtensions, true);

            for (File f : newList2) {
                newList.push_back(f);
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
            else {
                if (!validExtensions.empty()) {
                    push = false;
                }
            }

            if (push) newList.push_back(temp);
        }
    }

    return newList;
}