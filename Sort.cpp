#include "Sort.h"

Sort::Sort(std::vector<File> fv) {
	fileList = fv;
}

std::vector<File> Sort::sortList(std::string value, std::string ord) {
    if (value == "Name") {
        sortByName(ord);
    } else if (value == "Size") {
        sortBySize(ord);
    } else if (value == "Date") {
        sortByDate(ord);
    } else if (value == "Extension") {
        sortByExtension(ord);
    }

    return fileList;
}

void Sort::sortByName(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getName() > fileList[j + 1].getName() && order == "ASC") || (fileList[j].getName() < fileList[j + 1].getName() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

void Sort::sortByDate(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getDateMod() > fileList[j + 1].getDateMod() && order == "ASC") || (fileList[j].getDateMod() < fileList[j + 1].getDateMod() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

void Sort::sortBySize(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getSize() > fileList[j + 1].getSize() && order == "ASC") || (fileList[j].getSize() < fileList[j + 1].getSize() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

void Sort::sortByExtension(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getExtension() > fileList[j + 1].getExtension() && order == "ASC") || (fileList[j].getExtension() < fileList[j + 1].getExtension() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}
