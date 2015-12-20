#ifndef PANEL_HH
#define PANEL_HH

#include <vector>

using std::vector;

namespace tetris
{
    struct Position;
    
    class Panel
    {
    public:
        Panel(int height, int width);
        void clear_full_lines();

        // Check if `pos' or position (y, x) is a legal point
        // that can hold a single point.
        bool is_legal(const Position & pos) const;
        bool is_legal(int y, int x) const;

        int height() const;
        int width() const;

    private:
        int m_height;
        int m_width;
        vector<vector<bool> > blocks;
        int score;
    };
}

#endif
