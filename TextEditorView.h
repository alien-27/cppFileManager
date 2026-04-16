#pragma once

#include "Input.h"

#include <iostream>
#include <string>
#include <vector>

class TextEditorView {
    private:
	    Input input;
        void printHeader(std::string title);
    public:
        void displayTextEditor(std::string filePath, std::vector<std::string> contents, int column, int row);
        void displaySaveScreen(std::string filePath);
        void clearScreen();
};