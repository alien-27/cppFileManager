#include "MainApp.h"

#include "search.h"
#include "Sort.h"

//#include <iostream>

MainApp::MainApp() {
    //curPath = "C:\\Users\\2000389\\OneDrive - Dundee and Angus College\\Documents";
    selected = 0;
    fileList = ctrl.getFiles(curPath);

    input.clearScreen();
    view.printHeader(curPath);
    view.displayFiles(fileList, selected);

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
        input.clearScreen();

#ifdef _WIN32
        if (charInput == 0 || charInput == 224) { // Special keys
#else
        if (charInput == 91) {
#endif
            charInput = input.getch();
            switch (charInput) {
                case upChar: // Up Arrow
                    selected = ctrl.setSelect(selected - 1, -1, (int)fileList.size()); break;
                case downChar: // Down Arrow
                    selected = ctrl.setSelect(selected + 1, -1, (int)fileList.size()); break;
                case homeChar: // Home
                    selected = ctrl.setSelect(0, -1, (int)fileList.size()); break;
                case endChar: // End
                    selected = ctrl.setSelect((int)fileList.size() - 1, -1, (int)fileList.size()); break;
                default:
                    break;
            }
        }
        else {
            switch (charInput) {
                case bkspChar: // Backspace
                    back(); break;
                case enterChar: // Enter
                    enter(); break;
                case 49: // 1 (Search)
                    startSearch(); break;
                case 50: // 2 (Sort)
                    startSort(); break;
                case 51: // 3 (Cut)
                    clip.copy(fileList[selected].getPath(), true); break;
                case 52: // 4 (Copy)
                    clip.copy(fileList[selected].getPath(), false); break;
                case 53: // 5 (Paste)
                    clip.paste();
                    fileList = ctrl.getFiles(curPath); // Refresh
                    break;
                case 54: // 6 (Rename)
                    renameFile(fileList[selected].getPath()); break;
                case 55: // 7 (Delete)
                    deleteFile(fileList[selected].getPath()); break;
                case 56: // 8 (Encrypt / Decrypt)
                    break;
                case 57: // 9 (Exit)
                    view.exitMessage();
                    return;
                    break;
                default:
                    break;
            }
        }

        view.printHeader(curPath);
        view.displayFiles(fileList, selected);
    } while (true);
}

void MainApp::back() {
    if (!isSearch) {
        try {
            fs::path current = fs::current_path();
            fs::current_path(current.parent_path());
        } catch (const fs::filesystem_error& e) {
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

void MainApp::startSearch() {
    search Search = search();
    fileList = Search.doSearch(fs::current_path());

    isSearch = true;
}

void MainApp::startSort() {
    Sort sort = Sort(fileList);
    fileList = sort.sortList();
}

void MainApp::renameFile(std::string path) {
    if (path == "") return;
    if (!fs::exists(path)) return;

    fs::path p(path);

    std::string name = p.filename().stem().string();
    std::string extension = p.extension().string();

    input.clearScreen();
    view.printHeader("Rename file: '" + name + "'");

    std::string newName = "";
    std::getline(std::cin, newName);

    if (!fs::exists(newName + extension)) { // If there is no file with this name in the directory...
        try {
            fs::rename(p, newName + extension);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "\033[31mERROR: " << e.what() << std::endl;
        }
    } else {
        std::cout << "\033[31mERROR: File already exists" << std::endl;
    }

    fileList = ctrl.getFiles(curPath); // Refresh
}

void MainApp::deleteFile(std::string path) {
    try {
        fs::path p(path);
        fs::remove_all(p);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "\033[31mERROR: " << e.what() << std::endl;
    }

    fileList = ctrl.getFiles(curPath); // Refresh
}