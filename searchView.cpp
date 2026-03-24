#include "searchView.h"

#include <iostream>

void searchView::printHeader(std::string title) {
    std::cout << "\033[44m\033[37m" << title << std::endl << "\033[0m";
}