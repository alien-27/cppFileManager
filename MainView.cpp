#include "MainView.h"

#include "AudioFile.h"
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
    int rowsToPrint = input.consoleHeight() - 3; // How many rows will be displayed

    // Get start row.
    if (f.size() > rowsToPrint) { // If there are more rows in total than there are rows being displayed...
        if (selected >= rowsToPrint / 2) {
            startRow = selected - (rowsToPrint / 2) + 1;
        }

        if (startRow > f.size() - rowsToPrint) {
            startRow = f.size() - rowsToPrint;
        }
    }

    for (int i = startRow; i < startRow + rowsToPrint; i++) { // Display each row.
        // SCROLL BAR
        if (f.size() > rowsToPrint) {
            float trueI = (float)(i - startRow) / (rowsToPrint); // What row we are currntly printing.
            float barTop = (float)((float)startRow / (float)f.size()); // The top of the scroll bar
            float barBottom = (float)((float)(startRow + rowsToPrint + 1) / (float)f.size()); // The bottom of the scroll bar

            if (trueI >= barTop && trueI <= barBottom) { // If the current row intersects the scrollbar
                std::cout << "\033[44m"; // Set colour to blue
            } else {
                std::cout << "\033[0m"; // Else, set colour to black (invisible).
            }

            std::cout << " \033[0m "; // Prints the bar, and an empty space after it.
        }

        // FILE INFO
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
        TextFile& tf = static_cast<TextFile&>(f); // Turn f into a TextFile
        std::cout << "Lines: " << tf.getLines() << std::endl; // Display no of lines.
        filledRows += 1;
    } else if (f.getType() == "Audio") {
        AudioFile& af = static_cast<AudioFile&>(f);
        std::cout << "   Duration: " << af.getLength() << " seconds" << std::endl
                  << "Sample Rate: 0 kHz" << std::endl
                  << "   Channels: Mono" << std::endl;
        filledRows += 3;
    }

    for (int i = 0; i < input.consoleHeight() - filledRows; i++) {
        std::cout << std::endl;
    }
    
    printFooter(fileCtrls);
}

void MainView::printHeader(std::string title) { // Displays a header.
    std::string printStr = title;

    int width = input.consoleWidth();

    if (printStr.length() > width - 1) { // If ths title is wider than the window...
        printStr = title.substr(title.length() - (width - 1)); // Cut the beginning of it off.
    }

    // Display the header.
    if (errMsg != "") { // If there is an error...
        printStr = "ERROR: " + errMsg;
        std::cout << "\033[41m\033[30m" << printStr; // DIsplay that instead of the title.
        errMsg = ""; // Reset the error variable.
    }
    else {
        std::cout << "\033[44m\033[37m" << printStr;
    }

    if (width > printStr.length()) { // If the title is shorter than the window width...
        std::cout << std::string(width - printStr.length(), ' '); // Fill the rest of the row with spaces so the background colour isn't cut off
    }

    std::cout << std::endl << "\033[0m"; // Reset concolours.
}

void MainView::printFooter(std::map<std::string, std::string> ctrls) {
    int curWidth = 0; // How many characters are in the footer text.

    std::map<std::string, std::string>::iterator it;
    for (auto it = ctrls.begin(); it != ctrls.end(); it++) { // For each entry...
        std::cout << "\033[44m\033[37m " << it->first << " \033[47m\033[30m " << it->second << " "; // ...Display its data

        curWidth += it->first.length() + it->second.length() + 4; // Update the width.
    }

    int width = input.consoleWidth();

    if (width > curWidth) { // If the width is shorter than the window width...
        std::cout << std::string(width - curWidth, ' '); // Fill the rest of the row with spaces so the background colour isn't cut off
    }

    std::cout << "\033[0m"; // Reset console colours.
}

void MainView::exitMessage() {
    std::cout << "\033[44m\033[37mExiting Program.\033[0m";
}

void MainView::showError(std::string msg) {
    errMsg = msg;
}
