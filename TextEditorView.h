#pragma once

#include "Input.h"

#include <iostream>
#include <string>
#include <vector>

class TextEditorView {
    private:
	    Input input;
    public:
        void displayTextEditor(std::string filePath, std::vector<std::string> contents, int column, int row);
};