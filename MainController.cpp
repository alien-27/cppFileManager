#include "MainController.h"

#include "search.h"
#include "Sort.h"

namespace fs = std::filesystem;

std::vector<File> MainController::getFiles(std::string path) {
    std::vector<File> newList;

    for (const auto& p : fs::directory_iterator(path)) {
        File temp = File(p);
        newList.push_back(temp);
    }

    return newList;
}

int MainController::setSelect(int s, int min, int max) {
    int newS = s;

    if (newS < min) newS += max + 1;
    if (newS >= max) newS = min;

    return newS;
}