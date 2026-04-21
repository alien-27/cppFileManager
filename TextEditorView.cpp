#include "TextEditorView.h"

/// <summary>
/// Displays a header
/// </summary>
/// <param name="title">The title</param>
void TextEditorView::printHeader(std::string title) {
    std::string printStr = title;

    int width = input.consoleWidth();

    if (printStr.length() > width - 1) { // If ths title is wider than the window...
        printStr = "..." + title.substr(title.length() - (width - 3)); // Cut the beginning of it off.
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

    std::cout << std::endl << "\033[0m"; // Reset console colours.
}

/// <summary>
/// Displays the text editor
/// </summary>
/// <param name="filePath">The filepath for the header to display</param>
/// <param name="contents">The contents of the file</param>
/// <param name="column">The selected column</param>
/// <param name="row">The selected row</param>
void TextEditorView::displayTextEditor(std::string filePath, std::vector<std::string> contents, int column, int row) {
    // Get dimensions
    int width = input.consoleWidth();
    int height = input.consoleHeight();

    printHeader("Edit File: " + filePath); // Display header

    // Get the number of the row to be displayed at the top.
    int startOffset = 0;
    if (row > (height / 2)) {
        startOffset = row - (height / 2);
    }

    int rowsToPrint = height - 2;
    int rowCountWidth = std::to_string(startOffset + rowsToPrint).length(); // The width of the row counter at the left

    for (int i = 0; i < rowsToPrint; i++) { // For every line...
        int curRow = i + startOffset + 1;
        std::string curRowText = ""; // The text to be displayed

        if (i + startOffset < contents.size()) {
            if (curRow == row) { // If this is the selected row...
                std::string fullRow = contents[i + startOffset] + " ";

                for (int j = 0; j < fullRow.length(); j++) { // .. for every character...
                    if (j == column) curRowText += "\033[47m\033[30m"; // if this character is selected, give it different colours
                    curRowText += fullRow[j]; // add the character
                    if (j == column) curRowText += "\033[0m";
                }
            } else { // ...else add the contents of the row to the string
                curRowText = contents[i + startOffset];
            }
        }

        // Print the row
        std::cout << "\033[34m" << std::string(rowCountWidth - std::to_string(curRow).length(), ' ') << curRow << "\033[0m " << curRowText << std::endl;
    }

    // Print footer
    std::string footer = "Ln " + std::to_string(row) + ", Col " + std::to_string(column + 1) + " | Esc to Exit";
    std::cout << "\033[47m\033[30m" << footer << std::string(width - footer.length(), ' ') << "\033[0m";
}

/// <summary>
/// Display the save screen
/// </summary>
/// <param name="filePath">The filepath for the header to display</param>
void TextEditorView::displaySaveScreen(std::string filePath) {
    printHeader("Save File " + filePath + "?");

    std::cout << "[1] Exit and Save" << std::endl
              << "[2] Exit without Saving" << std::endl
              << "[3] Return" << std::endl;
}

/// <summary>
/// Clear the screen
/// </summary>
void TextEditorView::clearScreen() {
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}

/// <summary>
/// Sets an error message to be displayed in the header
/// </summary>
/// <param name="msg"></param>
void TextEditorView::showError(std::string msg) {
    errMsg = msg;
}