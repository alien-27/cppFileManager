#include "TextEditor.h"

#include <fstream>
#include <string>

// temporary
#include <iostream>

TextEditor::TextEditor(std::string filePath) {
    this->filePath = filePath;

	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
        while (std::getline(file, line)) { // For every line...
            contents.push_back(line);
        }
	}

    int p = 0;

    do {
        p++;
        clearScreen();
        view.displayTextEditor(filePath, contents, column, row);
        getInput();
    } while (!exit);
}

void TextEditor::getInput() {
#ifdef _WIN32
    int const upChar = 72;
    int const downChar = 80;
    int const leftChar = 65; // TO-DO: get correct values for left and right on windows
    int const rightChar = 66;

    int const homeChar = 71;
    int const endChar = 79;
    int const bkspChar = 8;
    int const enterChar = 13;
#else
    int const upChar = 65;
    int const downChar = 66;
    int const leftChar = 68;
    int const rightChar = 67; // lol

    int const homeChar = 72;
    int const endChar = 70;
    int const bkspChar = 127;
    int const enterChar = 10;
#endif

    int charInput = input.getch();

    //std::cout << (charInput);

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
            case homeChar: row = 1; changeRow(0); break;
            case endChar: row = contents.size(); changeRow(0); break;
            default: break;
        }
        //charInput = input.getch();
        return;
    } else {
        switch (charInput) {
            case 48: exit = true; return; // 0 (Exit)
            case bkspChar: bkspPress(); break;
            case enterChar: enterPress(); break;
            default:
                if (charInput >= 32 && charInput <= 126) {
                    contents[row - 1] = addChar(char(charInput));
                    changeColumn(1);
                }
                return;
        }
    }
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
    if (column > contents[row - 1].length()) { // Go to start of next row
        changeRow(1);
        column = 0;
    }
}

std::string TextEditor::addChar(char ch) {
    std::string oldStr = contents[row - 1];
    std::string newStr = "";

    for (int i = 0; i < oldStr.length() + 1; i++) {
        if (i == column) {
            newStr += ch;
        }
        if (i < oldStr.length()) newStr += oldStr[i];
    }
    
    return newStr;
}

void TextEditor::enterPress() {
    std::string newStr = "";
    std::string oldStr = contents[row - 1];

    for (int i = 0; i < oldStr.length(); i++) {
        if (i == column) {
            contents[row - 1] = newStr;
            newStr = "";
        }
        newStr += oldStr[i];
    }

    contents.insert(contents.begin() + row, newStr);

    column = 0;
    changeRow(1);
}

void TextEditor::bkspPress() {
    if (column > 0) { // Get rid of character before
        std::string newStr = "";
        std::string oldStr = contents[row - 1];

        for (int i = 0; i < oldStr.length(); i++) {
            if (i != column - 1) newStr += oldStr[i];
        }

        contents[row - 1] = newStr;

        changeColumn(-1);
    } else { // Move contents of this row to previous row
        int newCol = contents[row - 2].length();

        contents[row - 2] += contents[row - 1];
        contents.erase(contents.begin() + row - 1);

        column = newCol;
        changeRow(-1);
    }
}

void TextEditor::clearScreen()
{
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}