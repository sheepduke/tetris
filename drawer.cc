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
        // leave the border alone!
        panel_height += 2;
        panel_width += 2;
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
        wprintw(game_window, "%d", panel_height);
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

    void Drawer::draw(const Block & block)
    {
        auto & units = block.get_units();
        
        for (auto it = units.begin(); it != units.end(); it++)
        {
            draw(*it);
        }
    }

    void Drawer::clear(Block * block)
    {
        auto & units = block->get_units();

        for (auto it = units.begin(); it != units.end(); it++)
        {
            Position pos = get_scaled_position(*it);
            for (int i = 0; i < 3; i++)
                mvwprintw(game_window, pos.y() + i, pos.x(), "     ");
        }
        wrefresh(game_window);
    }

    void Drawer::draw(const Panel & panel)
    {
        panel.traverse(this);
    }
    
    void Drawer::visit(Unit * unit)
    {
        if (unit)
            draw(*unit);
    }

    void Drawer::draw(const Unit & unit)
    {
        Position pos = get_scaled_position(unit);

        // print top and bottom
        for (int y = pos.y(); y <= pos.y() + 2; y += 2)
        {
            mvwprintw(game_window, y, pos.x(), "+");
            for (int i = 1; i <= 3; i++)
                mvwprintw(game_window, y, pos.x() + i, "-");
            mvwprintw(game_window, y, pos.x() + 4, "+");
        }
        
        mvwprintw(game_window, pos.y() + 1, pos.x(), "|");
        wattron(game_window, COLOR_PAIR(unit.color()));
        for (int i = 1; i <= 3; i++)
            mvwprintw(game_window, pos.y() + 1, pos.x() + i, " ");
        wattroff(game_window, COLOR_PAIR(unit.color()));
        mvwprintw(game_window, pos.y() + 1, pos.x() + 4, "|");
        wrefresh(game_window);
    }

    Position Drawer::get_scaled_position(const Unit & unit) const
    {
        return Position(unit.y() * (UNIT_HEIGHT - 1) + 1,
                        unit.x() * (UNIT_WIDTH - 1) + 1);
    }
}
