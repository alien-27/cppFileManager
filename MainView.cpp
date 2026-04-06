#include "MainView.h"
#include "TextFile.h"

using namespace std::chrono_literals;

void MainView::displayFiles(std::vector<File> f, int selected) {
    int width = input.consoleWidth(); // The width of the window

    // Display exit at the top.
    std::cout << setColour(-1 == selected) << "<< Exit" << std::string(width - 7, ' ') << std::endl;

    if (f.empty()) { // If this folder is empty...
        std::cout << "\033[0mThis folder is empty." << std::endl; // Say it is and don't do the rest of this script
        return;
    }

    // Get the width of the longest filename.
    int longestStr = 0;

    for (const auto& file : f) {
        if (file.getNameWithExtension().length() > longestStr) {
            longestStr = (int)file.getNameWithExtension().length();
        }
    }

    int startRow = 0; // The top row that is being displayed
    int rowsToPrint = input.consoleHeight() - 3; // How many rows are displayed

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

            int gapWidth = width - (longestStr + 59);
            if (f.size() <= rowsToPrint) gapWidth += 2;
            if (gapWidth < 0) gapWidth = 0;

            // Display the file details
            std::cout << setColour(i == selected) << "\033[34m" << f[i].getIsFolderStr() << setColour(i == selected)
                      << f[i].getNameWithExtension() << std::string((longestStr - f[i].getNameWithExtension().length()) + 1, ' ') << std::string(gapWidth, ' ')
                      << "\033[34m: " << setColour(i == selected) << f[i].getSize() << " " << sizeUnit << std::string((10 - std::to_string(f[i].getSize()).length()), ' ')
                      << "\033[34m: Modified " << setColour(i == selected) << f[i].getDateModStr();
        } else {
            std::cout /*<< "\033[0m" << std::string(width, ' ')*/ << std::endl; // If it is empty, move on to the next row.
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

void MainView::printSortOptions() {
    std::cout << "[1] Sort By Name (Ascending)" << std::endl
              << "[2] Sort By Name (Descending)" << std::endl
              << "[3] Sort By Size (Ascending)" << std::endl
              << "[4] Sort By Size (Descending)" << std::endl
              << "[5] Sort By Extension (Ascending)" << std::endl
              << "[6] Sort By Extension (Descending)" << std::endl
              << "[7] Sort By Date (Ascending)" << std::endl
              << "[8] Sort By Date (Descending)" << std::endl;
}

void MainView::displayDetails(File& f) {
    printHeader("Viewing File: " + f.getNameWithExtension());

    std::string pathEnd = f.getPath();
    if (pathEnd.length() > input.consoleWidth() - 30) pathEnd = "..." + pathEnd.substr(pathEnd.length() - (input.consoleWidth() - 30));

    int filledRows = 9;

    std::cout << "  ____   :          Name: " << f.getName() << std::endl
              << " | __|_\\ :          Type: " << f.getType() << std::endl
              << " | ___ | :     Extension: " << f.getExtension() << std::endl
              << " | ___ | :      Location: " << pathEnd << std::endl
              << " |_____| :          Size: " << f.getSize() << " bytes" << std::endl
              << "         : Date Modified: " << f.getDateModStr()
              << "\033[44m\033[37m" << std::string(input.consoleWidth(), ' ') << "\033[0m" << std::endl;

    if (f.getType() == "Text" || f.getType() == "Code") {
        // Cast the generic File reference to a TextFile reference
        TextFile& tf = static_cast<TextFile&>(f);
        std::cout << "Lines: " << tf.getLines() << std::endl;

        //std::cout << "Lines: " << f.getLines() << std::endl;
        filledRows += 1;
    } else if (f.getType() == "Audio") {
        std::cout << "   Duration: 0 seconds" << std::endl
                  << "Sample Rate: 0 kHz" << std::endl
                  << "   Channels: Mono" << std::endl;
        filledRows += 3;
    }

    for (int i = 0; i < input.consoleHeight() - filledRows; i++) {
        std::cout << std::endl;
    }
    
    printFooter(fileCtrls);
}

void MainView::printHeader(std::string title) {
    std::string printStr = title;
    if (printStr.length() > input.consoleWidth() - 1) printStr = title.substr(title.length() - (input.consoleWidth() - 1));

    if (errMsg != "") {
        printStr = "ERROR: " + errMsg;
        std::cout << "\033[41m\033[30m" << printStr;
        errMsg = "";
    }
    else {
        std::cout << "\033[44m\033[37m" << printStr;
    }

    int width = input.consoleWidth();

    if (width > printStr.length()) {
        std::cout << std::string(width - printStr.length(), ' ');
    }

    std::cout << std::endl << "\033[0m";
}

void MainView::printFooter(std::map<std::string, std::string> ctrls) {
    int curWidth = 0;

    // Iterate through map
    std::map<std::string, std::string>::iterator it;
    for (auto it = ctrls.begin(); it != ctrls.end(); it++) {
        std::cout << "\033[44m\033[37m " << it->first << " \033[47m\033[30m " << it->second << " ";

        curWidth += it->first.length() + it->second.length() + 4;
    }

    int width = input.consoleWidth();

    if (width > curWidth) {
        std::cout << std::string(width - curWidth, ' ');
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
    for (int i = 0; i < input.consoleHeight(); i++) {
        std::cout << std::string(120, ' ');
    }
}