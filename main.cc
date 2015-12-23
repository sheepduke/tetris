#include <ncurses.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <mutex>

#include "drawer.hh"
#include "panel.hh"
#include "block.hh"

using namespace std;
using namespace tetris;

bool end_program = false;
mutex handle_lock;

static const int INIT_Y = 0;
static const int INIT_X = 6;
static const int BLOCK_DROP_INTEVAL = 200;

// Make a random block according to `panel'.
Block * make_block(const Panel & panel);
// React for user's input.
void interact(Drawer & drawer, Panel & panel, Block *& block);
// Show the Game-Over dialog, including the score.
void show_game_over(const Panel & panel);
// Show "Quit?" dialog
bool show_quit_dialog(const Panel & panel);

int main()
{
    Drawer drawer;

    int height, width;
    drawer.get_panel_size(height, width);
    Panel panel(height, width);
    drawer.draw(panel);

    Block * block = make_block(panel);
    drawer.draw(*block);

    thread interact_thread(interact, ref(drawer), ref(panel), ref(block));

    while (!end_program)
    {
        handle_lock.lock();
        if (end_program)
            break;

        drawer.clear(*block);

        if (!block->move_down(panel))
        {
            panel.fix_block(*block);
            drawer.draw(panel);
            delete block;
            if ((block = make_block(panel)) == NULL)
            {
                end_program = true;
                show_game_over(panel);
                break;
            }
            else
                drawer.draw(*block);
        }
        else
            drawer.draw(*block);
        handle_lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(BLOCK_DROP_INTEVAL));
    }

    interact_thread.join();
    
    return 0;
}

void interact(Drawer & drawer, Panel & panel, Block *& block)
{
    while (!end_program)
    {
        int ch = drawer.user_input();
        handle_lock.lock();
        // quit the program
        if (ch == 'q')
        {
            end_program = show_quit_dialog(panel);
        }
        else if (ch == ' ')
        {
            drawer.clear(*block);
            // block.drop(*panel);
            while (block->move_down(panel));
            panel.fix_block(*block);
            drawer.draw(panel);
            delete block;
            if ((block = make_block(panel)) == NULL)
            {
                end_program = true;
                show_game_over(panel);
                break;
            }
            else
                drawer.draw(*block);
        }
        else
        {
            // get key input and react
            drawer.clear(*block);
            switch (ch)
            {
            case 'w':
                block->rotate(panel);
                break;
            case 'a':
                block->move_left(panel);
                break;
            case 'd':
                block->move_right(panel);
                break;
            case 's':
                block->move_down(panel);
                break;
            case ' ':
                break;
            default:
                block->move_down(panel);
                break;
            }
            drawer.draw(*block);
        }
        handle_lock.unlock();
    }
}

Block * make_block(const Panel & panel)
{
    if (!panel.is_legal(INIT_Y, INIT_X))
        return NULL;
    
    return RandomBlockFactory::create_block(INIT_Y, INIT_X);
}

void show_game_over(const Panel & panel)
{
    int parent_y;
    int parent_x;
    getmaxyx(stdscr, parent_y, parent_x);
    // get score in string
    stringstream ss;
    ss << "Your Score: ";
    ss << panel.score();
    int width = ss.str().length();
    // create the game over screen
    WINDOW * win = newwin(4, width + 2, (parent_y - 4) / 2,
                          (parent_x - width - 2) / 2);
    box(win, 0, 0);

    mvwprintw(win, 1, (width - 7) / 2, "Game Over");
    mvwprintw(win, 2, 1, ss.str().c_str());
    wrefresh(win);
    wgetch(win);
    delwin(win);
}

bool show_quit_dialog(const Panel & panel)
{
    int parent_y;
    int parent_x;
    getmaxyx(stdscr, parent_y, parent_x);

    string prompt = "Quit? (y/n)";
    int width = prompt.length();
    WINDOW * win = newwin(3, width + 2, (parent_y - 3) / 2,
                          (parent_x - width - 2) / 2);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, prompt.c_str());
    wrefresh(win);

    while (true)
    {
        switch (wgetch(win))
        {
        case 'y':
            return true;
        case 'n':
            wclear(win);
            wrefresh(win);
            return false;
        default:
            break;
        }
    }
    
    delwin(win);
}
