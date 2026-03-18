#include "MainController.h"

namespace fs = std::filesystem;

std::vector<File> MainController::getFiles(std::string path) {
    std::vector<File> newList;

    for (auto& p : fs::directory_iterator(path)) {
        std::string curF = p.path().string();

        auto ftime = fs::last_write_time(p.path());
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());

        // Create file
        File temp = File(
            p.path().filename().stem().string(),
            p.path().extension().string(),
            (int)p.file_size(),
            std::chrono::system_clock::to_time_t(sctp),
            p.is_directory()
        );

        // Add file to vector
        newList.push_back(temp);
    }

    return newList;
}

int MainController::setSelect(int s, int min, int max) {
    int newS = s;

    if (newS < min) newS += max + 1;
    if (newS >= max) newS = min;

    return newS;
}