#pragma once

#include "Input.h"
#include "TextEditorView.h"

#include <string>
#include <vector>

class TextEditor {
    private:
        std::string filePath;
        std::vector<std::string> contents;
        int column;
        int row;

        Input input;
        TextEditorView view;

        void clearScreen();
    public:
        TextEditor(std::string filePath);
};