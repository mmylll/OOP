#include <iostream>
#include "gameBoard.h"
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

void printDoubleLattices(GameBoard gameBoard1, GameBoard gameBoard2, int player,int success) {
    int scale = gameBoard1.getScale();
    if((player == 0)&&(success == 0)){
        cout << "����� "<<gameBoard1.getUsername()<<" ����\n";
    }else if((player == 1)&&(success == 0)){
        cout << "����� "<<gameBoard2.getUsername()<<" ����\n";
    }
    cout << "���:"<<gameBoard1.getUsername()<<"     "<<"��ǰ�û��÷�:"<<setw(5)<<gameBoard1.getFraction()<<"                 "<<setw(15*(scale-4))<<"���:"<<gameBoard2.getUsername()<<"     "<<"��ǰ�û��÷�:"<<setw(5)<<gameBoard2.getFraction()<<"\n";
    for(int i = 0;i < 2*scale+1;i++){
        for(int j = 0;j < 2*scale;j++){//���������
            if(i%2==0){
                if(j == scale-1){
                    cout<<"+ ------ +"<<"        ";
                } else if(j == 2*scale-1) {
                    cout << "+ ------ +" << "\n";
                }else{
                    cout<<"+ ------ ";
                }
            }else{
                if(j == scale-1) {
                    if (gameBoard1.getLatticesMap()[(i - 1) / 2][j] != 0) {//��ʽ�����
                        cout << "|" << " " << setw(4) << gameBoard1.getLatticesMap()[(i - 1) / 2][j] << "   " << "|        ";
                        //cout<<setw(8)<<lattices_map[(i-1)/2][j]<<"\n";
                    } else {
                        //cout<<"|"<<"   "<<" "<<"   "<<"|\n";
                        cout << "|" << "    " << setw(4) << "   " << "|        ";
                    }
                }else if(j == 2*scale-1){
                    if (gameBoard2.getLatticesMap()[(i - 1) / 2][j-scale] != 0) {//��ʽ�����
                        cout << "|" << " " << setw(4) << gameBoard2.getLatticesMap()[(i - 1) / 2][j-scale] << "   " << "|\n";
                        //cout<<setw(8)<<lattices_map[(i-1)/2][j]<<"\n";
                    } else {
                        //cout<<"|"<<"   "<<" "<<"   "<<"|\n";
                        cout << "|" << "    " << setw(4) << "   " << "|\n";
                    }
                }else {
                    if (j < scale) {
                        if (gameBoard1.getLatticesMap()[(i - 1) / 2][j] != 0) {
                            cout << "|" << " " << setw(4) << gameBoard1.getLatticesMap()[(i - 1) / 2][j] << "   ";
                            //cout<<setw(8)<<lattices_map[(i-1)/2][j];
                        } else {
                            //cout<<"|"<<"   "<<" "<<"   ";
                            cout << "|" << "    " << setw(4) << "   ";
                        }
                    }else{
                        if (gameBoard2.getLatticesMap()[(i - 1) / 2][j-scale] != 0) {
                            cout << "|" << " " << setw(4) << gameBoard2.getLatticesMap()[(i - 1) / 2][j-scale] << "   ";
                            //cout<<setw(8)<<lattices_map[(i-1)/2][j];
                        } else {
                            //cout<<"|"<<"   "<<" "<<"   ";
                            cout << "|" << "    " << setw(4) << "   ";
                        }
                    }
                }
            }

        }
    }
}


int main(int argc,char* argv[]) {
    string opt = "-t";
    string opt1 = "-s";
    int mScale = 0;
    bool hasSuccessValue = false;
    bool hasScale = false;
    if(argc == 2) {
        if (opt == argv[1]) {
            hasSuccessValue = true;
        }
    }
    if(argc == 3) {
        if (opt1 == argv[1]) {
            hasScale = true;
            string str = argv[2];
            mScale = atoi(str.c_str());
            while((mScale < 3)||(mScale > 5)){
                hasScale = false;
                cout << "������������������"<<"\n";
                cin >> mScale;
                if((mScale > 2)&&(mScale < 6)){
                    hasScale = true;
                }
            }
        }
    }
    int pattern = 0;
    string operate;
   while(1){
       cout <<"---------------------��ʼ��Ϸ---------------------"<<"\n";
       cout <<"�����ģʽѡ��:"<<"\n";
       cout <<"1:����ģʽ"<<"\n";
       cout <<"2:˫��ģʽ"<<"\n";
       cout <<"3.�˳�"<<"\n";
       cout <<"������Ӧģʽ�����:"<<"\n";
       cin >> pattern;
       if((pattern == 1)||(pattern == 2)){
           break;
       }else{
           cout << "����ָ���ѡ��ģʽ" <<"\n";
           continue;
       }
   }
    if(pattern == 1){
        cout << "����ѡ����ģʽ����ʼ��Ϸ"<<"\n";
        GameBoard gameBoard;
        gameBoard.setValue(2);
        gameBoard.setScale(4);
        gameBoard.setInitNums(2);
        if(hasScale){
            gameBoard.setScale(mScale);
            cout << "�ѳɹ����ù�ģ!" << "\n";
        }
        gameBoard.initMap();
        gameBoard.setSuccessValue(2048);
        if(hasSuccessValue){
            gameBoard.setSuccessValue(64);
            cout << "�ѳɹ�������ֹ����!" << "\n";
        }

        cout << "��ʼ������:\n";
        gameBoard.printLattices();
        gameBoard.fileEmpty("player.txt");
        gameBoard.saveStatus("player.txt");
        //cout << gameBoard.readStatus("player.txt")[0] << "++++++++++++" <<"\n";
        int ch;
        int result;
        while (1) {
            if (_kbhit()) {//����а������£���_kbhit()����������
                ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
                //cout << ch <<"---------" << "\n";
                if((ch == 119)||(ch == 115)||(ch == 97)||(ch == 100)||(ch == 9)) {
                    result = gameBoard.logical_move(ch,gameBoard);
                    gameBoard.saveStatus("player.txt");
                    gameBoard.printLattices();
                    if(result == 0){
                        break;
                    }
                }else if(ch == 122){
                    if(gameBoard.CountLines("player.txt") == 1){
                        cout << "�������ٻ���!" <<"\n";
                        gameBoard.printLattices();
                        continue;
                    }
                    gameBoard.readStatus("player.txt");
                    gameBoard.printLattices();
                }else{
                    if(ch != 13){
                        cout<<"��������ȷָ��!"<<"\n";
                        gameBoard.printLattices();
                    }
                }
            }
        }
    }else if(pattern == 2){
        int num = 0;//��������
        int result = -1;//�߼��ƶ����
        cout << "��ѡ��˫��ģʽ����ʼ��Ϸ"<<"\n";
        string username;
        GameBoard gameBoard1;
        gameBoard1.setValue(2);
        gameBoard1.setScale(4);
        gameBoard1.setInitNums(2);
        if(hasScale){
            gameBoard1.setScale(mScale);
        }
        gameBoard1.initMap();
        gameBoard1.setSuccessValue(2048);
        GameBoard gameBoard2;
        gameBoard2.setValue(2);
        gameBoard2.setScale(4);
        gameBoard2.setInitNums(2);
        if(hasScale){
            gameBoard2.setScale(mScale);
            cout << "�ѳɹ����ù�ģ!" << "\n";
        }
        gameBoard2.initMap();
        gameBoard2.setSuccessValue(2048);
        if(hasSuccessValue){
            gameBoard1.setSuccessValue(64);
            gameBoard2.setSuccessValue(64);
            cout << "�ѳɹ�������ֹ����!" << "\n";
        }

        gameBoard1.initMap();
        gameBoard2.initMap();
        cout << "�������һλ����û���:" <<"\n";
        cin >> username;
        gameBoard1.setUserName(username);
        cout << "������ڶ�λ����û���:" <<"\n";
        cin >> username;
        gameBoard2.setUserName(username);
        printDoubleLattices(gameBoard1,gameBoard2,num%2,0);
        gameBoard1.fileEmpty("player1.txt");
        gameBoard1.saveStatus("player1.txt");
        gameBoard2.fileEmpty("player2.txt");
        gameBoard2.saveStatus("player2.txt");
        int ch;
        while (1) {
            if (_kbhit()) {//����а������£���_kbhit()����������
                ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ

                if((ch == 119)||(ch == 115)||(ch == 97)||(ch == 100)||(ch == 9)) {
                    if (num % 2 == 0) {
                        result = gameBoard1.logical_move(ch, gameBoard1);
                        gameBoard1.saveStatus("player1.txt");
                        if(gameBoard1.getRegretNums() < 0){
                            gameBoard1.setRegretNums(gameBoard1.getRegretNums()+1);
                        }
                    } else {
                        result = gameBoard2.logical_move(ch, gameBoard2);
                        gameBoard2.saveStatus("player2.txt");
                        if(gameBoard2.getRegretNums() < 0){
                            gameBoard2.setRegretNums(gameBoard2.getRegretNums()+1);
                        }
                    }
                    if((gameBoard1.getRegretNums() < 0)||(gameBoard2.getRegretNums() < 0)){
                        //cout << gameBoard1.getRegretNums() << "  " << gameBoard2.getRegretNums() << "\n";
                        if (num % 2 == 0) {
                           cout << gameBoard1.getUsername() << "�����:"<<"\n";

                        } else {
                            cout << gameBoard2.getUsername() << "�����:"<<"\n";
                        }
                    }else{
                        num++;
                    }
                    //cout << result << "\n";
                    if (result == 0) {
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,1);
                        break;
                    }
                    if(result == 2){
                        printDoubleLattices(gameBoard1,gameBoard2,num % 2,1);
                        if(gameBoard1.getFraction() > gameBoard2.getFraction()){
                            cout << gameBoard1.getUsername() << "ʤ������Ϸ����!" <<"\n";
                        }else if(gameBoard1.getFraction() < gameBoard2.getFraction()){
                            cout << gameBoard2.getUsername() << "ʤ������Ϸ����!" <<"\n";
                        }else{
                            cout << "ƽ�֣���Ϸ����!" <<"\n";
                        }
                        break;
                    }
                    printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                }else if(ch == 122){
                    if (num % 2 == 0) {
                        if(gameBoard1.CountLines("player1.txt") == 1){
                            cout << gameBoard1.getUsername() << "�������ٻ���!" <<"\n";
                            printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                            continue;
                        }
                        gameBoard1.readStatus("player1.txt");
                        if(gameBoard1.getRegretNums() == 0){
                            gameBoard1.setRegretNums(gameBoard1.getRegretNums()-1);
                        }
                        gameBoard1.setRegretNums(gameBoard1.getRegretNums()-1);
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                    } else {
                        if(gameBoard2.CountLines("player2.txt") == 1){
                            cout << gameBoard2.getUsername() << "�������ٻ���!" <<"\n";
                            printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                            continue;
                        }
                        gameBoard2.readStatus("player2.txt");
                        if(gameBoard2.getRegretNums() == 0){
                            gameBoard2.setRegretNums(gameBoard2.getRegretNums()-1);
                        }
                        gameBoard2.setRegretNums(gameBoard2.getRegretNums()-1);
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                    }
                }else{
                    if(ch != 13){
                        cout<<"��������ȷָ��!"<<"\n";
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                    }
                }
            }
        }
    }
   return 0;
}