#include "drawer.hh"
#include "panel.hh"
#include "block.hh"
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace tetris;

bool end_program = false;

// void draw(Drawer * drawer, Panel * panel, Block * block)
// {
//     while (!end_program)
//     {
//         drawer->clear(*block);

//         if (!block->move_down(*panel))
//             break;
        
//         drawer->draw(*block);
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//     }
// }

int main()
{
    Drawer drawer;

    int height, width;
    drawer.get_panel_size(height, width);

    Panel panel(height, width);
    Block * block = RandomBlockFactory::create_block(0, 4);


    // thread draw_thread(draw, &drawer, &panel, block);

    // int ch;
    // // nodelay(stdscr, TRUE);
    // while (!end_program && (ch = getch()))
    // {
    //     drawer.clear(*block);
    //     switch (ch)
    //     {
    //     case 'w':
    //         block->rotate(panel);
    //         break;
    //     case 'a':
    //         block->move_left(panel);
    //         break;
    //     case 'd':
    //         block->move_right(panel);
    //         break;
    //     case 's':
    //         block->move_down(panel);
    //         break;
    //     case ' ':
    //         block->drop(panel);
    //         break;
    //     case 'q':
    //         end_program = true;
    //         break;
    //     default:
    //         block->move_down(panel);
    //         break;
    //     }
    //     drawer.draw(*block);
    //     refresh();
    // }

    // draw_thread.join();

    for (int i = 0; i < 10; i+=2)
    {
        drawer.draw(panel);
        // block = RandomBlockFactory::create_block(0, 4);
        block = new SquareBlock(9, i);
        drawer.draw(*block);
        while (true)
        {
            drawer.clear(block);
            if (!block->move_down(panel))
            {
                panel.fix_block(*block);
                drawer.draw(panel);
                delete block;
                break;
            }
            drawer.draw(*block);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    drawer.draw(panel);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    return 0;
}
