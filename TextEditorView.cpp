#include "TextEditorView.h"

void TextEditorView::printHeader(std::string title) {
    int width = input.consoleWidth();

    if (title.length() > width) {
        title = "..." + title.substr(title.length() - (width - 3));
    }

    std::cout << "\033[44m\033[37m" << title << std::string(width - title.length(), ' ') << std::endl << "\033[0m";
}

void TextEditorView::displayTextEditor(std::string filePath, std::vector<std::string> contents, int column, int row) {
    int width = input.consoleWidth();
    int height = input.consoleHeight();

    printHeader("Edit File: " + filePath);

    int startOffset = 0;

    if (row > (height / 2)) {
        startOffset = row - (height / 2);
    }

    int rowsToPrint = height - 2;

    int rowCountWidth = std::to_string(startOffset + rowsToPrint).length();

    for (int i = 0; i < rowsToPrint; i++) {
        int curRow = i + startOffset + 1;
        std::string curRowText = "";

        if (i + startOffset < contents.size()) {
            if (curRow == row) {
                std::string fullRow = contents[i + startOffset] + " ";

                for (int j = 0; j < fullRow.length(); j++) {
                    if (j == column) curRowText += "\033[47m\033[30m";
                    curRowText += fullRow[j];
                    if (j == column) curRowText += "\033[0m";
                }
            } else {
                curRowText = contents[i + startOffset];
            }
        }

        std::cout << "\033[34m" << std::string(rowCountWidth - std::to_string(curRow).length(), ' ') << curRow << "\033[0m "
                  << curRowText << std::endl;
    }

    std::string footer = "Ln " + std::to_string(row) + ", Col " + std::to_string(column + 1) + " | Esc to Exit";
    std::cout << "\033[47m\033[30m" << footer << std::string(width - footer.length(), ' ') << "\033[0m";
}

void TextEditorView::displaySaveScreen(std::string filePath) {
    printHeader("Save File " + filePath + "?");

    std::cout << "[1] Exit and Save" << std::endl
              << "[2] Exit without Saving" << std::endl;
}

void TextEditorView::clearScreen() {
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}