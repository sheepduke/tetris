#include <ncurses.h>

#include "drawer.hh"
#include "shape.hh"
#include "block.hh"

namespace tetris
{
    Drawer::Drawer()
    {
        initscr();
        // use color
        start_color();
        // disable line buffer
        raw();
        // capture arrow key etc.
        keypad(stdscr, TRUE);
        // don't display user's input
        noecho();
        // don't display cursor
        curs_set(0);
        // initialize color pairs
        init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
        init_pair(RED, COLOR_BLACK, COLOR_RED);
        init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
        init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
        init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
        init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
    }

    Drawer::~Drawer()
    {
        endwin();
    }

    void Drawer::draw(const Shape & shape)
    {
        const vector<Block> & blocks = shape.get_blocks();
        for (auto it = blocks.begin(); it != blocks.end(); it++)
        {
            draw(*it);
        }
    }

    void Drawer::draw(const Block & block)
    {
        int color_pair = WHITE;

        switch (block.color())
        {
        case Block::WHITE:
            color_pair = WHITE;
            break;
        case Block::RED:
            color_pair = RED;
            break;
        case Block::GREEN:
            color_pair = GREEN;
            break;
        case Block::YELLOW:
            color_pair = YELLOW;
            break;
        case Block::BLUE:
            color_pair = BLUE;
            break;
        case Block::CYAN:
            color_pair = CYAN;
            break;
        }
        init_pair(9, COLOR_WHITE, COLOR_RED);
        attron(COLOR_PAIR(9));
        mvprintw(block.y(), block.x(), "  ");
        attroff(COLOR_PAIR(9));
    }

    void Drawer::clear(const Shape & shape)
    {
        const vector<Block> & blocks = shape.get_blocks();
        for (auto it = blocks.begin(); it != blocks.end(); it++)
        {
            mvprintw(it->y(), it->x(), "  ");
        }
    }
}
