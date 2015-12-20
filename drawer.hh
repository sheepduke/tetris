#ifndef DRAWER_HH
#define DRAWER_HH

#include <map>
#include <ncurses.h>

using std::map;

namespace tetris
{
    class Panel;
    class StickBlock;
    class SquareBlock;
    class Block;
    class Unit;
    
    class Drawer
    {
    public:
        Drawer(int panel_height, int panel_width);
        ~Drawer();

        void draw(Block * block);
        void draw(const StickBlock & block);
        void draw(const SquareBlock & block);

        void clear(const Block & block);

        static const int UNIT_HEIGHT = 3;
        static const int UNIT_WIDTH = 5;

    private:
        // Draw a unit.
        // offset_y is the offset that this function will take while
        // drawing the height. offset_x is for the width.
        void draw(const Unit & unit, int offset_y = 0, int offset_x = 0);
        void refresh();

        WINDOW * game_window;
        WINDOW * score_window;

        map<const Unit *, WINDOW *> window_table;
    };
}

#endif
