#include"main.h"
#include"Game.h"
using namespace std;

void Game::Welcome(){
    string wlc = R"(
=============================================================
Welcome to 99 points!!!

Are you ready to use your wits and luck to conquer the game? 
Start your challenge and enjoy every thrilling moment! 
=============================================================
1. Instruction
2. Start the game
(choose what you want, 1 or 2): )";
    cout << wlc;

    int ipt;
    while((cin >> ipt) && ipt != 2){
        if(ipt == 1) {
            Intruction();
            cout << " 1. Instruction\n" << " 2. Start the game\n" << " (choose what you want, 1 or 2): ";
        }
        else cout << "No this choice. Choose 1 or 2: ";
    }
    Start();
}

void Game::Intruction(){
    string itr = R"(
=============================================================
1. Set how many rounds you want to play. 
2. Set how many players you want (2 ~ 5), robots will play 
   with you.
3. Every player will have 5 cards
4. Once you play all the cards in your hand and your points 
   are less than 99, you will become the winner this round.
5. After each round, you will get some points. You will become 
   the finial winner if you have the most points.
#Special cards:
   - 4: reverse (when players more than 4)
   - 5: choose a player to play
   - 10: add 10 or subtract 10
   - J: skip this round
   - Q: add 20 or subtract 20
   - K: add points to 99
=============================================================)";
    cout << itr << endl;
}

void Game::finish(){
    sort(_player.begin(), _player.end(), [](Player& p1, Player& p2){
        return p1.getTP() > p2.getTP();
    });
    int place = 1;
    cout << "\n====================================================================" << endl;
    cout << " That's the game! Congrats to the winner, and well played everyone!" << endl;
    cout << " Here are the final rankings " << endl;
    cout << " See you next time ~" << endl;
    cout << "====================================================================" << endl;
    for(int mem = 0; mem < _member; mem++){
        cout << " ___ " << endl;
        cout << "| " << place << " | " << _player[mem].getName() << "   Points: " << _player[mem].getTP() << endl;
        cout << " --- " << endl;
        if(mem != _member - 1 && _player[mem].getTP() != _player[mem + 1].getTP()){
            place++;
        }
    }
}

void Game::showRound(int round){
    cout << '\n' << round << " round! Order of this round: ";
    for(int mem = 0; mem < _member; mem++){
        if(mem != 0) cout << " -> ";
        cout << _player[mem].getName();
    }
    cout << '\n' << endl;
}

void Game::Start(){
    int member, round;
    cout << "How many players in total (2 to 5, including you): ";
    while(cin >> member && member > 5 || member < 2){
        cout << "Enter 2 to 5: ";
    }
    cout << "How many rounds do you want to play: ";
    cin >> round;
    _member = member;
    _round = round;
    _deck.setDeck();
    _deck.Shuffle();


    setPlayer(_member);
    while(_round--){
        cout << "round: " << _round << endl;
        int round = 1;
        int Fplace = 0, Lplace = 0;         //結束遊戲人數
        setPlayerID(_member);  //抽遊戲順序
        for(int mem = 0; mem < _member; mem++){   //原本的一張 + 新的四張
            _player[mem].addCard(_deck.deelCard(4));
        }
        showRound(round);

        int member = 0, way = 1;   //way: 遊戲方向(1:順時針、0:逆時針)
        while(1){                      //play

            cout << "Deck Size: " << _deck.deckSize() << endl;

            int flag = 0;   //judge card 5 or not
            if(_player[member].getInGame() == 1){
                if(_player[member].getStatus()){
                    cout << "Your turn! You have " << _player[member].getCP() << " points now" << endl;
                    int op = human(_player[member], member);
                    if(op == -2){
                        if(way == 1) way = 0;
                        else if(way == 0) way = 1;
                    }
                    else if(op != -1 && op != -2){
                        if(_deck.deckSize() > 0)
                            _player[member].addCard(_deck.deelCard(1));
                        cout <<"You choose " << _player[op].getName() << " to be the next\n" << endl;
                        member = op;
                        flag = 1;
                    }
                }
                else{
                    cout << _player[member].getName() << "'s turn! " << _player[member].getName() 
                        << " have " << _player[member].getCP() << " points now" << endl;
                    int op = robot(_player[member], member);
                    if(op == -2){
                        if(way == 1) way = 0;
                        else if(way == 0) way = 1;
                    }
                    else if(op != -1 && op != -2){
                        if(_deck.deckSize() > 0)
                            _player[member].addCard(_deck.deelCard(1));
                        cout << _player[member].getName() << " choose " << _player[op].getName() << " to be the next\n" << endl;
                        member = op;
                        flag = 1;
                    }
                }
                
            judgeWin(_player[member], Fplace, Lplace);
            judgeLose(_player[member], Fplace, Lplace);
            }
            if(judgeOver(_player[member], Fplace, Lplace) == 0)
                break;


            if(_deck.deckSize() > 0 && flag == 0)
                _player[member].addCard(_deck.deelCard(1));
            if(flag == 0){
                if(way == 1) member++;
                else member--;
            }
            if(member >= _member) member = 0;
            else if(member < 0) member = _member - 1;            
        }

        for(auto& player: _player){
            cout << player.getName() << "'s total points: " << player.getTP() << endl;
        }

        for(int mem = 0; mem < _member; mem++){   //遊戲結束，數據重製
            _player[mem].clearCard(-1);
            _player[mem].clearPoint();
        }
        _deck.setDeck();
        _deck.Shuffle();
        round++;
    }
    finish();    
}

void Game::setPlayerID(int member){
    map<string, int> priority = {
        {"c", 0}, {"d", 1}, {"h", 2}, {"s", 3}
    };

    for(int mem = 0; mem < member; mem++){
        _player[mem].addCard(_deck.deelCard(1));
    }

    sort(_player.begin(), _player.end(), [&priority](Player& p1, Player& p2){  //排列Players的順序
        int num1 = stoi(p1.getCard(0).getNumber());
        int num2 = stoi(p2.getCard(0).getNumber()); 
        if(num1 != num2)
            return num1 > num2;
        else{
            string suit1 = p1.getCard(0).getSuit();
            string suit2 = p2.getCard(0).getSuit();
            return priority.at(suit1) > priority.at(suit2);
        }
    });
    for(int id = 1; id <= member; id++){  //設定Players的ID
        _player[id - 1].setID(id);
    }
}

void Game::setPlayer(int member){
    string name;
    cout << "What is your nickname (enter 0 if you don't want to set nickname): ";
    cin >> name;
    for(int mem = 0; mem < member; mem++){
        _player.push_back(Player());
        if(mem == 0){
            _player[mem].setStatus(1, name);
        }
        else{
            _player[mem].setStatus(0, "robot" + to_string(mem));
        }
    }    
}
int Game::human(Player& player, int idx){
    process(player.getCardStr());
    call(1);
    cout << '\n';

    int choice, func, add;   //choice: 選哪張牌，func: 那張牌的功能，add: 加還是減
    cout << "Which card do you want? Enter the number: ";
    cin >> choice;
    while(!(choice <= player.getCardSize() && choice >= 1)){
        cout << "Please enter number between 1 ~ " << player.getCardSize() << ": ";
        cin >> choice;
    }
    cout << endl;
    func = player.getCard(choice - 1).function();
    player.clearCard(choice - 1);

    if(func == 10 || func == 20){
        cout << "Enter 1 for +" << func << ", 0 for -" << func << ": ";
        cin >> add;
        while(add != 1 && add != 0){
            cout <<"Enter 1 for +, 0 for -: ";
            cin >> add;
        }
        player.addPoint(func, add);
    }
    else if(func == 4 && _member > 3){
        return -2;
    }
    else if(func == 5){
        int next;
        cout << "Other players: ";
        for(int mem = 0; mem < _member; mem++){
            if(mem != idx)
                cout << _player[mem].getName() << "(id: " << _player[mem].getID() << "), ";
        }
        cout << "Enter ID to specify the next player: ";
        cin >> next;
        while(next == idx + 1 || next > _member || next < 1){
            cout << "ID cannot be found, try again: ";
            cin >> next;
        }
        return next - 1;
    }
    else if(func == 11){
        return -1;
    }
    else{
        player.addPoint(func, 1);
    }
    return -1;
}

int Game::robot(Player& player, int idx){
    int priority[7] = { 4, 11, 5, 10, 20, 0, 99};
    int min = 100, idxC = -1;
    for(int card = 0; card < player.getCardSize(); card++){   //basic card
        int func = player.getCard(card).function();
        if(find(begin(priority), end(priority), func) == end(priority)){
            if(func < min){
                min = func;
                idxC = card;
            }
        }
    }

    if(idxC != -1){
        cout << player.getName() << " played this card:" << endl;
        string s = player.getCard(idxC).getSuit() + player.getCard(idxC).getNumber();        
        process(s);
        call(0);
        cout << '\n';
        player.addPoint(min, 1);
        player.clearCard(idxC);
        return -1;
    }

    for(int p = 0; p < 7; p++){                    //function card
        for(int card = 0; card < player.getCardSize(); card++){
            int func = player.getCard(card).function();
            if(func == priority[p]){
                cout << player.getName() << " played this card:" << endl;
                string s = player.getCard(card).getSuit() + player.getCard(card).getNumber();
                process(s);
                call(0);
                cout << '\n';
                player.clearCard(card);

                switch(func){
                    case 4:
                        if(_member <= 3){
                            player.addPoint(4, 1);
                            return -1;
                        }
                        return -2;
                    case 11: return -1;
                    case 5:{
                        random_device rd;
                        mt19937 g(rd());
                        uniform_int_distribution<> dist(0,_member - 1);
                        int rn;
                        do{
                            rn = dist(g);                            
                        }while(rn == idx);
                        return rn;
                    }
                    case 10: case 20:
                        player.addPoint(func, 0);
                        return -1;
                    case 0: case 99:
                        player.addPoint(func, 1);
                        return -1;
                }
            }
        }
    }
    return -1;
}

int Game::judgeOver(Player& player, int& Fplace, int& Lplace){
    if(_deck.deckSize() <= 1){
        sort(_player.begin(), _player.end(), [](Player& p1, Player& p2){
            if(p1.getInGame() == 1 && p2.getInGame() == 1){
                return p1.getCP() < p2.getCP();
            }
            return p1.getInGame() == 1;
        });

        for(int mem = 0; mem < _member; mem++){
            if(_player[mem].getInGame() == 1){
                _player[mem].addTotal(_member - Fplace);
                Fplace++;
            }
        }
        cout << "This round is over\n" << endl;
        return 0;
    }
    else{
        if(Fplace + Lplace == _member - 1){
            for(int mem = 0; mem < _member; mem++){
                if(_player[mem].getInGame() == 1){
                    _player[mem].addTotal(_member - Fplace);
                    break;
                }
            }
            cout << "This round is over\n" << endl;
            return 0;
        }
    }
    return 1;
}

void Game::judgeWin(Player& player, int& Fplace, int& Lplace){
    if(player.getCardSize() == 0 && player.getCP() <= 99){
        player.addTotal(_member - Fplace);
        Fplace++;
        cout << player.getName() << " win!";
        cout << " The current total score is " << player.getTP() << " points." << endl;
        player.setInGame(0);
    }
}

void Game::judgeLose(Player& player, int& Fplace, int& Lplace){
    int priority[7] = { 4, 11, 5, 10, 20, 0, 99};
    int sum = 0, functionCard = 0;
    for(int card = 0; card < player.getCardSize(); card++){
        int func = player.getCard(card).function();
        if(find(begin(priority), end(priority), func) == end(priority)){
            sum += func;
        }
        else{
            functionCard++;
        }
    }

    if(player.getCP() > 99){
        player.addTotal(Lplace + 1);
        Lplace++;
        cout << player.getName() << " is eliminated.\n" << endl;
        player.setInGame(0);
    }
    else{
        if(sum + player.getCP() > 99){
            if(functionCard == 0 && player.getStatus() == 0){
                player.addTotal(Lplace + 1);
                Lplace++;
                cout << player.getName() << " is eliminated.\n" << endl;
                player.setInGame(0);
            }
        }
    }
}