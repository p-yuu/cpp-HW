#include<iostream>
#include"player.h"

Player::Player(){
    _x = _y = _row = _col = _count = 0;
}

void Player::welcome(int argc, int mode){
    int mp;
    if(mode == 1){
        string welcome = R"(
====================================================================================
 Welcome to the maze. 
 Your goal is simple: navigate through the twists and turns to find the exit.
 "&" is your character, "1" is the end.
 Use the "W,S,A,D" keys to move your character.
 Good luck!
)";
        cout << welcome;
    }
    else if(mode == 2){
        cout << "================================= MAP SELECTION ====================================" << endl;
        cout << " Here are " << argc - 1 << " maps, choose one you like." << endl;
        cout << " Enter 1 ~ " << argc - 1 << ": " ;
    }
    else if(mode == 3){
        cout << "================================= MODE SELECTION ===================================" << endl;
        cout << " Choose how you want to play:" << endl;
        cout << " [1] Manual Mode - Control the player yourself using W, A, S, D keys." << endl;
        cout << " [2] Auto Mode   - Let the robot solve the maze for you." << endl;
        cout << " [3] Bomb Mode   - You have 5 bombs to blast through walls and create your own path!" << endl;
        cout << " Enter 1 ~ 3 to begin: ";       
    }
}

void Player::moveXY(int dx, int dy){
    _x += dx;
    _y += dy;
}

void Player::setXY(int x, int y){
    _x = x;
    _y = y;
}

void Player::setEnd(int x, int y){
    _endX = x;
    _endY = y;
}

void Player::setMap(fstream& file, int mode){
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
            else if(temp[col] == '1') setEnd(col, row);
        }
    }
    if(mode == 1) moveMap(1);
    else if(mode == 2) robot(_x, _y);
    else if(mode == 3) moveMap(3);
}

bool Player::Move(int dx, int dy){
    if(_x + dx < 0 || _x + dx >= _col || _y + dy < 0 || _y + dy >= _row) return false;
    if(_mp[_y + dy][_x + dx] != '/') return true;
    return false;
}

void Player::moveMap(int mode){
    string move;
    int bomb = 5;
    printMap();
    while(!(_x == _endX && _y == _endY)){
        int dx = 0, dy = 0;
        if(mode == 3){
            cout << "You still have " << bomb << " bombs left." << endl;
            cout << "If you want to use it, enter 'E' + 'WSAD'." << endl;
        }
        cout << "Which way do you want to move (WSAD): ";
        cin >> move;
        cout << endl;
        switch(move[0]){
            case 'W': case 'w': dx = 0, dy = -1; break;
            case 'S': case 's': dx = 0, dy = 1; break;
            case 'D': case 'd': dx = 1, dy = 0; break;
            case 'A': case 'a': dx = -1, dy = 0; break;
            case 'E': case 'e': {
                bomb--;
                if(bomb) explode(move[1]);
                else{                    
                    cout << "-------------------------------" << endl;
                    cout << " You don't have bomb any more." << endl;
                    cout << "-------------------------------" << endl;
                }
                break;
            }
            default: dx = 0, dy = 0; break;
        }
        if(Move(dx, dy)){
            _mp[_y][_x] = '*';
            moveXY(dx, dy);
            _mp[_y][_x] = '&';
        }
        else{
            cout << "--------------------------------------" << endl;
            cout << " That's a wall. Try another direction." << endl;
            cout << "--------------------------------------" << endl;
        }
        if(!(move[0] == 'E'|| move[0] == 'e')) _count++;
        printMap();
    }
    cout << "-------------------------------------------" << endl;
    cout << " Congratulations! You've reached the exit." << endl;
    cout << " Total steps taken: " << _count << "." << endl;
    cout << "-------------------------------------------" << endl;
    system("PAUSE");
}

void Player::printMap(){
    cout << "You've moved " << _count << " times." << endl;
    for(int row = 0; row < _row; row++){
        for(int col = 0; col < _col; col++){
            cout << _mp[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

void Player::robot(int x, int y){
    if(x == _endX && y == _endY){
        _count++;
        _mp[_y][_x] = '*';
        _mp[y][x] = '&';
        printMap();
        cout << "-------------------------------------------" << endl;
        cout << " Congratulations! You've reached the exit." << endl;
        cout << " Total steps taken: " << _count << "." << endl;
        cout << "-------------------------------------------" << endl;
        system("PAUSE");
        exit(0);
    }
    if(x < 0 || x >= _col || y < 0 || y >= _row) return;
    if(_mp[y][x] == '*' || _mp[y][x] == '/') return;
    
    _mp[_y][_x] = '*';
    _x = x;
    _y = y;
    _mp[_y][_x] = '&';
    _count++;
    printMap();
    this_thread::sleep_for(chrono::milliseconds(200));

    robot(x, y - 1);
    robot(x + 1, y);
    robot(x, y + 1);
    robot(x - 1, y);
    
    _mp[y][x] = '-';
}

void Player::explode(char wall){
    int dx = 0, dy = 0;
    switch(wall){
        case 'W': case 'w': dx = 0, dy = -1; break;
        case 'S': case 's': dx = 0, dy = 1; break;
        case 'D': case 'd': dx = 1, dy = 0; break;
        case 'A': case 'a': dx = -1, dy = 0; break;
        default: break;
    }
    if(_x + dx >= 0 && _x + dx < _col && _y + dy >=0 && _y + dy < _row)
        _mp[_y + dy][_x + dx] = '-';
    else
        cout << "No walls can blast." << endl;
}