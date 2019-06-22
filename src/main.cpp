#include "life.h"
#include "display.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int width = 0;
    int height = 0;
    bool toroid = false;
    int fg = 7;
    int bg = 0;
    for (int i = 1; i < argc; i++) {
        if (((string)argv[i] == "-w" || (string)argv[i] == "--width") && i + 1 < argc) {
            try {
                width = stoi((string)argv[++i]);
            } catch(exception) {}
        }
        else if (((string)argv[i] == "-h" || (string)argv[i] == "--height") && i + 1 < argc) {
            try {
                height = stoi((string)argv[++i]);
            } catch(exception) {}
        }
        else if ((string)argv[i] == "-t" || (string)argv[i] == "--toroid") {
            toroid = true;
        }
        else if (((string)argv[i] == "-fg" || (string)argv[i] == "--foreground") && i + 1 < argc) {
            try {
                fg = stoi(argv[++i]);
            } catch(exception) {}
        }
        else if (((string)argv[i] == "-bg" || (string)argv[i] == "--background") && i + 1 < argc) {
            try {
                bg = stoi(argv[++i]);
            } catch(exception) {}
        }
    }
    Life life = Life(width, height, toroid, fg, bg);
    life.run();
    return 0;
}
