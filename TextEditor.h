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
        bool exit = false;

        Input input;
        TextEditorView view;

        void getInput();
        void changeRow(int amt);
        void changeColumn(int amt);
        void enterPress();
        void bkspPress();
        std::string addChar(char ch);
    public:
        TextEditor(std::string filePath);
};