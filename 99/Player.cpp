#include"Player.h"

Player::Player(){
    _name = "anonymous";
    _id = 0;
    _cardPoint = 0;
    _totalPoint = 0;
    _status = 0;
    _inGame = 1;
}

void Player::clearPoint(){
    _cardPoint = 0;
    _inGame = 1;
}

void Player::clearCard(int idx){    //輸入要刪除元素，或是輸入-1刪除所有元素
    if(idx == -1) _card.clear();
    else _card.erase(_card.begin() + idx);
}

void Player::setStatus(bool status, string name){
    if(name == "0")
        name = "anonymous";
    _status = status;
    _name = name;
}

void Player::setID(int id){
    _id = id;
}

void Player::setInGame(bool inGame){
    _inGame = inGame;
}

int Player::getCP(){
    return _cardPoint;
}

int Player::getTP(){
    return _totalPoint;
}

void Player::addCard(vector<Card> card){
    _card.insert(_card.end(), card.begin(), card.end());
}

int Player::getCardSize(){
    return _card.size();
}

string Player::getName(){
    return _name;
}

void Player::addTotal(int point){
    _totalPoint += point;
}

void Player::addPoint(int point, int add){
    if(add == 1){
        if(point == 0){
            _cardPoint = 0;
        }
        else if(point == 99){
            _cardPoint = 99;
        }
        else{
            _cardPoint += point;
        }
    }
    else{
        _cardPoint -= point;
        if(_cardPoint < 0) _cardPoint = 0;
    }
}

string Player::getCardStr(){
    string s;
    for(int idx = 0; idx < _card.size(); idx++){
        s += _card[idx].getSuit() + _card[idx].getNumber() + ' ';
    }
    return s;
}

Card Player::getCard(int idx){
    return _card[idx];
}

bool Player::getStatus(){
    return _status;
}

int Player::getID(){
    return _id;
}

bool Player::getInGame(){
    return _inGame;
}