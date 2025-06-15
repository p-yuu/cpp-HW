#include"box.cpp"
using namespace std;

int main(int argc, char** argv){
    Box box;
    box.welcome(1);

    int file_number;
    fstream file;
    string file_name;
    do {
        cout << "Enter the map's number (only need number): ";
        cin >> file_number;
        file_name = "mission" + to_string(file_number) + ".txt";
        file.open(file_name, ios::in);

        if (!file) {
            cout << "This is not a map, enter again." << endl;
        }
    } while (!file);
    cout << endl;
    
    box.setMap(file);
    box.setBox();

    box.welcome(2);
    int mode;
    cin >> mode;
    cout << endl;
    box.moveBox(mode);
}