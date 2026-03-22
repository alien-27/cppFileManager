#include "MainApp.h"

#include "search.h"
#include "Sort.h"

//#include <iostream>

MainApp::MainApp() {
    //curPath = "C:\\Users\\2000389\\OneDrive - Dundee and Angus College\\Documents";
    selected = 0;
    fileList = ctrl.getFiles(curPath);

    input.clear();
    view.displayFiles(curPath, fileList, selected);

#ifdef _WIN32
    int const upChar = 72;
    int const downChar = 80;
    int const homeChar = 71;
    int const endChar = 79;

    int const bkspChar = 8;
    int const enterChar = 13;
#else
    int const upChar = 65;
    int const downChar = 66;
    int const homeChar = 72;
    int const endChar = 70;

    int const bkspChar = 127;
    int const enterChar = 10;
#endif

    do {
        int charInput = input.getch();
        input.clear();

#ifdef _WIN32
        if (charInput == 0 || charInput == 224) { // Special keys
#else
        if (charInput == 91) {
#endif
            charInput = input.getch();
            switch (charInput) {
                case upChar: // Up Arrow
                    selected = ctrl.setSelect(selected - 1, -1, (int)fileList.size());
                    break;
                case downChar: // Down Arrow
                    selected = ctrl.setSelect(selected + 1, -1, (int)fileList.size());
                    break;
                case homeChar: // Home
                    selected = ctrl.setSelect(0, -1, (int)fileList.size());
                    break;
                case endChar: // End
                    selected = ctrl.setSelect((int)fileList.size() - 1, -1, (int)fileList.size());
                    break;
                default:
                    break;
            }
        } else {
            switch (charInput) {
                case bkspChar: // Backspace
                    back();
                    break;
                case enterChar: // Enter
                    enter();
                    break;
                case 49: { // 1
                    search Search = search();
                    fileList = Search.doSearch(fs::current_path());

                    isSearch = true;
                    break;
                }
                case 50: { // 2
                    Sort sort = Sort(fileList);
                    fileList = sort.sortList();
                    break;
                }
                default:
                    break;
            }
        }

        view.displayFiles(curPath, fileList, selected);

        //std::cout << charInput;
    } while (true);
}

void MainApp::back() {
    if (!isSearch) {
        try {
            fs::path current = fs::current_path();
            fs::current_path(current.parent_path());
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "\033[31mERROR: " << e.what() << std::endl;
        }

        curPath = fs::current_path().string();
    }

    isSearch = false;

    selected = 0;
    fileList = ctrl.getFiles(curPath);
}

void MainApp::enter() {
    if (selected == -1) {
        back();
        return;
    }

    if (fileList.empty()) return;

    isSearch = false;

    if (fileList[selected].getIsFolder()) {
        try {
            fs::path current = fileList[selected].getPath();
            fs::current_path(current);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "\033[31mERROR: " << e.what() << std::endl;
        }
        curPath = fs::current_path().string();

        selected = 0;
        fileList = ctrl.getFiles(curPath);
    } else {

    }
}