#include <iostream>
#include <conio.h>  // Windows only

int main() {
    std::cout << "ESC...\n";
    while (true) {
        int ch = _getch(); // 讀取第一個字元

        if (ch == 27) { // ESC 鍵 ASCII = 27
            std::cout << "exit。\n";
            break;
        }

        if (ch == 0 || ch == 224) {
            // 特殊鍵：上下左右鍵等
            int arrow = _getch(); // 再讀一個字元判別是哪個特殊鍵
            switch (arrow) {
                case 72: std::cout << "up\n"; break;
                case 80: std::cout << "down\n"; break;
                case 75: std::cout << "left\n"; break;
                case 77: std::cout << "right\n"; break;
                default: std::cout << "other " << arrow << "\n"; break;
            }
        } else {
            std::cout << "normal:" << static_cast<char>(ch) << "\n";
        }
    }
    return 0;
}
