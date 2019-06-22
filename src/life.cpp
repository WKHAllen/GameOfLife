#include "life.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

void sleep(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

Life::Life(int width, int height, bool toroid, int fg, int bg) {
    Display d = Display();
    if (width == 0) {
        width = d.termWidth();
    }
    if (height == 0) {
        height = d.termHeight();
    }
    w = width;
    h = height;
    toroidal = toroid;
    board.resize(w, vector<int>(h));
    screen = Display(w, h);
    screen.setTextColor(fg);
    screen.setBackgroundColor(bg);
    screen.clear();
    srand(time(NULL));
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            board[i][j] = rand() % 2; // random board
            // board[i][j] = 0; // empty board
        }
    }
    // glider:
    // board[0][0] = board[2][0] = board[1][1] = board[1][2] = board[2][1] = 1;
    // glider gun:
    // board[1][5] = board[1][6] = board[2][5] = board[2][6] = board[11][5] = board[11][6] = board[11][7] = board[12][4] = board[12][8] = board[13][3] = board[13][9] = board[14][3] = board[14][9] = board[15][6] = board[16][4] = board[16][8] = board[17][5] = board[17][6] = board[17][7] = board[18][6] = board[21][3] = board[21][4] = board[21][5] = board[22][3] = board[22][4] = board[22][5] = board[23][2] = board[23][6] = board[25][1] = board[25][2] = board[25][6] = board[25][7] = board[35][3] = board[35][4] = board[36][3] = board[36][4] = 1;
}

Life::Life(int width, int height, bool toroid) : Life(width, height, toroid, 7, 0) {}

Life::Life(bool toroid) : Life(0, 0, toroid) {}

vector<vector<int>> Life::clone(vector<vector<int>> b) {
    vector<vector<int>> newboard;
    for (int i = 0; i < b.size(); i++) {
        vector<int> newrow;
        for (int j = 0; j < b[i].size(); j++) {
            newrow.push_back(b[i][j]);
        }
        newboard.push_back(newrow);
    }
    return newboard;
}

int Life::numNeighbors(vector<vector<int>> b, int x, int y) {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i != x || j != y) {
                if (toroidal) {
                    if (b[(i + w) % w][(j + h) % h] == 1) {
                        neighbors++;
                    }
                }
                else {
                    if (i >= 0 && i < w && j >= 0 && j < h && b[i][j] == 1) {
                        neighbors++;
                    }
                }
            }
        }
    }
    return neighbors;
}

void Life::next() {
    int neighbors;
    vector<vector<int>> oldboard = clone(board);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            neighbors = numNeighbors(oldboard, i, j);
            if (board[i][j] == 1 && (neighbors < 2 || neighbors > 3)) {
                board[i][j] = 0;
                screen.setAt(i, j, ' ');
            }
            else if (board[i][j] == 0 && neighbors == 3) {
                board[i][j] = 1;
                screen.setAt(i, j, 219);
            }
        }
    }
}

void Life::display() { // using this instead of displaying things in Life::next is good practice, but far slower
    char chr;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            chr = board[i][j] == 0 ? ' ' : 219;
            screen.setAt(i, j, chr);
        }
    }
}

void Life::run() {
    while (true) {
        // display();
        // sleep(1000 / 10);
        next();
    }
}
