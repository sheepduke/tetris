#include "drawer.hh"
#include "block.hh"
#include "unit.hh"

#include <string>

using std::string;

namespace tetris
{
    Drawer::Drawer(int panel_height, int panel_width)
    {
        initscr();
        start_color();          // use color
        cbreak();               // disable line buffer
        keypad(stdscr, TRUE);   // capture arrow key etc.
        noecho();               // don't display user's input
        curs_set(0);            // don't display cursor
        
        // initialize color pairs
        init_pair(Unit::WHITE, COLOR_BLACK, COLOR_WHITE);
        init_pair(Unit::RED, COLOR_BLACK, COLOR_RED);
        init_pair(Unit::GREEN, COLOR_BLACK, COLOR_GREEN);
        init_pair(Unit::YELLOW, COLOR_BLACK, COLOR_YELLOW);
        init_pair(Unit::BLUE, COLOR_BLACK, COLOR_BLUE);
        init_pair(Unit::CYAN, COLOR_BLACK, COLOR_CYAN);

        // set windows according to panel_size
        panel_height = (panel_height) * (UNIT_HEIGHT - 1) + 1;
        panel_width = (panel_width) * (UNIT_WIDTH - 1) + 1;
        int max_height;
        int max_width;
        getmaxyx(stdscr, max_height, max_width);
        int height = (panel_height >= max_height) ? max_height : panel_height;
        int width = (panel_width >= max_width) ? max_width : panel_width;

        // initialize windows
        game_window = newwin(height, width, 0, 0);
        score_window = newwin(height, max_width - width, 0, width);

        // draw the border of windows
        box(game_window, 0, 0);
        box(score_window, 0, 0);
        // refresh windows
        wrefresh(game_window);
        wrefresh(score_window);
    }

    Drawer::~Drawer()
    {
        delwin(game_window);
        delwin(score_window);
        endwin();
    }

    void Drawer::draw(Block * block)
    {
        if (dynamic_cast<StickBlock *>(block) != NULL)
            draw(*dynamic_cast<StickBlock *>(block));
        else if (dynamic_cast<SquareBlock *>(block) != NULL)
            draw(*dynamic_cast<SquareBlock *>(block));
    }

    void Drawer::draw(const StickBlock & block)
    {
        auto & units = block.get_units();
        draw(units[0]);
        draw(units[1], -1, 0);
        draw(units[2], -2, 0);
        draw(units[3], -3, 0);
        refresh();
    }

    void Drawer::draw(const SquareBlock & block)
    {
        auto & units = block.get_units();
        draw(units[0]);
        draw(units[1], 0, -1);
        draw(units[2], -1, 0);
        draw(units[3], -1, -1);
        refresh();
    }

    void Drawer::draw(const Unit & unit, int offset_y, int offset_x)
    {
        WINDOW * win = newwin(UNIT_HEIGHT, UNIT_WIDTH,
                              unit.y() * UNIT_HEIGHT + offset_y,
                              unit.x() * UNIT_WIDTH + offset_x);
        // wattron(win, COLOR_PAIR(color_pair) | A_REVERSE);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        // wattroff(win, COLOR_PAIR(color_pair) | A_REVERSE);
        wattron(win, COLOR_PAIR(unit.color()));
        mvwprintw(win, 1, 1, string(UNIT_WIDTH - 2, ' ').c_str());
        wattroff(win, COLOR_PAIR(unit.color()));
        window_table[&unit] = win;
    }

    void Drawer::clear(const Block & block)
    {
        // auto & units = block.get_units();
        // for (auto it = units.cbegin(); it != units.cend(); it++)
        // {
        //     WINDOW * win = window_table[&*it];
        //     if (win != NULL)
        //     {
        //         wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        //         mvwprintw(win, 1, 1, string(UNIT_WIDTH - 2, ' ').c_str());
        //         wrefresh(win);
        //         delwin(win);
        //         window_table.erase(&*it);
        //     }
        // }
        // refresh();

        // werase(game_window);
        // werase(score_window);
        refresh();
    }

    void Drawer::refresh()
    {
        for (auto it = window_table.begin(); it != window_table.end(); it++)
        {
            wrefresh(it->second);
        }
        // box(game_window, 0, 0);
        wrefresh(game_window);
        // box(score_window, 0, 0);
        wrefresh(score_window);
    }
}
