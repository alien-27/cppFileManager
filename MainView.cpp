#include "MainView.h"

using namespace std::chrono_literals;

void MainView::displayFiles(std::string title, std::vector<File> f, int selected) {
    // Title bar
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";

    // Display exit at the top.
    setColour(-1 == selected);
    std::cout << "<< Exit" << std::endl;

    if (f.empty()) {
        std::cout << "\033[0mThis folder is empty." << std::endl;
        return;
    }

    int longestStr = 0;

    for (const auto& file : f) {
        if (file.getNameWithExtension().length() > longestStr) {
            longestStr = (int)file.getNameWithExtension().length();
        }
    }

    int startRow = 0;
    int rowsToPrint = 27;

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
            }
            else {
                sizeUnit = "bytes";
            }

            setColour(i == selected);
            std::cout << "\033[34m" << f[i].getIsFolderStr();
            setColour(i == selected);
            std::cout << f[i].getNameWithExtension() << std::string((longestStr - f[i].getNameWithExtension().length()) + 1, ' ') << "\033[34m: "; // Display file details
            setColour(i == selected);
            std::cout << f[i].getSize() << " " << sizeUnit << std::string((10 - std::to_string(f[i].getSize()).length()), ' ') << "\033[34m: Modified ";
            setColour(i == selected);
            std::cout << /*"Modified " << */f[i].getDateModStr()/* << std::endl*/;
        } else {
            std::cout << std::endl;
        }
    }

    // TO-DO: replace this
    printFooter();

    std::cout << "\033[0m";
}

void MainView::setColour(bool selected) {
    if (selected) { // If this is the selected option...
        std::cout << "\033[47m\033[30m"; // ...Foreground black, background white
    }
    else {
        std::cout << "\033[0m"; // ... if it's not, reset colours
    }
}

void MainView::printFooter() {
    std::cout << "\033[44m\033[37m Enter \033[47m\033[30m View ";
    std::cout << "\033[44m\033[37m 1 \033[47m\033[30m Search ";
    std::cout << "\033[44m\033[37m 2 \033[47m\033[30m Sort ";
    std::cout << "\033[44m\033[37m 3 \033[47m\033[30m Cut ";
    std::cout << "\033[44m\033[37m 4 \033[47m\033[30m Copy ";
    std::cout << "\033[44m\033[37m 5 \033[47m\033[30m Paste ";
}