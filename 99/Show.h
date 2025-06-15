#ifndef SHOW
#define SHOW
#include<vector>
#include<iostream>
#include<iomanip>
#include<cctype>
#include<string>
#include<cstdlib>
using namespace std;

class Show{
    private:
    vector<int> _number;
    vector<char> _suit;
    void num(int, int, char);
    void spade(int);
    void heart(int);
    void diamond(int);
    void club(int);
    void king(int);
    void queen(int);
    void soldier(int);
public:
    void process(string);
    void call(int);
    void clean();
};

#endif