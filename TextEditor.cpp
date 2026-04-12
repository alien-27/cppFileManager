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

    do {
        clearScreen();
        view.displayTextEditor(filePath, contents);

        int charInput = input.getch();
        switch (charInput) {
            case 48: return; // 0 (Exit)
            default: break;
        }
    } while (true);
}

void TextEditor::clearScreen() {
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}