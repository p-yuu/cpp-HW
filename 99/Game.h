#ifndef GAME
#define GAME
#include<vector>
#include"Player.cpp"
#include"Deck.cpp"
#include"Show.cpp"

class Game : public Show{
private:
    int _member;
    int _round;
    vector<Player> _player;
    Deck _deck;
public:
    void Welcome();
    void Intruction();
    void finish();
    void Start();
    void setPlayerID(int);
    void setPlayer(int);
    void showRound(int);
    int human(Player&, int);
    int robot(Player&, int);
    int judgeOver(Player&, int&, int&);
    void judgeWin(Player&, int&, int&);
    void judgeLose(Player&, int&, int&);
};

#endif