#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char** argv){
    string line;
    fstream file(argv[1], ios::in);
    if(!file){
        cout << "error" << endl;
        return 0;
    }
    while (getline(file, line)) {
        cout << line << endl;  // 輸出每一行
    }
    file.close();
    return 0;
}