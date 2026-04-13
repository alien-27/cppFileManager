#pragma once

#include "Input.h"
#include "TextEditorView.h"

#include <string>
#include <vector>

class TextEditor {
    private:
        std::string filePath;
        std::vector<std::string> contents;
        int column = 0;
        int row = 1;

        Input input;
        TextEditorView view;

        void clearScreen();
        void changeRow(int amt);
        void changeColumn(int amt);
    public:
        TextEditor(std::string filePath);
};