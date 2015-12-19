#include "drawer.hh"
#include "panel.hh"
#include "block.hh"
#include <ncurses.h>

using namespace std;
using namespace tetris;

int main()
{
    Drawer drawer;
    Panel panel(15, 20);
    Block * block = new StickBlock(4, 4);

    drawer.draw(*block);    
    refresh();

    int ch;
    while ((ch = getch()) != 'q')
    {
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
            block->drop(panel);
        }
        drawer.draw(*block);
    }
    
    refresh();
    
    return 0;
}
