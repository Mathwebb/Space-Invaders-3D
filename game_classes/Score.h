#ifndef SCORE_H
#define SCORE_H

class Score{
    private:
        int score;
    public:
        Score(){
            this->score = 0;
        }

        int getScore(){
            return this->score;
        }

        void setScore(int score){
            this->score = score;
        }

        void addScore(int score){
            this->score += score;
        }
};

#endif