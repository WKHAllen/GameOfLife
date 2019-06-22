#ifndef LIFE_H
#define LIFE_H

#include "display.h"
#include <vector>

using namespace std;

class Life {
    private:
        int w;
        int h;
        bool toroidal;
        vector<vector<int>> board;
        Display screen;
        int numNeighbors(vector<vector<int>> b, int x, int y);
        vector<vector<int>> clone(vector<vector<int>> b);

    public:
        Life(int width, int height, bool toroid, int fg, int bg);
        Life(int width, int height, bool toroid);
        Life(bool toroid);
        void next();
        void display();
        void run();
};

#endif
