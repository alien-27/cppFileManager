#include "Sort.h"

Sort::Sort(std::vector<File> fv) {
	fileList = fv;
}

std::vector<File> Sort::sortList() {
	std::string ord = "ASC";
    sortBySize(ord);

    return fileList;
}

void Sort::sortByName(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if (order == "ASC") {
                if (fileList[j].getName() > fileList[j + 1].getName()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            } else {
                if (fileList[j].getName() < fileList[j + 1].getName()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
        }
    }
}

void Sort::sortByDate(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if (order == "ASC") {
                if (fileList[j].getDateMod() > fileList[j + 1].getDateMod()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
            else {
                if (fileList[j].getDateMod() < fileList[j + 1].getDateMod()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
        }
    }
}

void Sort::sortByType(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if (order == "ASC") {
                if (fileList[j].getExtension() > fileList[j + 1].getExtension()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
            else {
                if (fileList[j].getExtension() < fileList[j + 1].getExtension()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
        }
    }
}

void Sort::sortBySize(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if (order == "ASC") {
                if (fileList[j].getSize() > fileList[j + 1].getSize()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
            else {
                if (fileList[j].getSize() < fileList[j + 1].getSize()) {
                    std::swap(fileList[j], fileList[j + 1]);
                }
            }
        }
    }
}
