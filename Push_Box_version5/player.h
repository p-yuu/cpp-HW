#ifndef PLAYER
#define PLAYER
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

class Player{
protected:
    vector<vector<char>> _mp;
    vector<pair<int,int>> _end;
    vector<bool> _finish;
    int _x;
    int _y;
    int _dx;
    int _dy;
    int _row;
    int _col;
    int _count; // how many steps
    void setXY(int, int);
    bool Move();
    void moveXY();
    bool moveMap();
    void printMap();
public:
    Player();
    void welcome(int);
    void setMap(fstream&);
};

#endif