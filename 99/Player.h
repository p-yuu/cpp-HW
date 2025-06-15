#ifndef PLAYER
#define PLAYER
#include"main.h"

class Player{
private:
    string _name;
    int _id;
    vector<Card> _card;
    int _cardPoint;
    int _totalPoint;
    bool _status;            //0 for robot, 1 for player
    bool _inGame;
public:
    Player();
    void clearPoint();
    void clearCard(int);
    void setStatus(bool, string);
    void setID(int);
    void setInGame(bool);
    int getCP();
    int getTP();
    int getID();
    string getName();
    bool getStatus();
    bool getInGame();
    Card getCard(int);
    int getCardSize();
    string getCardStr();
    void addCard(vector<Card>);
    void addTotal(int);
    void addPoint(int, int);
};

#endif