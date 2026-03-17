#include "MainApp.h"

namespace fs = std::filesystem;

MainApp::MainApp() {
    curPath = "C:\\Users\\2000389\\OneDrive - Dundee and Angus College\\Documents";
    std::cout << curPath << std::endl;
    fileList = getFiles(curPath);

    changeSelect(-1);
}

std::vector<File> MainApp::getFiles(std::string path) {
    selected = 0;
    std::vector<File> newList;

    for (auto& p : fs::directory_iterator(path)) {
        std::string curF = p.path().string();

        File temp = File(
            p.path().filename().stem().string(),
            p.path().extension().string(),
            (int)p.file_size(),
            p.is_directory()
        );

        newList.push_back(temp);
    }

    return newList;
}

void MainApp::changeSelect(int a) {
    selected += a;
    view.displayFiles(fileList, selected);
}