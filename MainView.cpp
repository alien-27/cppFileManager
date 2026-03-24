#include "MainView.h"

using namespace std::chrono_literals;

void MainView::displayFiles(std::vector<File> f, int selected) {
    // Display exit at the top.
    setColour(-1 == selected);
    std::cout << "<< Exit" << std::endl;

    if (f.empty()) { // If this folder is empty...
        std::cout << "\033[0mThis folder is empty." << std::endl; // Say it is and don't do the rest of this script
        return;
    }

    // Get the width of the lingest filename.
    int longestStr = 0; 

    for (const auto& file : f) {
        if (file.getNameWithExtension().length() > longestStr) {
            longestStr = (int)file.getNameWithExtension().length();
        }
    }

    int startRow = 0; // The top row that is being displayed
    int rowsToPrint = 27; // How many rows are displayed

    if (f.size() > rowsToPrint) {
        if (selected >= rowsToPrint / 2) {
            startRow = selected - (rowsToPrint / 2) + 1;
        }

        if (startRow > f.size() - rowsToPrint) {
            startRow = f.size() - rowsToPrint;
        }
    }

    for (int i = startRow; i < startRow + rowsToPrint; i++) {
        if (i < f.size()) {
            std::string sizeUnit;

            if (f[i].getIsFolder()) {
                sizeUnit = "files";
            } else {
                sizeUnit = "bytes";
            }

            // Display file details
            std::cout << setColour(i == selected) << "\033[34m" << f[i].getIsFolderStr() << setColour(i == selected)
                      << f[i].getNameWithExtension() << std::string((longestStr - f[i].getNameWithExtension().length()) + 1, ' ')
                      << "\033[34m: " << setColour(i == selected) << f[i].getSize() << " " << sizeUnit << std::string((10 - std::to_string(f[i].getSize()).length()), ' ')
                      << "\033[34m: Modified " << setColour(i == selected) << f[i].getDateModStr();
        } else {
            std::cout << std::endl;
        }
    }
    
    printFooter();

    std::cout << "\033[0m"; // Reset console colours.
}

std::string MainView::setColour(bool selected) {
    if (selected) { // If this is the selected option...
        return "\033[47m\033[30m"; // ...Foreground black, background white
    }
    else {
        return "\033[0m"; // ... if it's not, reset console colours
    }
}

void MainView::printHeader(std::string title) {
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";
}

void MainView::printFooter() { // TO-DO: replace this
    std::cout << "\033[44m\033[37m Enter \033[47m\033[30m View "
              << "\033[44m\033[37m 1 \033[47m\033[30m Search "
              << "\033[44m\033[37m 2 \033[47m\033[30m Sort "
              << "\033[44m\033[37m 3 \033[47m\033[30m Cut "
              << "\033[44m\033[37m 4 \033[47m\033[30m Copy "
              << "\033[44m\033[37m 5 \033[47m\033[30m Paste "
              << "\033[44m\033[37m 6 \033[47m\033[30m Rename "
              << "\033[44m\033[37m 7 \033[47m\033[30m Delete "
              << "\033[44m\033[37m 8 \033[47m\033[30m Encrypt "
              << "\033[44m\033[37m 9 \033[47m\033[30m Exit ";
}

void MainView::exitMessage() {
    std::cout << "\033[44m\033[37mExiting Program.\033[0m";
}