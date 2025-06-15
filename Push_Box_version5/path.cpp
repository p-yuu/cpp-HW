#include"path.h"


Path::Path(){
    _playerX = 0;
    _playerY = 0;
    _endpointX = 0;
    _endpointY = 0;
    _arrive = false;
}

Path::Path(int px, int py, int ex, int ey, int row, int col, vector<vector<char>> &mp){
    _copyMp = mp;
    _row = row;
    _col = col;
    _playerX = px;
    _playerY = py;
    _endpointX = ex;
    _endpointY = ey;
    _arrive = false;
}

void Path::robot(int x, int y){
    if(x < 0 || x >= _col || y < 0 || y >= _row) return;
    if(_copyMp[y][x] == '*' || _copyMp[y][x] == '/' || _copyMp[y][x] == '@') return;
    if(_arrive) return;

    if(x == _endpointX && y == _endpointY){
        _arrive = true;
        return;
    }

    _copyMp[y][x] = '*';

    robot(x, y - 1); 
    robot(x + 1, y); 
    robot(x, y + 1); 
    robot(x - 1, y);
}

bool Path::getArrive(){
    robot(_playerX, _playerY);
    return _arrive;
}