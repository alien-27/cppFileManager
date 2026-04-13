#include "TextEditorView.h"

void TextEditorView::displayTextEditor(std::string filePath, std::vector<std::string> contents, int column, int row) {
    int width = input.consoleWidth();
    int height = input.consoleHeight();

    std::string title = "Edit File: " + filePath;

    if (title.length() > width) {
        title = "..." + title.substr(title.length() - (width - 3));
    }

    std::cout << "\033[44m\033[37m" << title << std::string(width - title.length(), ' ') << std::endl << "\033[0m";

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
                //curRowText = "\033[47m\033[30m" + contents[i + startOffset] + " \033[0m";

                std::string fullRow = contents[i + startOffset];

                for (int j = 0; j < fullRow.length() + 1; j++) {
                    if (j == column) curRowText += "\033[47m\033[30m";

                    if (j < fullRow.length()) {
                        curRowText += fullRow[j];
                    } else {
                        curRowText += " ";
                    }
                    
                    if (j == column) curRowText += "\033[0m";
                }
            } else {
                curRowText = contents[i + startOffset];
            }
        }

        std::cout << "\033[47m\033[30m" << std::string(rowCountWidth - std::to_string(curRow).length(), ' ') << curRow << "\033[0m "
                  << curRowText << std::endl;
    }

    std::string footer = "press 0 to exit";
    std::cout << "\033[47m\033[30m" << footer << std::string(width - footer.length(), ' ') << "\033[0m";
}