#pragma once

#include <string>
#include <vector>

class TextEditorController {
    public:
        std::vector<std::string> readFromFile(std::string filePath);
        bool saveToFile(std::string filePath, std::vector<std::string> contents);
};