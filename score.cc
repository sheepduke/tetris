#include "score.hh"

namespace tetris
{
    Score::Score()
    {
        score = 0;
    }

    int Score::current_score() const
    {
        return score;
    }

    void Score::handle_full_lines(int number_of_lines)
    {
        score += (10 + 5 * (number_of_lines - 1)) * number_of_lines;
    }
}
