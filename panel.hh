#ifndef PANEL_HH
#define PANEL_HH

#include <vector>

using std::vector;

namespace tetris
{
    class Score;
    struct Position;
    
    class Panel
    {
    public:
        Panel(int max_y, int max_x);
        void clear_full_lines(Score & rule);
        bool is_legal(const Position & pos) const;
        bool is_legal(int y, int x) const;
        int get_center_x() const;

    private:
        int max_x;
        int max_y;
        vector<vector<bool> > blocks;
    };
}

#endif
