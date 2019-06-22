#include "display.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <term.h>
    #include <sys/ioctl.h>
    #include <stdio.h>
#endif

// not tested on Unix

using namespace std;

Display::Display(int width, int height) {
    w = width;
    h = height;
}

void Display::clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int Display::termWidth() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int columns = w.ws_col;
        return columns;
    #endif
}

int Display::termHeight() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return rows;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int rows = w.ws_row;
        return rows;
    #endif
}

void Display::goTo(int x, int y) {
    #ifdef _WIN32
        COORD p = {(short)x, (short)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
    #else
        int err;
        if (!cur_term) {
            if (setupterm(NULL, STDOUT_FILENO, &err ) == ERR) {
                return;
            }
        }
        putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
    #endif
}

void Display::setAt(int x, int y, char chr) {
    goTo(x, y);
    cout << chr;
}

void Display::setTextColor(int color) {
    #ifdef _WIN32
        fg = color;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
    #else
        cout << "\033[" << color << "m";
    #endif
}

void Display::setBackgroundColor(int color) {
    #ifdef _WIN32
        bg = color;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
    #else
        cout << "\033[" << color << "m";
    #endif
}
