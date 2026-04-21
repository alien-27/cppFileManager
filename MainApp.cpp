#include "MainApp.h"

#include "search.h"
#include "Sort.h"
#include "Encrypt.h"
#include "TextEditor.h"

#include "TextFile.h"

#include <fstream>

/// <summary>
/// The main loop
/// </summary>
MainApp::MainApp() {
    selected = 0;
    fileList = ctrl.getFiles(curPath);

    input.clearScreen();
    view.printHeader(curPath);
    view.displayFiles(fileList, selected);

    // Get value of special characters.
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

    do { // Get a character input and do a thing based on that input.
        int charInput = input.getch();
        input.clearScreen();

        bool screenEmpty = true;

        // Some keyboard inputs are made up of two characters. What the if statement below does is check
        // if the first one is a special key, and gets the input from the second one.
#ifdef _WIN32
        if (charInput == 0 || charInput == 224) {
#else
        if (charInput == 91) {
#endif
            charInput = input.getch();
            screenEmpty = false;
            switch (charInput) {
                case upChar: // Up Arrow, Change selection by -1
                    selected = ctrl.setSelect(selected - 1, -1, (int)fileList.size()); break;
                case downChar: // Down Arrow, Change selection by 1
                    selected = ctrl.setSelect(selected + 1, -1, (int)fileList.size()); break;
                case homeChar: // Home, Go to Top
                    selected = ctrl.setSelect(0, -1, (int)fileList.size()); break;
                case endChar: // End, Go to Bottom
                    selected = ctrl.setSelect((int)fileList.size() - 1, -1, (int)fileList.size()); break;
                default: break;
            }
        } else {
            switch (charInput) {
                case bkspChar: // Backspace, exit this directory
                    back(); break;
                case enterChar: // Enter, enter selected file/folder
                    enter(); break;
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
                    encrypt(fileList[selected]); break;
                case 48: // 0 (Exit)
                    clearScreen();
                    view.exitMessage();
                    return;
                default:
                    break;
            }
        }

#ifdef _WIN32
        if (screenEmpty) {
            input.emptyScreen();
            input.clearScreen();
        }
#endif

        view.printHeader(curPath);
        view.displayFiles(fileList, selected);
    } while (true);
}

void MainApp::back() {
    std::string prevPath = curPath; // Store current path incase something goes wrong

    if (!isSearch) { // Only go into the containing folder if the user isn't searching
        try {
            fs::path current = fs::current_path();
            fs::current_path(current.parent_path());
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }

        curPath = fs::current_path().string();
    }

    // Reset variables
    isSearch = false;
    selected = 0;

    // Try and get list of files in new directory
    try {
        fileList = ctrl.getFiles(curPath);
    } catch (const std::filesystem::filesystem_error& e) {
        // Show error and go to previous path.
        view.showError(e.what());

        curPath = prevPath;
        fs::path current = curPath;
        fileList = ctrl.getFiles(curPath);
    }
}

/// <summary>
/// Code to be executed when 'enter' is pressed
/// </summary>
void MainApp::enter() {
    if (selected == -1) { // If "<< Back" is selected.
        back(); // Go back,
        return; // Don't do the rest of this function.
    }

    if (fileList.empty()) return; // Stop if there are no files to enter.

    isSearch = false; // Reset search.

    if (fileList[selected].getIsFolder()) { // OPEN FOLDER
        try {
            fs::path current = fileList[selected].getPath();
            fs::current_path(current);
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }
        curPath = fs::current_path().string();

        selected = 0;
        fileList = ctrl.getFiles(curPath); // Get the list of files
    } else { // OPEN FILE
#ifdef _WIN32
        int const bkspChar = 8;
        int const enterChar = 13;
#else
        int const bkspChar = 127;
        int const enterChar = 10;
#endif

        // This dipslays the files details...
        do { // ...until the user exits this screen.
            clearScreen();
            view.displayDetails(fileList[selected]);

            int charInput = input.getch();
            switch (charInput) {
                case bkspChar: clearScreen(); return; break; // Exit this screen.
                case enterChar: // Enter text editor (on text files only)
                    if (fileList[selected].getType() == "Text" || fileList[selected].getType() == "Code") {
                        TextEditor te = TextEditor(fileList[selected].getPath());
                    }
                    break;
                default: break;
            }
        } while (true);
    }
}

/// <summary>
/// Gets a new list of files from the search class
/// </summary>
void MainApp::startSearch() {
    clearScreen();
    search Search = search();
    fileList = Search.doSearch(fs::current_path());

    isSearch = true;
}

/// <summary>
/// Uses the sort class to sort the file list
/// </summary>
void MainApp::startSort() {
    clearScreen();
    Sort sort = Sort(fileList);

    do {
        // Ask user to sort files
        view.printHeader("Sort Files:");
        view.printSortOptions();

        // Get user input
        int charInput = input.getch();
        clearScreen();

        // Sort files based on input
        switch (charInput) {
            case 49: fileList = sort.sortList("Name", "ASC"); return; break;
            case 50: fileList = sort.sortList("Name", "DESC"); return; break;
            case 51: fileList = sort.sortList("Size", "ASC"); return; break;
            case 52: fileList = sort.sortList("Size", "DESC"); return; break;
            case 53: fileList = sort.sortList("Extension", "ASC"); return; break;
            case 54: fileList = sort.sortList("Extension", "DESC"); return; break;
            case 55: fileList = sort.sortList("Date", "ASC"); return; break;
            case 56: fileList = sort.sortList("Date", "DESC"); return; break;
            default: view.showError("Invalid Input"); break;
        }
    } while (true);
}

/// <summary>
/// Creates a new file or folder.
/// </summary>
void MainApp::makeNew() {
    do { // Repeat until we gat a valid input.
        // Ask user what they want to make.
        clearScreen();
        view.printHeader("Do you want to make a file [1] or a folder [2]?");

        // Get user input
        int charInput = input.getch();
        clearScreen();

        if (charInput == 49 || charInput == 50) { // If input is valid...
            std::string itemToCreate = "File";
            if (charInput == 50) {
                itemToCreate = "Folder";
            }

            // Get a name from the user.
            if (itemToCreate == "File") {
                view.printHeader("Enter a Name (with the extension):");
            } else {
                view.printHeader("Enter a Name:");
            }
            std::string newName = "";
            std::getline(std::cin, newName);

            if (!fs::exists(newName)) { // If there is no file with this name in the directory...
                if (itemToCreate == "File") {
                    std::ofstream newFile(newName); // Create the file.
                } else {
                    fs::create_directory(newName); // Create the folder
                }
            } else {
                view.showError(itemToCreate + " already exists"); // else, display an error.
            }

            return;
        } else {
            view.showError("Invalid Input"); // Show error
        }
    } while (true);
}

/// <summary>
/// Renames a chosen file
/// </summary>
/// <param name="path">The path of the file to be renamed</param>
void MainApp::renameFile(std::string path) {
    if (path == "") return; // Stop if there is no file to rename
    if (!fs::exists(path)) return; // Stop if the file doesn't exist.

    fs::path p(path);

    // Get original name
    std::string name = p.filename().stem().string();
    std::string extension = p.extension().string();

    // Ask user to enter a new name
    clearScreen();
    view.printHeader("Rename file: '" + name + "'");

    // Get new name from user.
    std::string newName = "";
    std::getline(std::cin, newName);

    if (!fs::exists(newName + extension)) { // If there is no file with this name in the directory...
        try { // Try and rename the file.
            fs::rename(p, newName + extension);
        } catch (const fs::filesystem_error& e) {
            view.showError(e.what());
        }
    } else {
        view.showError("File already exists"); // ... else display an error
    }

    fileList = ctrl.getFiles(curPath); // Refresh file list
}

/// <summary>
/// Deletes a file
/// </summary>
/// <param name="path">The path of the file to be deleted</param>
void MainApp::deleteFile(std::string path) {
    try { // Try and delete the file
        fs::path p(path);
        fs::remove_all(p);
    } catch (const fs::filesystem_error& e) {
        view.showError(e.what()); // Display error if failed
    }

    fileList = ctrl.getFiles(curPath); // Refresh
}

/// <summary>
/// Creates a new file which stores the encrypted/decrypted content of the selected file.
/// </summary>
/// <param name="f">The selected filepath</param>
void MainApp::encrypt(File f) {
    if (f.getType() != "Text" && f.getType() != "Code" && f.getExtension() != ".encr") { // If this is not a text file, stop.
        view.showError("Cannot encrypt non text files"); return;
    }

    std::string newFileName = ""; // The destination name of the newly encrypted/decrypted file.
    std::string headerText = ""; // The text tht will be displayed at the top of the screen.

    if (f.getExtension() == ".encr") { // File is encrypted, we want to decrypt this.
        newFileName = f.getName();
        headerText = "Enter the encryption key: ";
    } else { // File is not encrypted, we want to encrypt this.
        newFileName = f.getNameWithExtension() + ".encr";
        headerText = "Enter an encryption key (Remember this!): ";
    }

    if (fs::exists(newFileName)) { // Stop if a file with the destination name exists.
        view.showError("Destination file already exists."); return;
    }

    // Ask user to input key
    clearScreen();
    view.printHeader(headerText);

    // Get the key from the user
    std::string key = "";
    std::getline(std::cin, key);

    Encrypt e = Encrypt();

    // Creates the new file
    std::string const newPath = curPath + "/" + newFileName;
    
    // Open the file
    std::ofstream encFile(newPath);

    // Fills the file.
    if (f.getExtension() == ".encr") {
        encFile << e.decrypt(curPath + "/" + f.getNameWithExtension(), key);
    } else {
        encFile << e.encrypt(curPath + "/" + f.getNameWithExtension(), key);
    }
    
    // Close the file
    encFile.close();

    fileList = ctrl.getFiles(curPath); // Refresh
}

/// <summary>
/// Clears the screen
/// </summary>
void MainApp::clearScreen() {
    input.clearScreen();
#ifdef _WIN32
    input.emptyScreen();
    input.clearScreen();
#endif
}