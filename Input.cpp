#include "Input.h"

#include <iostream>
#include <iomanip>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

/// <summary>
/// Get a character from keyboard inputs
/// </summary>
/// <returns></returns>
int Input::getch() {
	return _getch();
}

void Input::clearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

/// <summary>
/// Return the width of the screen
/// </summary>
/// <returns></returns>
int Input::consoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

/// <summary>
/// Return the height of the screen
/// </summary>
/// <returns></returns>
int Input::consoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}

#else

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

/// <summary>
/// Get a character from keyboard inputs
/// </summary>
/// <returns></returns>
int Input::getch() {
	struct termios oldTermios, newTermios;
    int ch;
    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    return ch;
}

void Input::clearScreen() {
	system("clear");
}

/// <summary>
/// Return the width of the screen
/// </summary>
/// <returns></returns>
int Input::consoleWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

/// <summary>
/// Return the height of the screen
/// </summary>
/// <returns></returns>
int Input::consoleHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

#endif

/// <summary>
/// Fills the screen with black (empty) space.
/// </summary>
void Input::emptyScreen() {
    int width = consoleWidth();
    int height = consoleHeight();
    for (int i = 0; i < height; i++) {
        std::cout << std::string(width, ' ');
    }
}