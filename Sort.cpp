#include "Sort.h"

Sort::Sort(std::vector<File> fv) {
	fileList = fv;
}

/// <summary>
/// Takes a list of files and returns a sorted list.
/// </summary>
/// <param name="value">Which value to sort by</param>
/// <param name="ord">What order to sort it by</param>
/// <returns>The sorted list of files</returns>
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

/// <summary>
/// Sort the list of files by name
/// </summary>
/// <param name="order">What order to sort it by</param>
void Sort::sortByName(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getName() > fileList[j + 1].getName() && order == "ASC") || (fileList[j].getName() < fileList[j + 1].getName() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

/// <summary>
/// Sort the list of files by date
/// </summary>
/// <param name="order">What order to sort it by</param>
void Sort::sortByDate(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getDateMod() > fileList[j + 1].getDateMod() && order == "ASC") || (fileList[j].getDateMod() < fileList[j + 1].getDateMod() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

/// <summary>
/// Sort the list of files by size
/// </summary>
/// <param name="order">What order to sort it by</param>
void Sort::sortBySize(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getSize() > fileList[j + 1].getSize() && order == "ASC") || (fileList[j].getSize() < fileList[j + 1].getSize() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}

/// <summary>
/// Sort the list of files by extension
/// </summary>
/// <param name="order">What order to sort it by</param>
void Sort::sortByExtension(std::string order) {
    for (int i = 0; i < fileList.size() - 1; i++) {
        for (int j = 0; j < fileList.size() - 1 - i; j++) {
            if ((fileList[j].getExtension() > fileList[j + 1].getExtension() && order == "ASC") || (fileList[j].getExtension() < fileList[j + 1].getExtension() && order == "DESC")) {
                std::swap(fileList[j], fileList[j + 1]);
            }
        }
    }
}
