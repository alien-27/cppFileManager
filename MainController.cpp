#include "MainController.h"

#include "search.h"
#include "Sort.h"

namespace fs = std::filesystem;

/// <summary>
/// Gets a list of all files and folders in a chosen directory.
/// </summary>
/// <param name="path"The chosen directory></param>
/// <returns>A vector of Files</returns>
std::vector<File> MainController::getFiles(std::string path) {
    std::vector<File> newList;

    for (const auto& p : fs::directory_iterator(path)) {
        File temp = File(p);
        newList.push_back(temp);
    }

    return newList;
}

/// <summary>
/// Sets the selection
/// </summary>
/// <param name="s">The new value</param>
/// <param name="min">The minimum value</param>
/// <param name="max">The maximum value</param>
/// <returns>The new select value</returns>
int MainController::setSelect(int s, int min, int max) {
    int newS = s;

    if (newS < min) newS += max + 1;
    if (newS >= max) newS = min;

    return newS;
}
