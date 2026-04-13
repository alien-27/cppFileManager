#include "TextEditor.h"

#include <fstream>
#include <string>

TextEditor::TextEditor(std::string filePath) {
    this->filePath = filePath;

	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
        while (std::getline(file, line)) { // For every line...
            contents.push_back(line);
        }
	}
    
#ifdef _WIN32
    int const upChar = 72;
    int const downChar = 80;
    int const leftChar = 65; // TO-DO: get correct values for left and right on windows
    int const rightChar = 66;
#else
    int const upChar = 65;
    int const downChar = 66;
    int const leftChar = 68;
    int const rightChar = 67; // lol
#endif

    do {
        clearScreen();
        view.displayTextEditor(filePath, contents, column, row);

        int charInput = input.getch();
        // Some keyboard inputs are made up of two characters. What the if statement below does is check
        // if the first one is a special key, and gets the input from the second one.
#ifdef _WIN32
        if (charInput == 0 || charInput == 224) {
#else
        if (charInput == 91) {
#endif
            charInput = input.getch();
            switch (charInput) {
                case upChar: changeRow(-1); break; // Up Arrow
                case downChar: changeRow(1); break; // Down Arrow
                case leftChar: changeColumn(-1); break; // Left Arrow
                case rightChar: changeColumn(1); break; // Right Arrow
                default: break;
            }
        } else {
            switch (charInput) {
                case 48: return; // 0 (Exit)
                default: break;
            }
        }
    } while (true);
}

void TextEditor::changeRow(int amt) {
    row += amt;

    if (row < 1) row = 1;
    if (column > contents[row - 1].length()) column = contents[row - 1].length();

    if (row > contents.size()) {
        contents.push_back("");
    }
}

void TextEditor::changeColumn(int amt) {
    column += amt;

    if (column < 0) { // Go to end of previous row.
        column = contents[row - 2].length();
        changeRow(-1);
    }
    if (column > contents[row - 1].length()) column = contents[row - 1].length();
}

void TextEditor::clearScreen() {
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}