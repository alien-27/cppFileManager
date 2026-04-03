#include "SearchController.h"

#include <algorithm>
#include <unordered_set>

SearchController::SearchController() { }

bool SearchController::isValidType(std::string t) {
    std::unordered_set<std::string> validTypes = { "Text", "Document", "Code", "Graphic", "Model", "Video", "Audio", "Archive", "Application", "File", "Folder"};
    return validTypes.count(t);
}

std::vector<File> SearchController::executeSearch(fs::path p, std::string query, int minSize, int maxSize, std::vector<std::string> validExtensions, std::vector<std::string> validTypes, bool recursive) {
    std::vector<File> newList;

    for (const auto& p : fs::directory_iterator(p)) {
        if (p.is_directory() && recursive) {
            std::vector<File> newList2 = executeSearch(p.path(), query, minSize, maxSize, validExtensions, validTypes, true);

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

                // Check if file extension is valid
                if (!validExtensions.empty()) {
                    auto ft = std::find(validExtensions.begin(), validExtensions.end(), temp.getExtension());

                    if (ft == validExtensions.end()) {
                        push = false;
                    }
                }
            } else {
                if (!validExtensions.empty()) {
                    push = false;
                }
            }

            // Check if file type is valid
            if (!validTypes.empty()) {
                auto ft = std::find(validTypes.begin(), validTypes.end(), temp.getType());

                if (ft == validTypes.end()) {
                    push = false;
                }
            }

            if (push) newList.push_back(temp);
        }
    }

    return newList;
}