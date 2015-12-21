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
    Panel panel(20, 10);
    Drawer drawer(20, 10);
    Block * block = RandomBlockFactory::create_block(0, 0);


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
    drawer.draw(panel);

    drawer.draw(*block);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    drawer.clear(block);
    block->move_down(panel);
    drawer.draw(*block);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return 0;
}
