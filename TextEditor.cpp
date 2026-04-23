#include "TextEditor.h"

#include <string>

TextEditor::TextEditor(std::string filePath) {
    // Get the data from the file
    contents = ctrl.readFromFile(filePath);

    do { // Repeat until the file has been exited
        // TEXT EDITOR
        do { // Repeat until exit key pressed
            view.clearScreen();
            view.displayTextEditor(filePath, contents, column, row);
            getInput();
        } while (!exit);

        // Reset exit stuff
        bool exiting = true;
        exit = false;

        // EXIT SCREEN
        do {
            view.clearScreen();
            view.displaySaveScreen(filePath);

            int charInput = input.getch();

            switch (charInput) {
                case 49: // 1 (Exit and save)
                    if (ctrl.saveToFile(filePath, contents)) {
                        return;
                    } else {
                        view.showError("Could not save file.");
                    }
                    
                    return;
                case 50: return; // 2 (Exit without saving)
                case 51: exiting = false; break; // 3 (Return)
                default: break;
            }
        } while (exiting);
    } while (true);
}

void TextEditor::getInput() {
#ifdef _WIN32
    int const upChar = 72;
    int const downChar = 80;
    int const leftChar = 75;
    int const rightChar = 77;

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

    int charInput = input.getch(); // Get character input

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
            case endChar: row = (int)contents.size(); changeRow(0); view.showError("error test."); break;
            default: break;
        }
        skipNextInput = false;
        return;
    } else {
        switch (charInput) {
            case 27:
                if (skipNextInput) {
                    skipNextInput = false;
                    exit = true;
                } else {
                    skipNextInput = true;
                    return;
                }
            return; // Esc (Exit)
            case bkspChar: bkspPress(); break; // Backspace
            case enterChar: enterPress(); break; // Enter
            default: // Other keyboard inputs (insert inputted letter into file)
                if (charInput >= 32 && charInput <= 126) {
                    contents[row - 1] = addChar(char(charInput));
                    changeColumn(1);
                }
                return;
        }
    }
}

/// <summary>
/// Change the selected row.
/// </summary>
/// <param name="amt"></param>
void TextEditor::changeRow(int amt) {
    row += amt;

    // Make sure row doesn't go beyond the top
    if (row < 1) {
        row = 1;
    }

    // Make sure row doesn't go beyond the bottom
    if (row > (int)contents.size()) {
        row = (int)contents.size();
    }

    if (column > contents[row - 1].length()) { // If the newly selected row is shorter than the previous one...
        column = contents[row - 1].length(); // ...make sure the column is not to the right of the text
    }
}

/// <summary>
/// Change the selected column.
/// </summary>
/// <param name="amt">The amount to change</param>
void TextEditor::changeColumn(int amt) {
    column += amt;

    if (column < 0) { // If the leftmost column is selected...
        // ...Go to end of previous row.
        column = contents[row - 2].length();
        changeRow(-1);
    }
    if (column > contents[row - 1].length()) { // If the rightmost column is selected...
        // ...Go to start of next row
        changeRow(1);
        column = 0;
    }
}

/// <summary>
/// Adds a character at position 'column' of the current row
/// </summary>
/// <param name="ch">The character that is being added</param>
/// <returns>The newly modified string</returns>
std::string TextEditor::addChar(char ch) {
    std::string oldStr = contents[row - 1];
    std::string newStr = "";

    for (int i = 0; i < oldStr.length() + 1; i++) { // For every character...
        if (i == column) { // If this is the selected letter...
            newStr += ch; //... add the character to the new string.
        }
        if (i < oldStr.length()) newStr += oldStr[i]; // add the character to the new string
    }
    
    return newStr;
}

/// <summary>
/// Logic for when enter is pressed
/// </summary>
void TextEditor::enterPress() {
    std::string newStr = "";
    std::string oldStr = contents[row - 1];

    if (column < oldStr.length()) { // If the selected character is in the middle of the line...
        for (int i = 0; i < oldStr.length(); i++) {
            if (i == column) {
                contents[row - 1] = newStr;
                newStr = "";
            }
            newStr += oldStr[i];
        }
    }

    contents.insert(contents.begin() + row, newStr); // Add new string to textfile

    // Go to the start of the new row.
    column = 0;
    changeRow(1);
}

/// <summary>
/// Logic for when backspace is pressed
/// </summary>
void TextEditor::bkspPress() {
    if (column > 0) { // If the selected is after the start of the row...
        // Get rid of character before
        std::string newStr = "";
        std::string oldStr = contents[row - 1];

        for (int i = 0; i < oldStr.length(); i++) {
            if (i != column - 1) newStr += oldStr[i];
        }

        contents[row - 1] = newStr;

        changeColumn(-1);
    } else {
        // Move contents of this row to previous row
        int newCol = contents[row - 2].length();

        contents[row - 2] += contents[row - 1];
        contents.erase(contents.begin() + row - 1);

        column = newCol;
        changeRow(-1);
    }
}