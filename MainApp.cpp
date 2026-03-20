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

    do {
        int charInput = input.getch();
        input.clear();

#ifdef _WIN32
// WINDOWS
        if (charInput == 0 || charInput == 224) { // Special keys
            charInput = input.getch();
            switch (charInput) {
                case 72: // Up Arrow
                    selected = ctrl.setSelect(selected - 1, -1, (int)fileList.size());
                    break;
                case 80: // Down Arrow
                    selected = ctrl.setSelect(selected + 1, -1, (int)fileList.size());
                    break;
                case 71: // Home
                    selected = ctrl.setSelect(0, -1, (int)fileList.size());
                    break;
                case 79: // End
                    selected = ctrl.setSelect((int)fileList.size() - 1, -1, (int)fileList.size());
                    break;
                default:
                    break;
            }
        }
        else {
            switch (charInput) {
                case 8: // Backspace
                    back();
                    break;
                case 13: // Enter
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
#else
// LINUX
        if (charInput == 91) {
            charInput = input.getch();
            switch (charInput) {
            case 65: // Up Arrow
                selected = ctrl.setSelect(selected - 1, -1, fileList.size());
                break;
            case 66: // Down Arrow
                selected = ctrl.setSelect(selected + 1, -1, fileList.size());
                break;
            case 72: // Home
                selected = ctrl.setSelect(0, -1, fileList.size());
                break;
            case 70: // End
                selected = ctrl.setSelect(fileList.size() - 1, -1, fileList.size());
                break;
            default:
                break;
            }
        } else {
            switch (charInput) {
            case 127: // Backspace
                back();
                break;
            case 10: // Enter
                enter();
                break;
            default:
                break;
            }
        }

#endif

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