#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cctype>
#include<random>
#include<ctime>
#include<chrono>
#include<thread>
#include"class.h"

void welcome(){
    cout << "\nPlease enter the suit and number you want." << endl;
    cout << "You can enter more than one card at a time." << endl;
    cout << "Enter \"*\" as you finish.";
    cout << "(If you choose \"random\", please don't enter a number.)"<< endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "| Suit:                                                   |" << endl;
    cout << "|    S: spade   H: heart   D:diamond   C:club   R: random |" << endl;
    cout << "| Number:                                                 |" << endl;
    cout << "|    1 ~ 13                                               |" << endl;
    cout << "| (example: H2 D11 R *)                                   |" << endl;
    cout << "-----------------------------------------------------------" << endl;
}

void poker::clean(){
    number.clear();
    suit.clear();
}

void poker::process(const vector<string>& list){
    for(const auto& str: list){
        string number_part;
        string suit_part;

        for(char ch: str){
            if(isalpha(ch)){
                suit_part += ch;
            }
            else if(isdigit(ch)){
                number_part += ch;
            }
        }
    
        suit.push_back(suit_part[0]);
        number.push_back(stoi(number_part));
    }

}

int poker::Random(int num){
    srand(time(NULL));
    return 1 + rand() % (num); 
}

void poker::call(){    
    for(int l = 0; l < 10; l++){            //l: line, one loop prine one line for each card
        for(int idx = 0; idx < suit.size(); idx++){   //loop for search every suit
            if(l == 0 || l == 9){                     //print top and bottom
                cout << " ----------------- ";
            }
            else if(l == 1 || l == 8){                //print number
                if(suit[idx] == 'W')
                    jump(l);
                else
                    num(l, number[idx], suit[idx]);
            }
            else{                                     //print picture
                char c = suit[idx];
                if(!(c == 'S' || c == 's' || c == 'H' || c == 'h' || c == 'D' || c == 'd' || c == 'C' || c == 'c' || c == 'W')){
                    joker(l);
                }
                else if(c == 'W'){
                    jump(l);
                }
                else{
                    if(number[idx] > 13 || number[idx] < 1){
                        joker(l);
                    }
                    else if(number[idx] >= 11 && number[idx] <= 13){
                        switch(number[idx]){
                            case 11: soldier(l); break;
                            case 12: queen(l); break;
                            case 13: king(l); break;
                        }
                    }                
                    else{
                        switch(suit[idx]){
                            case 'S': case 's': spade(l); break;
                            case 'H': case 'h': heart(l); break;
                            case 'D': case 'd': diamond(l); break;
                            case 'C': case 'c': club(l); break;
                            default: joker(l); break;
                        }
                    }
                }
            }

            cout << "\t";
        }
        cout << endl;
    }
}

void poker::num(int line, int number, char suit){
    string num;
    string s;              //save whole suit name
    switch(suit){
        case 'S': case 's': s = "(spade)"; break;
        case 'H': case 'h': s = "(heart)"; break;
        case 'D': case 'd': s = "(diamond)"; break;
        case 'C': case 'c': s = "(club)"; break;
        default: s = ""; break;
    }
    if(number <= 13 && number >= 1 && s != ""){
        switch(number){
            case 11: num = "J" + s; break;
            case 12: num = "Q" + s; break;
            case 13: num = "K" + s; break; 
            default: num = to_string(number);
        }
    }
    else{
        num = "JOKER";
    }

    if(line == 1){
        cout << "| " << setw(16) << setiosflags(ios::left) << num << "|";
    }
    else if(line == 8){
        cout << "|" << setw(16) << setiosflags(ios::right) << num << " |";
    }

    cout << resetiosflags(ios::left | ios::right);
}

void poker::spade(int line){
    switch (line){
        case 2: cout << "|        /\\       |"; break;
        case 3: cout << "|      /    \\     |"; break;
        case 4: cout << "|    /        \\   |"; break;
        case 5: cout << "|   |          |  |"; break;
        case 6: cout << "|    `--'||`--'   |"; break;
        case 7: cout << "|        /\\       |"; break;
    }
}

void poker::heart(int line){
    switch (line){
        case 2: cout << "|       _   _     |"; break;
        case 3: cout << "|     /  \\/  \\    |"; break;
        case 4: cout << "|     \\      /    |"; break;
        case 5: cout << "|      \\    /     |"; break;
        case 6: cout << "|       \\  /      |"; break;
        case 7: cout << "|        \\/       |"; break;
    }
}

void poker::diamond(int line){
    switch (line){
        case 2: cout << "|        /\\       |"; break;
        case 3: cout << "|       /  \\      |"; break;
        case 4: cout << "|      /    \\     |"; break;
        case 5: cout << "|      \\    /     |"; break;
        case 6: cout << "|       \\  /      |"; break;
        case 7: cout << "|        \\/       |"; break;
    }
}

void poker::club(int line){
    switch (line){
        case 2: cout << "|       ___       |"; break;
        case 3: cout << "|      /   \\      |"; break;
        case 4: cout << "|    __\\   /__    |"; break;
        case 5: cout << "|   /         \\   |"; break;
        case 6: cout << "|   \\__/| |\\__/   |"; break;
        case 7: cout << "|       /_\\       |"; break;
    }
}

void poker::joker(int line){
    switch (line){
        case 2: cout << "|    / _\\_/_ \\    |"; break;
        case 3: cout << "|   / /_____\\ \\   |"; break;
        case 4: cout << "|  | | +   + | |  |"; break;
        case 5: cout << "|  0 |   O   | 0  |"; break;
        case 6: cout << "|    |'\\__/` |    |"; break;
        case 7: cout << "|    `-------'    |"; break;
    }
}

void poker::king(int line){
    switch (line){
        case 2: cout << "|       /\\        |"; break;
        case 3: cout << "|      |  |       |"; break;
        case 4: cout << "|      |  |       |"; break;
        case 5: cout << "|      |  |       |"; break;
        case 6: cout << "|    ,-====-'     |"; break;
        case 7: cout << "|       ||        |"; break;
    }
}

void poker::queen(int line){
    switch (line){
        case 2: cout << "|       /\\        |"; break;
        case 3: cout << "|     /\\\\//\\      |"; break;
        case 4: cout << "|     \\//\\\\/      |"; break;
        case 5: cout << "|       \\/        |"; break;
        case 6: cout << "|   *\\  ||  /*    |"; break;
        case 7: cout << "|       ||        |"; break;
    }
}

void poker::soldier(int line){
    switch (line){
        case 2: cout << "|       ___       |"; break;
        case 3: cout << "|      /   \\      |"; break;
        case 4: cout << "|      \\   /      |"; break;
        case 5: cout << "|      <   >      |"; break;
        case 6: cout << "|      /   \\      |"; break;
        case 7: cout << "|      \\___/      |"; break;
    }
};

void poker::jump(int line){
    switch (line){
        case 1: cout << "|______           |"; break;
        case 2: cout << "| ] [] |   \\ O /  |"; break;
        case 3: cout << "| ] [] |    /     |"; break;
        case 4: cout << "| ] [] |   ))     |"; break;
        case 5: cout << "| ] [] |          |"; break;
        case 6: cout << "| ] [] |          |"; break;
        case 7: cout << "|  calm down !!!  |"; break;
        case 8: cout << "| ] [] |          |"; break;
    }
}
