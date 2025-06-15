#ifndef PLAYER
#define PLAYER
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<thread>
#include<chrono>
using namespace std;

class Player{
private:
    vector<vector<char>> _mp;
    int _x;
    int _y;
    int _endX;
    int _endY;
    int _row;
    int _col;
    int _count;
    void setXY(int, int);
    void setEnd(int, int);
    bool Move(int, int);
    void moveXY(int, int);
    void moveMap(int);
    void robot(int, int);
    void explode(char);
    void printMap();
public:
    Player();
    void welcome(int, int);
    void setMap(fstream&, int);
};

#endif