#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<random>
#include<ctime>
#include"class.h"
#include"function.cpp"
using namespace std;

int main(int argc, char** argv){    
    char go = 'y';

    welcome();

    while(go == 'y' || go == 'Y'){
        poker pok;
        vector<string> enter;
        string str;

        cout << "Enter: ";

        while(str != "*"){                     //enter and process vector
            cin >> str;
            this_thread::sleep_for(chrono::milliseconds(500));
            int surprise = pok.Random(8);
            if(surprise != 1){
                if(str != "R" && str != "r")
                    enter.push_back(str);
                else{
                    char s;
                    int rs = pok.Random(5);
                    int rn = pok.Random(13);
                    if(rs == 1) s = 'S';
                    else if(rs == 2) s = 'H';
                    else if(rs == 3) s = 'D';
                    else if(rs == 4) s = 'C';
                    else if(rs == 5) s = 'K';
                    string S = s + to_string(rn);
                    enter.push_back(S);
                }
            }
            else{
                enter.push_back("W0");
            }
        }
        enter.pop_back();
        pok.process(enter);

        pok.call();

        cout << "\n" << "Do you want to execute the program again? (enter 'y' for yes, 'n' for no): ";
        cin >> go;
        cout << endl;
        pok.clean();
    }
    
    return 0;
}