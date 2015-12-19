#ifndef SCORE_RULE_HH
#define SCORE_RULE_HH

namespace tetris
{
    class Score
    {
    public:
        Score();
        int current_score() const;
        void handle_full_lines(int number_of_lines);

    private:
        int score;
    };
}

#endif
