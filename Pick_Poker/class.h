#ifndef POKER_H
#define POKER_H
#include<string>
#include<vector>
using namespace std;

class poker{
    private:
        vector<int> number;
        vector<char> suit;
        void num(int, int, char);
        void spade(int);
        void heart(int);
        void diamond(int);
        void club(int);
        void joker(int);
        void king(int);
        void queen(int);
        void soldier(int);
        void jump(int);
    public:
        void process(const vector<string>&);
        void call();
        int Random(int);
        void clean();
};

#endif