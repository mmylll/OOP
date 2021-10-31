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
    cout << "��ʼ������:\n";
    lattices.printLattices();
    int ch;
    while (1) {
        if (_kbhit()) {//����а������£���_kbhit()����������
            ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
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