#include"box.h"

Box::Box(): Player(), _temp_box_x(0), _temp_box_y(0), _idx(0) {}

void Box::setBox(){
    for(int row = 0; row < _row; row++){
        for(int col = 0; col < _col; col++){
            if(_mp[row][col] == '1'){
                _mp[row][col] = '@';
                pair<int,int> temp(col,row);
                _box.push_back(temp);
            }
        }
    }
}

void Box::moveBox(int mode){
    int pull_times;
    bool stuck = false; 

    if(mode == 2) pull_times = 3;
    else pull_times = 0;

    while(_box.size() != 0){
        if(mode == 2) cout << "You can pull the box " << pull_times << " more times. (P + Move)" << endl;

        for(int test = 0; test < _box.size(); test++){
            if(!Judge(_box[test].first, _box[test].second)){
                stuck = true;
                break;
            }
        }
        if(stuck && pull_times == 0){
            stuck = true;
            break;
        }

        bool pull = moveMap();
        int dx = _x + _dx;
        int dy = _y + _dy;

        _temp_box_x = -2;
        _temp_box_y = -2;
        _idx = -2;
        for(int item = 0; item < _box.size(); item++){
            if(dx == _box[item].first && dy == _box[item].second){
                _temp_box_x = dx;
                _temp_box_y = dy;
                _idx = item;
            }
        }

        if(pull && mode == 2 && pull_times != 0){
            pull_times--;
            Pull();
        }
        else if(pull && mode == 2 && pull_times <= 0){
            cout << "-------------------------------" << endl;
            cout << " You can't pull anymore." << endl;
            cout << "-------------------------------" << endl;
        }
        else{
            if(dx == _temp_box_x && dy == _temp_box_y){
                if(Can_Move_box()){
                    _mp[_temp_box_y][_temp_box_x] = '&';
                    _mp[_y][_x] = '-';
                    for(int item = 0; item < _end.size(); item++){
                        if(_finish[item] == false) _mp[_end[item].second][_end[item].first] = '2';
                    }

                    Move_Box_XY();
                    moveXY();
                    _mp[_box[_idx].second][_box[_idx].first] = '@';

                    for(int item = 0; item < _end.size(); item++){
                        if(_end[item].first == _temp_box_x && _end[item].second == _temp_box_y && _finish[item] == false){
                            _finish[item] = true;
                            _mp[_temp_box_y][_temp_box_x] = '-';
                            _box.erase(_box.begin() + _idx);
                            break;
                        }
                    }
                }
                else{
                    cout << "--------------------------------------" << endl;
                    cout << " There's a wall. Try another direction." << endl;
                    cout << "--------------------------------------" << endl;
                }
            }
            else{
                if(Move()){
                    _mp[_y][_x] = '-';
                    for(int item = 0; item < _end.size(); item++){
                        if(_finish[item] == false) _mp[_end[item].second][_end[item].first] = '2';
                    }
                    moveXY();
                    _mp[_y][_x] = '&';
                }
                else{
                    cout << "--------------------------------------" << endl;
                    cout << " That's a wall. Try another direction." << endl;
                    cout << "--------------------------------------" << endl;
                }
            }
        }
        _count++;
    }
    printMap();
    if(stuck){
        cout << "--------------------------------------" << endl;
        cout << " Game over, you can't move anymore." << endl;
        cout << "--------------------------------------" << endl;
    }
    else{
        cout << "-------------------------------------------" << endl;
        cout << " Congratulations! You've reached the exit." << endl;
        cout << " Total steps taken: " << _count << "." << endl;
        cout << "-------------------------------------------" << endl;
    }
    system("PAUSE");
}

void Box::Pull(){
    int box_dx = -2, box_dy = -2;

    /*int dx = _x + _dx;
    int dy = _y + _dy;*/

    _temp_box_x = -2;
    _temp_box_y = -2;
    _idx = -2;
    for(int item = 0; item < _box.size(); item++){
        if(_box[item].first + _dx == _x && _box[item].second + _dy == _y){
            _temp_box_x = _box[item].first;
            _temp_box_y = _box[item].second;
            box_dx = _box[item].first + _dx;
            box_dy = _box[item].second + _dy;
            _idx = item;
        }
    }

    if(Move()){
        if(box_dx == _x && box_dy == _y){
            _mp[_y][_x] = '@';
            _mp[_temp_box_y][_temp_box_x] = '-';
            for(int item = 0; item < _end.size(); item++){
                if(_finish[item] == false) _mp[_end[item].second][_end[item].first] = '2';
            }

            Move_Box_XY();
            moveXY();
            _mp[_y][_x] = '&';

            for(int item = 0; item < _end.size(); item++){
                if(_end[item].first == _temp_box_x && _end[item].second == _temp_box_y && _finish[item] == false){
                    _finish[item] = true;
                    _mp[_temp_box_y][_temp_box_x] = '-';
                    _box.erase(_box.begin() + _idx);
                    break;
                }
            }
        }
        else{
            _mp[_y][_x] = '-';
            for(int item = 0; item < _end.size(); item++){
                if(_finish[item] == false) _mp[_end[item].second][_end[item].first] = '2';
            }
            moveXY();
            _mp[_y][_x] = '&';
        }
    }
    else{
        cout << "--------------------------------------" << endl;
        cout << " There's a wall. Try another direction." << endl;
        cout << "--------------------------------------" << endl;
    }
}

void Box::Move_Box_XY(){
    _box[_idx].first += _dx;
    _box[_idx].second += _dy;
    _temp_box_x += _dx;
    _temp_box_y += _dy;
}

bool Box::Can_Move_box(){
    int dx = _temp_box_x + _dx;
    int dy = _temp_box_y + _dy;
    if(dx < 0 && dx >= _col && dy < 0 && dy >= _row) return false;
    if(_mp[dy][dx] == '/' || _mp[dy][dx] == '@') return false;
    return true;
}

bool Box::Judge(int _box_x, int _box_y){
    int dx[4] = {0,1,0,-1};
    int dy[4] = {-1,0,1,0};

    vector<int> wall;
    int person = -1;
    for(int i = 0; i < 4; i++){
        int box_tempX = _box_x + dx[i];
        int box_tempY = _box_y + dy[i];

        if(box_tempX < 0 && box_tempX >= _col && box_tempY < 0 && box_tempY >= _row){
            wall.push_back(i);
        }
        else if(_mp[box_tempY][box_tempX] == '/'){
            wall.push_back(i);
        }
        else if(_mp[box_tempY][box_tempX] == '&'){
            person = i;
        }
    }

    if(wall.size() == 3) return false;
    else if(wall.size() == 2){
        if(abs(wall[0] - wall[1]) == 1 || abs(wall[0] - wall[1]) == 3) return false;
    }
    else if(wall.size() == 1 && person != -1){
        if(abs(person - wall[0]) == 2){
            int idx[2], j = 0;
            for(int i = 0; i < 4; i++){
                if(i != person && i != wall[0]){
                    idx[j] = i;
                    j++;
                }
            }
            int p1x = _box_x + dx[idx[0]], p1y = _box_y + dy[idx[0]];
            int p2x = _box_x + dx[idx[1]], p2y = _box_y + dy[idx[1]];

            Path p1(_x, _y, p1x, p1y, _row, _col, _mp);
            Path p2(_x, _y, p2x, p2y, _row, _col, _mp);
            if(!(p1.getArrive() || p2.getArrive())) return false;
        }
    }

    return true;
}