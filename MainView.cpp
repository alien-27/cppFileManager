#include "MainView.h"

using namespace std::chrono_literals;

void MainView::displayFiles(std::string title, std::vector<File> f, int selected) {
    // Title bar
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";

    int longestStr = 0;

    for (const auto& file : f) {
        if (file.getNameWithExtension().length() > longestStr) {
            longestStr = (int)file.getNameWithExtension().length();
        }
    }

    for (int i = 0; i < f.size(); i++) {
        if (i == 0) {
            setColour(-1 == selected);
            std::cout << "<< Exit" << std::endl; // Display exit at the top.
        }

        setColour(i == selected);
        std::cout << "\033[34m" << f[i].getIsFolderStr();
        setColour(i == selected);
        std::cout << f[i].getNameWithExtension() << std::string((longestStr - f[i].getNameWithExtension().length()) + 1, ' ') << "\033[34m: "; // Display file details
        setColour(i == selected);
        std::cout << f[i].getSize() << " bytes" << std::string((10 - std::to_string(f[i].getSize()).length()), ' ') << "\033[34m: Modified ";
        setColour(i == selected);
        std::cout << /*"Modified " << */f[i].getDateModStr()/* << std::endl*/;
    }
    std::cout << "\033[0m";
}

void MainView::setColour(bool selected) {
    if (selected) { // If this is the selected option...
        std::cout << "\033[47m\033[30m"; // ...Foreground black, background white
    }
    else {
        std::cout << "\033[0m"; // ... if it's not, reset colours
    }
}