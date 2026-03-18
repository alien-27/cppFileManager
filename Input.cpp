#include "Input.h"

#include <iostream>
#include <iomanip>

#ifdef _WIN32

// WINDOWS

#include <conio.h>

int Input::getch() {
	return _getch();
}

void Input::clear() {
	system("cls");
}

#else

// MAC & LINUX

#include <termios.h>
#include <unistd.h>
#include <cstdlib>

int unix_getch() {
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

int Input::getch() {
	return unix_getch();
}

void Input::clear() {
	system("clear");
}

#endif