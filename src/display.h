#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
    private:
        int w;
        int h;
        int fg;
        int bg;

    public:
        Display() = default;
        Display(int width, int height);
        void clear();
        int termWidth();
        int termHeight();
        void goTo(int x, int y);
        void setAt(int x, int y, char chr);
        void setTextColor(int color);
        void setBackgroundColor(int color);
};

#endif
