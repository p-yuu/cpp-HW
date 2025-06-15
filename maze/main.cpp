#include"player.cpp"
using namespace std;

int main(int argc, char** argv){
    vector<fstream> file;
    for(int i = 1; i < argc; i++){
        fstream tempFile(argv[i], ios::in);
        if (!tempFile.is_open()) {
            cout << "input file " << argv[i] << " open failed." << endl;
            exit(1);
        }

        file.push_back(move(tempFile));
    }

    Player play;
    int mp, mode;
    play.welcome(argc, 1);
    play.welcome(argc, 2);
    while(cin >> mp){
        if(mp >= 1 && mp < argc) break;
        cout << "Enter 1 ~ " << argc - 1 << ": " ;
    }
    play.welcome(argc, 3);
    while(cin >> mode){
        if(mode >= 1 && mode <= 3) break;
        cout << "Enter 1 ~ 3: ";
    }

    cout << endl;
    play.setMap(file[mp - 1], mode);
}