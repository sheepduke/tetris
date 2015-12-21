#ifndef DRAWER_HH
#define DRAWER_HH

#include <ncurses.h>

#include "panel.hh"

namespace tetris
{
    class Panel;
    class StickBlock;
    class SquareBlock;
    class Block;
    class Unit;
    
    class Drawer : public PanelVisitor
    {
    public:
        Drawer();
        ~Drawer();

        void get_panel_size(int & height, int & width);

        // draw different shapes of blocks
        void draw(const Block & block);
        void draw(const StickBlock & block);
        void draw(const SquareBlock & block);

        // clear the block
        void clear(Block * block);
        
        // draw the panel
        void draw(const Panel & panel);

        // virtual function from PanelVisitor
        virtual void visit(Unit * unit);

    protected:
        static const int PANEL_WIDTH = 10;
        static const int UNIT_HEIGHT = 3;
        static const int UNIT_WIDTH = 5;

    private:
        // Draw a unit.
        // offset_y is the offset that this function will take while
        // drawing the height. offset_x is for the width.
        void draw(const Unit & unit);

        Position get_scaled_position(const Unit & unit) const;

        WINDOW * game_window;
        WINDOW * score_window;

        int panel_height;
        int panel_width;
        int window_height;
        int window_width;
    };
}

#endif
