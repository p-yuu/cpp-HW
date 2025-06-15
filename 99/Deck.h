#ifndef DECK
#define DECK
#include"main.h"

class Deck{
private:
    vector<Card> _deck;
public:
    void setDeck();
    void Shuffle();
    vector<Card> deelCard(int);
    int deckSize();
};

#endif