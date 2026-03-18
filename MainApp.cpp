#include "MainApp.h"

#include <iostream>
MainApp::MainApp() {
    //curPath = "C:\\Users\\2000389\\OneDrive - Dundee and Angus College\\Documents";
    std::cout << curPath << std::endl;
    selected = 0;
    fileList = ctrl.getFiles(curPath);

    input.clear();
    view.displayFiles(curPath, fileList, selected);

    do {
        int charInput = input.getch();

#ifdef _WIN32
// WINDOWS
        if (charInput == 0 || charInput == 224) { // Special keys
            charInput = input.getch();
            switch (charInput) {
                case 72: // Up Arrow
                    selected = ctrl.setSelect(selected - 1, -1, fileList.size());
                    break;
                case 80: // Down Arrow
                    selected = ctrl.setSelect(selected + 1, -1, fileList.size());
                    break;
                case 71: // Home
                    selected = ctrl.setSelect(-1, -1, fileList.size());
                    break;
                case 79: // End
                    selected = ctrl.setSelect(fileList.size() - 1, -1, fileList.size());
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

                    break;
                default:
                    break;
            }
        }
#else
// MAC & LINUX

        // TO-DO: add linux and mac implementatoin

#endif

        input.clear();
        view.displayFiles(curPath, fileList, selected);

        std::cout << charInput;
    } while (true);
}

void MainApp::back() {
    fs::path current = fs::current_path();
    fs::current_path(current.parent_path());
    curPath = fs::current_path().string();

    selected = 0;
    fileList = ctrl.getFiles(curPath);
}