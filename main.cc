#include "drawer.hh"
#include "panel.hh"
#include "block.hh"
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;
using namespace tetris;

Block * block = NULL;
bool end_program = false;
bool keyboard_lock = false;

static const int INIT_Y = 0;
static const int INIT_X = 6;
static const int BLOCK_DROP_INTEVAL = 200;

Block * make_block(const Panel & panel);
void interact(Drawer * drawer, Panel * panel, Block * block);
void show_game_over(const Panel & panel);

int main()
{
    Drawer drawer;

    int height, width;
    drawer.get_panel_size(height, width);
    Panel panel(height, width);
    drawer.draw(panel);

    block = make_block(panel);
    drawer.draw(*block);

    thread interact_thread(interact, &drawer, &panel, block);

    while (!end_program)
    {
        if (!keyboard_lock)
        {
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
            drawer.draw(*block);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(BLOCK_DROP_INTEVAL));
    }

    interact_thread.join();

    // debug
    // interact(&drawer, &panel, block);

    // // debug
    // block = new StickBlock(2, 2);
    // block->rotate(panel);
    // block->move_left(panel);
    // block->drop(panel);
    // panel.fix_block(*block);
    // drawer.draw(*block);
    // std::this_thread::sleep_for(std::chrono::milliseconds(0));
        
    // block = new StickBlock(2, 2);
    // block->rotate(panel);
    // block->move_left(panel);
    // block->drop(panel);
    // panel.fix_block(*block);
    // drawer.draw(*block);
    // std::this_thread::sleep_for(std::chrono::milliseconds(0));
    
    // block = new SquareBlock(2, 4);
    // block->drop(panel);
    // panel.fix_block(*block);
    // drawer.draw(*block);
    // std::this_thread::sleep_for(std::chrono::milliseconds(0));
    
    // block = new SquareBlock(2, 6);
    // block->drop(panel);
    // panel.fix_block(*block);
    // drawer.draw(*block);
    // delete block;
    // std::this_thread::sleep_for(std::chrono::milliseconds(0));

    // block = new SquareBlock(2, 8);
    // block->drop(panel);
    // panel.fix_block(*block);
    // drawer.draw(*block);
    // delete block;
    // std::this_thread::sleep_for(std::chrono::milliseconds(0));
    
    // drawer.draw(panel);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    return 0;
}

void interact(Drawer * drawer, Panel * panel, Block * block)
{
    int ch;
    while (!end_program && (ch = drawer->user_input()))
    {
        keyboard_lock = true;
        // quit the program
        if (ch == 'q')
            end_program = true;
        else if (ch == ' ')
        {
            drawer->clear(*block);
            block->drop(*panel);
            panel->fix_block(*block);
            drawer->draw(*panel);
            // delete block;
            if ((block = make_block(*panel)) == NULL)
            {
                end_program = true;
                show_game_over(*panel);
                break;
            }
            else
                drawer->draw(*block);
        }
        else
        {
            // get key input and react
            drawer->clear(*block);
            switch (ch)
            {
            case 'w':
                block->rotate(*panel);
                break;
            case 'a':
                block->move_left(*panel);
                break;
            case 'd':
                block->move_right(*panel);
                break;
            case 's':
                block->move_down(*panel);
                break;
            case ' ':
                break;
            default:
                block->move_down(*panel);
                break;
            }
            drawer->draw(*block);
        }
        keyboard_lock = false;
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
