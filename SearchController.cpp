#include "SearchController.h"

#include <algorithm>
#include <unordered_set>

SearchController::SearchController() { }

/// <summary>
/// Returns if the entered type is valid or not
/// </summary>
/// <param name="t">The type that is being compared</param>
/// <returns>If the entered type is valid or not</returns>
bool SearchController::isValidType(std::string t) {
    std::unordered_set<std::string> validTypes = { "Text", "Document", "Code", "Graphic", "Model", "Video", "Audio", "Archive", "Application", "File", "Folder"};
    return validTypes.count(t);
}

/// <summary>
/// Returns a list of file withn a directoru that matches the inputted criteria
/// </summary>
/// <param name="p">The path we are searching</param>
/// <param name="query">The search query</param>
/// <param name="minSize">The minimum filesize</param>
/// <param name="maxSize">The maximum filesize</param>
/// <param name="validExtensions">A list of valid extensions (can be empty)</param>
/// <param name="validTypes">A list of valid filetypes (can be empty)</param>
/// <param name="recursive">Recursive Search</param>
/// <returns></returns>
std::vector<File> SearchController::executeSearch(fs::path p, std::string query, int minSize, int maxSize, std::vector<std::string> validExtensions, std::vector<std::string> validTypes, bool recursive) {
    std::vector<File> newList; // Initialise the list

    // Do this for every file in this directory
    for (const auto& p : fs::directory_iterator(p)) {
        if (p.is_directory() && recursive) { // If this is a folder and we are searching recursively...
            // Add all the files in this folder to the list.
            std::vector<File> newList2 = executeSearch(p.path(), query, minSize, maxSize, validExtensions, validTypes, true);

            for (File f : newList2) {
                newList.push_back(f);
            }
        }

        if (p.path().filename().string().find(query) != std::string::npos) { // If the filename contains the query...
            bool push = true; // Add it to list

            File temp = File(p);

            // Validate file
            if (!temp.getIsFolder()) { // If this is not a folder
                // Check minimum & maximum size
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
                // Check if file extension is valid
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

            if (push) newList.push_back(temp); // If this file is valid, add it to the list.
        }
    }

    return newList; // Return the list
}