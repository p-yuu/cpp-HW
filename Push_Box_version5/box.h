#ifndef BOX_H
#define BOX_H
#include"player.cpp"
#include"path.cpp"

class Box: public Player{
protected:
    int _temp_box_x;
    int _temp_box_y;
    int _idx;
    vector<pair<int,int>> _box;
public:
    Box();
    void setBox();
    void moveBox(int);
    void Pull();
    void Move_Box_XY();
    bool Can_Move_box();
    bool Judge(int,int);
};

#endif