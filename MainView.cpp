#include "MainView.h"

using namespace std::chrono_literals;

void MainView::displayFiles(std::vector<File> f, int selected) {
    // Display exit at the top.
    std::cout << setColour(-1 == selected) << "<< Exit" << std::endl;

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
        if (f.size() > rowsToPrint) { // SCROLL BAR
            float trueI = (float)(i - startRow) / (rowsToPrint); // What row we are currntly printing.
            float barTop = (float)((float)startRow / (float)f.size()); // The top of the scroll bar
            float barBottom = (float)((float)(startRow + rowsToPrint + 1) / (float)f.size()); // The bottom of the scroll bar

            if (trueI >= barTop && trueI <= barBottom) { // If the current row intersecs the scrollbar
                std::cout << "\033[44m"; // Set colour to blue
            } else {
                std::cout << "\033[0m"; // Else, set colour to black.
            }

            std::cout << " \033[0m "; // Prints the bar, and a space after it.
        }

        if (i < f.size()) { // If this row shoudn't be empty.
            std::string sizeUnit = "bytes";

            if (f[i].getIsFolder()) {
                sizeUnit = "files";
            }

            // Display the file details
            std::cout << setColour(i == selected) << "\033[34m" << f[i].getIsFolderStr() << setColour(i == selected)
                      << f[i].getNameWithExtension() << std::string((longestStr - f[i].getNameWithExtension().length()) + 1, ' ')
                      << "\033[34m: " << setColour(i == selected) << f[i].getSize() << " " << sizeUnit << std::string((11 - std::to_string(f[i].getSize()).length()), ' ')
                      << "\033[34m: Modified " << setColour(i == selected) << f[i].getDateModStr();
        } else {
            std::cout << std::endl; // If it is empty, move on to the next row.
        }
    }
    
    printFooter(folderCtrls);
}

std::string MainView::setColour(bool selected) {
    if (selected) { // If this is the selected option...
        return "\033[47m\033[30m"; // ...Foreground black, background white
    }
    else {
        return "\033[0m"; // ... if it's not, reset console colours
    }
}

void MainView::displayDetails(File f) {
    printHeader("Viewing File: " + f.getNameWithExtension());

    std::cout << " :          Name: " << f.getName() << std::endl
              << " :     Extension: " << f.getExtension() << std::endl
              << " :      Location: " << f.getPath() << std::endl
              << " :          Size: " << f.getSize() << " bytes" << std::endl
              << " : Date Modified: " << f.getDateModStr() << std::endl;

    for (int i = 0; i < 21; i++) {
        std::cout << std::endl;
    }

    printFooter(fileCtrls);
}

void MainView::printHeader(std::string title) {
    if (errMsg != "") {
        std::cout << "\033[41m\033[30mERROR: " << errMsg << std::endl << "\033[0m";
        errMsg = "";
    }
    else {
        std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";
    }
}

void MainView::printFooter(std::map<std::string, std::string> ctrls) { // TO-DO: replace this
    // Iterate through map
    std::map<std::string, std::string>::iterator it;
    for (auto it = ctrls.begin(); it != ctrls.end(); it++) {
        std::cout << "\033[44m\033[37m " << it->first << " \033[47m\033[30m " << it->second << " ";
    }

    std::cout << "\033[0m"; // Reset console colours.
}

void MainView::exitMessage() {
    std::cout << "\033[44m\033[37mExiting Program.\033[0m";
}

void MainView::showError(std::string msg) {
    errMsg = msg;
}

void MainView::emptyScreen() {
    for (int i = 0; i < 50; i++) {
        std::cout << std::string(120, ' ');
    }
}