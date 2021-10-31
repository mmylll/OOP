#include <iostream>
#include "gameBoard.h"
#include <conio.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;
void printDoubleLattices(GameBoard gameBoard1, GameBoard gameBoard2, int player,int success) {
    int scale = gameBoard1.getScale();
    if((player == 0)&&(success == 0)){
        cout << "请玩家 "<<gameBoard1.getUsername()<<" 操作\n";
    }else if((player == 1)&&(success == 0)){
        cout << "请玩家 "<<gameBoard2.getUsername()<<" 操作\n";
    }
    cout << "玩家:"<<gameBoard1.getUsername()<<"     "<<"当前用户得分:"<<setw(5)<<gameBoard1.getFraction()<<"                 "<<"玩家:"<<gameBoard2.getUsername()<<"     "<<"当前用户得分:"<<setw(5)<<gameBoard2.getFraction()<<"\n";
    for(int i = 0;i < 2*scale+1;i++){
        for(int j = 0;j < 2*scale;j++){//看几个玩家
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
                    if (gameBoard1.getLatticesMap()[(i - 1) / 2][j] != 0) {//格式化输出
                        cout << "|" << " " << setw(4) << gameBoard1.getLatticesMap()[(i - 1) / 2][j] << "   " << "|        ";
                        //cout<<setw(8)<<lattices_map[(i-1)/2][j]<<"\n";
                    } else {
                        //cout<<"|"<<"   "<<" "<<"   "<<"|\n";
                        cout << "|" << "    " << setw(4) << "   " << "|        ";
                    }
                }else if(j == 2*scale-1){
                    if (gameBoard2.getLatticesMap()[(i - 1) / 2][j-scale] != 0) {//格式化输出
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
    bool hasSuccessValue = false;
    //cout << argc <<"\n";
    if(argc == 2) {
        if (opt == argv[1]) {
            hasSuccessValue = true;
        }
    }
    int pattern = 0;
    string operate;
   while(1){
       cout <<"---------------------开始游戏---------------------"<<"\n";
       cout <<"请进行模式选择:"<<"\n";
       cout <<"1:单人模式"<<"\n";
       cout <<"2:双人模式"<<"\n";
       cout <<"3.退出"<<"\n";
       cout <<"请键入对应模式的序号:"<<"\n";
       cin >> pattern;
       if((pattern == 1)||(pattern == 2)){
           break;
       }else{
           cout << "错误指令，请选择模式" <<"\n";
           continue;
       }
   }
    if(pattern == 1){
        cout << "您已选择单人模式，开始游戏"<<"\n";
        GameBoard gameBoard;
        gameBoard.setValue(2);
        gameBoard.setScale(4);
        gameBoard.setInitNums(2);
        gameBoard.initMap();
        gameBoard.setSuccessValue(2048);
        if(hasSuccessValue){
            gameBoard.setSuccessValue(64);
            cout << "已成功设置终止条件!" << "\n";
        }
        cout << "初始化方格:\n";
        gameBoard.printLattices();
        int ch;
        int result;
        while (1) {
            if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
                ch = _getch();//使用_getch()函数获取按下的键值
                if((ch == 119)||(ch == 115)||(ch == 97)||(ch == 100)||(ch == 9)) {
                    result = gameBoard.logical_move(ch,gameBoard);
                    gameBoard.printLattices();
                    if(result == 0){
                        break;
                    }
                }else{
                    if(ch != 13){
                        cout<<"请输入正确指令!"<<"\n";
                        gameBoard.printLattices();
                    }
                }
            }
        }
    }else if(pattern == 2){
        int num = 0;//操作次数
        int result = -1;//逻辑移动结果
        cout << "已选择双人模式，开始游戏"<<"\n";
        string username;
        GameBoard gameBoard1;
        gameBoard1.setValue(2);
        gameBoard1.setScale(4);
        gameBoard1.setInitNums(2);
        gameBoard1.initMap();
        gameBoard1.setSuccessValue(2048);
        GameBoard gameBoard2;
        gameBoard2.setValue(2);
        gameBoard2.setScale(4);
        gameBoard2.setInitNums(2);
        gameBoard2.initMap();
        gameBoard2.setSuccessValue(2048);
        if(hasSuccessValue){
            gameBoard1.setSuccessValue(64);
            gameBoard2.setSuccessValue(64);
            cout << "已成功设置终止条件!" << "\n";
        }

        cout << "请输入第一位玩家用户名:" <<"\n";
        cin >> username;
        gameBoard1.setUserName(username);
        cout << "请输入第二位玩家用户名:" <<"\n";
        cin >> username;
        gameBoard2.setUserName(username);
        printDoubleLattices(gameBoard1,gameBoard2,num%2,0);
        int ch;
        while (1) {
            if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
                ch = _getch();//使用_getch()函数获取按下的键值
                if((ch == 119)||(ch == 115)||(ch == 97)||(ch == 100)||(ch == 9)) {
                    if (num % 2 == 0) {
                        result = gameBoard1.logical_move(ch, gameBoard1);
                    } else {
                        result = gameBoard2.logical_move(ch, gameBoard2);
                    }
                    num++;
                    //cout << result << "\n";
                    if (result == 0) {
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,1);
                        break;
                    }
                    if(result == 2){
                        printDoubleLattices(gameBoard1,gameBoard2,num % 2,1);
                        if(gameBoard1.getFraction() > gameBoard2.getFraction()){
                            cout << gameBoard1.getUsername() << "胜利，游戏结束!" <<"\n";
                        }else if(gameBoard1.getFraction() < gameBoard2.getFraction()){
                            cout << gameBoard2.getUsername() << "胜利，游戏结束!" <<"\n";
                        }else{
                            cout << "平局，游戏结束!" <<"\n";
                        }
                        break;
                    }
                    printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                }else {
                    if(ch != 13){
                        cout<<"请输入正确指令!"<<"\n";
                        printDoubleLattices(gameBoard1, gameBoard2, num % 2,0);
                    }
                }
            }
        }
    }
   return 0;
}
