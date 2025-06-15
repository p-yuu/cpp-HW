#include"Show.h"

void Show::clean(){
    _number.clear();
    _suit.clear();
}

void Show::process(string cardStr){
    int i = 0;
    while(i < cardStr.size()){
        if(isalpha(cardStr[i])){
            _suit.push_back(cardStr[i]);
            i++;

            int num = 0;
            while(i < cardStr.size() && isdigit(cardStr[i])){
                num = num * 10 + (cardStr[i] - '0');
                i++;
            }
            _number.push_back(num);
        }
        else{
            i++;
        }
    }
}

void Show::call(int idt){    
    for(int l = 0; l < 13; l++){            //l: line, one loop prine one line for each card
        for(int idx = 0; idx < _suit.size(); idx++){   //loop for search every suit
            if(l == 0 || l == 9){                     //print top and bottom
                cout << " ----------------- ";
            }
            else if(l == 1 || l == 8){                //print number
                num(l, _number[idx], _suit[idx]);
            }
            else if(l == 10 || l == 11 || l == 12){
                if(idt == 1){  //don't print if it is robot(0)
                    switch(l){
                        case 10: cout << "        ___        "; break;
                        case 11: cout << "       | " << idx + 1 << " |       "; break;
                        case 12: cout << "        ---        "; break;
                    }
                }
            }
            else{                                     //print picture
                char c = _suit[idx];
                if(_number[idx] >= 11 && _number[idx] <= 13){
                    switch(_number[idx]){
                        case 11: soldier(l); break;
                        case 12: queen(l); break;
                        case 13: king(l); break;
                    }
                }                
                else{
                    switch(_suit[idx]){
                        case 's': spade(l); break;
                        case 'h': heart(l); break;
                        case 'd': diamond(l); break;
                        case 'c': club(l); break;
                    }
                }                
            }
            cout << "\t";
        }
        cout << endl;
    }
    clean();
}

void Show::num(int line, int number, char suit){
    string num;
    string s;              //save whole suit name
    switch(suit){
        case 's': s = "(spade)"; break;
        case 'h': s = "(heart)"; break;
        case 'd': s = "(diamond)"; break;
        case 'c': s = "(club)"; break;
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

    if(line == 1){
        cout << "| " << setw(16) << setiosflags(ios::left) << num << "|";
    }
    else if(line == 8){
        cout << "|" << setw(16) << setiosflags(ios::right) << num << " |";
    }

    cout << resetiosflags(ios::left | ios::right);
}

void Show::spade(int line){
    switch (line){
        case 2: cout << "|        /\\       |"; break;
        case 3: cout << "|      /    \\     |"; break;
        case 4: cout << "|    /        \\   |"; break;
        case 5: cout << "|   |          |  |"; break;
        case 6: cout << "|    `--'||`--'   |"; break;
        case 7: cout << "|        /\\       |"; break;
    }
}

void Show::heart(int line){
    switch (line){
        case 2: cout << "|       _   _     |"; break;
        case 3: cout << "|     /  \\/  \\    |"; break;
        case 4: cout << "|     \\      /    |"; break;
        case 5: cout << "|      \\    /     |"; break;
        case 6: cout << "|       \\  /      |"; break;
        case 7: cout << "|        \\/       |"; break;
    }
}

void Show::diamond(int line){
    switch (line){
        case 2: cout << "|        /\\       |"; break;
        case 3: cout << "|       /  \\      |"; break;
        case 4: cout << "|      /    \\     |"; break;
        case 5: cout << "|      \\    /     |"; break;
        case 6: cout << "|       \\  /      |"; break;
        case 7: cout << "|        \\/       |"; break;
    }
}

void Show::club(int line){
    switch (line){
        case 2: cout << "|       ___       |"; break;
        case 3: cout << "|      /   \\      |"; break;
        case 4: cout << "|    __\\   /__    |"; break;
        case 5: cout << "|   /         \\   |"; break;
        case 6: cout << "|   \\__/| |\\__/   |"; break;
        case 7: cout << "|       /_\\       |"; break;
    }
}

void Show::king(int line){
    switch (line){
        case 2: cout << "|       /\\        |"; break;
        case 3: cout << "|      |  |       |"; break;
        case 4: cout << "|      |  |       |"; break;
        case 5: cout << "|      |  |       |"; break;
        case 6: cout << "|    ,-====-'     |"; break;
        case 7: cout << "|       ||        |"; break;
    }
}

void Show::queen(int line){
    switch (line){
        case 2: cout << "|       /\\        |"; break;
        case 3: cout << "|     /\\\\//\\      |"; break;
        case 4: cout << "|     \\//\\\\/      |"; break;
        case 5: cout << "|       \\/        |"; break;
        case 6: cout << "|   *\\  ||  /*    |"; break;
        case 7: cout << "|       ||        |"; break;
    }
}

void Show::soldier(int line){
    switch (line){
        case 2: cout << "|       ___       |"; break;
        case 3: cout << "|      /   \\      |"; break;
        case 4: cout << "|      \\   /      |"; break;
        case 5: cout << "|      <   >      |"; break;
        case 6: cout << "|      /   \\      |"; break;
        case 7: cout << "|      \\___/      |"; break;
    }
};
