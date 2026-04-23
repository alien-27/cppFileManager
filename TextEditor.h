#pragma once

#include "Input.h"
#include "TextEditorView.h"
#include "TextEditorController.h"

#include <string>
#include <vector>

class TextEditor {
    private:
        std::vector<std::string> contents;
        int column = 0;
        int row = 1;
        bool exit = false;

        bool skipNextInput = false;

        Input input;
        TextEditorView view;
        TextEditorController ctrl;

        void getInput();
        void changeRow(int amt);
        void changeColumn(int amt);
        void enterPress();
        void bkspPress();
        std::string addChar(char ch);
    public:
        TextEditor(std::string filePath);
};