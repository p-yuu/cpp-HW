#ifndef CARD
#define CARD
#include<string>
using namespace std;

class Card{
private:
    string _suit;
    string _number;
public:
    Card(string, string);
    Card();
    string getNumber();
    string getSuit();
    int function();
};

#endif