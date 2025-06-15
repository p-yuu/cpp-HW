#ifndef PATH_H
#define PATH_H
#include"player.h"

class Path{
protected:
    vector<vector<char>> _copyMp;
    int _row;
    int _col;
    int _playerX;
    int _playerY;
    int _endpointX;
    int _endpointY;
    bool _arrive;
public:
    Path();
    Path(int,int,int,int,int,int, vector<vector<char>>&);
    void robot(int,int);
    bool getArrive();
};

#endif