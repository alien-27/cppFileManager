#include "MainApp.h"

#include "search.h"
#include "Sort.h"

#include <fstream>

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

        bool screenEmpty = true;

#ifdef _WIN32
        if (charInput == 0 || charInput == 224) { // Special keys
#else
        if (charInput == 91) {
#endif
            charInput = input.getch();
            screenEmpty = false;
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
                    back();
                    break;
                case enterChar: // Enter
                    enter();
                    break;
                case 49: // 1 (Search)
                    startSearch(); break;
                case 50: // 2 (Sort)
                    startSort(); break;
                case 51: // 3 (New)
                    makeNew();
                    fileList = ctrl.getFiles(curPath); // Refresh
                    break;
                case 52: // 4 (Cut)
                    clip.copy(fileList[selected].getPath(), true); screenEmpty = false; break;
                case 53: // 5 (Copy)
                    clip.copy(fileList[selected].getPath(), false); screenEmpty = false; break;
                case 54: // 6 (Paste)
                    clip.paste();
                    fileList = ctrl.getFiles(curPath); // Refresh
                    break;
                case 55: // 7 (Rename)
                    renameFile(fileList[selected].getPath()); break;
                case 56: // 8 (Delete)
                    deleteFile(fileList[selected].getPath()); break;
                case 57: // 9 (Encrypt / Decrypt)
                    break;
                case 48: // 0 (Exit)
#ifdef _WIN32
                    view.emptyScreen();
                    input.clearScreen();
#endif
                    view.exitMessage();
                    return;
                    break;
                default:
                    break;
            }
        }

#ifdef _WIN32
        if (screenEmpty) {
            view.emptyScreen();
            input.clearScreen();
        }
#endif

        view.printHeader(curPath);
        view.displayFiles(fileList, selected);
    } while (true);
}

void MainApp::back() {
    std::string prevPath = curPath;

    if (!isSearch) {
        try {
            fs::path current = fs::current_path();
            fs::current_path(current.parent_path());
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }

        curPath = fs::current_path().string();
    }

    isSearch = false;

    selected = 0;

    try {
        fileList = ctrl.getFiles(curPath);
    } catch (const std::filesystem::filesystem_error& e) {
        view.showError(e.what());

        // Reset variables
        curPath = prevPath;
        fs::path current = curPath;
        fileList = ctrl.getFiles(curPath);
    }
}

void MainApp::enter() {
    if (selected == -1) {
        back();
        return;
    }

    if (fileList.empty()) return;

    isSearch = false;

    if (fileList[selected].getIsFolder()) { // OPEN FOLDER
        try {
            fs::path current = fileList[selected].getPath();
            fs::current_path(current);
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }
        curPath = fs::current_path().string();

        selected = 0;
        fileList = ctrl.getFiles(curPath);
    } else { // OPEN FILE
#ifdef _WIN32
        int const bkspChar = 8;
        int const enterChar = 13;
#else
        int const bkspChar = 127;
        int const enterChar = 10;
#endif
        do {
            input.clearScreen();
#ifdef _WIN32
            view.emptyScreen();
            input.clearScreen();
#endif

            view.displayDetails(fileList[selected]);

            int charInput = input.getch();
            switch (charInput) {
                case bkspChar:
                    input.clearScreen();
#ifdef _WIN32
                    view.emptyScreen();
                    input.clearScreen();
#endif
                    return; break;
                case enterChar: break;
                default: break;
            }
        } while (true);
    }
}

void MainApp::startSearch() {
#ifdef _WIN32
    view.emptyScreen();
    input.clearScreen();
#endif
    search Search = search();
    fileList = Search.doSearch(fs::current_path());

    isSearch = true;
}

void MainApp::startSort() {
#ifdef _WIN32
    view.emptyScreen();
    input.clearScreen();
#endif
    Sort sort = Sort(fileList);
    fileList = sort.sortList();
}

void MainApp::makeNew() {
    do {
#ifdef _WIN32
        view.emptyScreen();
        input.clearScreen();
#endif
        view.printHeader("Do you want to make a file [1] or a folder [2]?");

        int charInput = input.getch();
        input.clearScreen();
#ifdef _WIN32
        view.emptyScreen();
        input.clearScreen();
#endif

        switch (charInput) {
            case 49: { // 1 (File)
                view.printHeader("Enter a Name (with the extension):");
                std::string newName = "";
                std::getline(std::cin, newName);

                if (!fs::exists(newName)) { // If there is no file with this name in the directory...
                    std::ofstream newFile(newName);
                }
                else {
                    view.showError("File already exists");
                }

                return;
                break;
            }
            case 50: { // 2 (Folder)
                view.printHeader("Enter a Name:");
                std::string newName = "";
                std::getline(std::cin, newName);


                if (!fs::exists(newName)) { // If there is no file with this name in the directory...
                    fs::create_directory(newName);
                }
                else {
                    view.showError("Folder already exists");
                }
                
                return;
                break;
            }
            default:
                view.showError("Invalid Input");
                break;
        }
    } while (true);
}

void MainApp::renameFile(std::string path) {
    if (path == "") return;
    if (!fs::exists(path)) return;

    fs::path p(path);

    std::string name = p.filename().stem().string();
    std::string extension = p.extension().string();

    input.clearScreen();
#ifdef _WIN32
    view.emptyScreen();
    input.clearScreen();
#endif
    view.printHeader("Rename file: '" + name + "'");

    std::string newName = "";
    std::getline(std::cin, newName);

    if (!fs::exists(newName + extension)) { // If there is no file with this name in the directory...
        try {
            fs::rename(p, newName + extension);
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }
    } else {
        view.showError("File already exists");
    }

    fileList = ctrl.getFiles(curPath); // Refresh
}

void MainApp::deleteFile(std::string path) {
    try {
        fs::path p(path);
        fs::remove_all(p);
    } catch (const fs::filesystem_error& e) {
        view.showError(e.what());
    }

    fileList = ctrl.getFiles(curPath); // Refresh
}