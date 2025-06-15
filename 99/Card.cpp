#include"Card.h"

Card::Card(string suit, string number){
    _suit = suit;
    _number = number;
}

Card::Card(){
    _suit = "unknown";
    _number = "unknown";
}

string Card::getNumber(){
    return _number;
}
string Card::getSuit(){
    return _suit;
}

int Card::function(){
    if(_number == "1" && _suit == "s") return 0;
    else if(_number == "1" && _suit != "s") return 1;
    else if(_number == "2") return 2;
    else if(_number == "3") return 3;
    else if(_number == "4") return 4;
    else if(_number == "5") return 5;
    else if(_number == "6") return 6;
    else if(_number == "7") return 7;
    else if(_number == "8") return 8;
    else if(_number == "9") return 9;
    else if(_number == "10") return 10;
    else if(_number == "11") return 11;
    else if(_number == "12") return 20;
    else if(_number == "13") return 99;
    return 0;
}