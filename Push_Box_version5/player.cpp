#include<iostream>
#include"player.h"

Player::Player(){
    _x = _y = _dx = _dy = _row = _col = _count = 0;
}

void Player::welcome(int mode){
    int mp;
    if(mode == 1){
        string welcome = R"(
================================ Welcome to Sokoban ================================
Your job's simple: push all the boxes onto the goals to beat the level.
Just remember - you can push, but you can't pull!

"&" is you, the player
"@" is a box
"2" is a goal

Move with W, A, S, D
In "Pull Mode", you can use P + Move to pull the box
Think ahead, don't get stuck - and have fun!
)";
        cout << welcome;
        cout << "====================================================================================" << endl;
    }
    else if(mode == 2){
        cout << "================================= MODE SELECTION ===================================" << endl;
        cout << " Choose how you want to play:" << endl;
        cout << " [1] General Mode - You can only pull the box." << endl;
        cout << " [2] Pull Mode    - You have three chances to pull the box." << endl;
        cout << " Enter 1 or 2 to begin: ";   
    }
}

void Player::moveXY(){
    _x += _dx;
    _y += _dy;
}

void Player::setXY(int x, int y){
    _x = x;
    _y = y;
}

void Player::setMap(fstream& file){
    file >> _row >> _col;
    _mp = vector<vector<char>>(_row, vector<char>(_col));
    for(int row = 0; row < _row; row++){
        string temp;
        file >> temp;
        for(int col = 0; col < _col; col++){
            _mp[row][col] = temp[col];
            if(temp[col] == '0'){
                setXY(col, row);
                _mp[row][col] = '&';
            }
            else if(temp[col] == '2'){
                pair<int,int> temp(col,row);
                _end.push_back(temp);
                _finish.push_back(false);
            }
        }
    }
}

bool Player::Move(){
    if(_x + _dx < 0 || _x + _dx >= _col || _y + _dy < 0 || _y + _dy >= _row) return false;
    if(_mp[_y + _dy][_x + _dx] != '/') return true;
    return false;
}

bool Player::moveMap(){
    string move;
    printMap();

    cout << "Which way do you want to move (WSAD): ";
    cin >> move;
    cout << endl;

    bool pull = false;
    if(move.length() == 2 && (move[0] == 'p' || move[0] == 'P')){
        pull = true;
        move[0] = move[1];
    }

    switch(move[0]){
        case 'W': case 'w': _dx = 0, _dy = -1; break;
        case 'S': case 's': _dx = 0, _dy = 1; break;
        case 'D': case 'd': _dx = 1, _dy = 0; break;
        case 'A': case 'a': _dx = -1, _dy = 0; break;
        default: _dx = 0, _dy = 0; break;
    }
    return pull;
}

void Player::printMap(){
    cout << "You've moved " << _count << " times." << endl;

    bool all_true = true;
    for(int i = 0; i < _end.size(); i++){
        if(_finish[i] == false){
            all_true = false;
            break;
        }
    }
    if(all_true){
        for(int i = 0; i < _end.size(); i++){
            _mp[_end[i].second][_end[i].first] = '@';
        }
    }

    for(int row = 0; row < _row; row++){
        for(int col = 0; col < _col; col++){
            cout << _mp[row][col];
        }
        cout << endl;
    }
    cout << endl;
}