#include"Deck.h"

void Deck::setDeck(){
    string suits[] = {"s", "h", "d", "c"};
    string numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"};
    for(int suit = 0; suit < 4; suit++){
        for(int num = 0; num < 13; num++){
            _deck.push_back(Card(suits[suit],numbers[num]));
        }
    }
}

void Deck::Shuffle(){
    random_device rd;
    mt19937 g(rd());
    shuffle(_deck.begin(), _deck.end(), g);
}

vector<Card> Deck::deelCard(int num){
    if(_deck.size() >= num){
        vector<Card> c;
        for(int number = 0; number < num; number++){
            c.push_back(_deck.back());
            _deck.pop_back();
        }
        return c;
    }

    throw runtime_error("No more card");
}

int Deck::deckSize(){
    return _deck.size();
}