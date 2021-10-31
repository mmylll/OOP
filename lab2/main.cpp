#include <iostream>
#include <conio.h>
#include "Lattices.h"

using namespace std;

int main() {
    Lattices lattices{};
    lattices.setValue(2);
    lattices.setWidth(4);
    lattices.setInitNums(2);
    lattices.initMap();
    lattices.setSuccessValue(2048);
    cout << "初始化方格:\n";
    lattices.printLattices();
    int ch;
    while (1) {
        if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
            ch = _getch();//使用_getch()函数获取按下的键值
            int result = lattices.logical_move(ch,lattices);
            //cout << result << "\n";
            if(result == 0){
                break;
            }
        }
    }
    //system("pause");
    return 0;
}