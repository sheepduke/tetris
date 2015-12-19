#include <ncurses.h>

#include "drawer.hh"
#include "block.hh"
#include "point.hh"

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

    void Drawer::draw(const Block & block)
    {
        const vector<Point> & points = block.get_points();
        for (auto it = points.begin(); it != points.end(); it++)
        {
            draw(*it);
        }
    }

    void Drawer::draw(const Point & point)
    {
        int color_pair = WHITE;

        switch (point.color())
        {
        case Point::WHITE:
            color_pair = WHITE;
            break;
        case Point::RED:
            color_pair = RED;
            break;
        case Point::GREEN:
            color_pair = GREEN;
            break;
        case Point::YELLOW:
            color_pair = YELLOW;
            break;
        case Point::BLUE:
            color_pair = BLUE;
            break;
        case Point::CYAN:
            color_pair = CYAN;
            break;
        }
        init_pair(9, COLOR_WHITE, COLOR_RED);
        attron(COLOR_PAIR(9));
        mvprintw(point.y(), point.x(), "  ");
        attroff(COLOR_PAIR(9));
    }

    void Drawer::clear(const Block & block)
    {
        const vector<Point> & points = block.get_points();
        for (auto it = points.begin(); it != points.end(); it++)
        {
            mvprintw(it->y(), it->x(), "  ");
        }
    }
}
