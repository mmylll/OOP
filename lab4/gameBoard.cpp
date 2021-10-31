//
// Created by 22332 on 2021/4/2.
//
#include <iostream>
#include <iomanip>
#include "gameBoard.h"
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>


using namespace std;
void GameBoard ::setScale(int mScale) {
    this->scale = mScale;
}
void GameBoard :: setValue(int mValue){
    this->value = mValue;
}
void GameBoard :: setLatticesMap(int x,int y){
    lattices_map[x][y] = value;
}
void GameBoard ::setSuccessValue(int mSuccessValue) {
    success_value = mSuccessValue;
}
void GameBoard ::setInitNums(int mNums) {
    initNums = mNums;
}
void GameBoard ::setRoundFraction(int mRoundFraction) {
    this->roundFraction = mRoundFraction;
}
void GameBoard ::setFraction(int mFraction) {
    this->fraction = mFraction;
}
void GameBoard ::setUserName(std::string mUsername) {
    this->username = mUsername;
}
void GameBoard::setRegretNums(int mRegretNums) {
    this->regret_nums = mRegretNums;
}
int GameBoard ::getScale() const{
    return this->scale;
}
int GameBoard :: getValue() const{
    return this->value;
}
int **GameBoard ::getLatticesMap() {
    return lattices_map;
}
int * GameBoard :: getRandoms() {
    if((scale != 0)&&(initNums != 0)) {
        int *randoms = new int[initNums];
        randoms[0] = (rand() % (scale - 0)) + 0;
        randoms[1] = (rand() % (scale - 0)) + 0;
        //cout<<randoms[0]<<" "<<randoms[1]<<"\n";
        return randoms;
    }
}
int GameBoard :: getSuccessValue() {
    return success_value;
}
int GameBoard ::getRoundFraction() {
    return this->roundFraction;
}
int GameBoard ::getFraction() {
    return fraction;
}
string GameBoard ::getUsername() {
    return this->username;
}
int GameBoard::getRegretNums() {
    return this->regret_nums;
}
void GameBoard :: initMap(){//先初始化数组
    regret_nums = 0;
    fraction = 0;
    roundFraction = 0;
    int count = 0;//记录初始化数字个数
    if((scale != 0)&&(initNums != 0)){
        lattices_map = new int*[scale];
        for(int i = 0;i < scale;i++){
            lattices_map[i] = new int[scale];
        }
        for(int i = 0;i < scale;i++){
            for (int j = 0;j < scale;j++){
                lattices_map[i][j] = 0;
            }
        }
    }
    //刚开始的填充数字
    while(count < initNums){
        int *temp = getRandoms();
        if(isFull(temp[0],temp[1])){
            continue;
        }else{
            lattices_map[temp[0]][temp[1]] = value;
            count++;
        }
    }
}
void GameBoard :: printLattices(){//细分行，粗分列
    cout<<scale<<"*"<<scale<<"\n";
    cout<<"当前得分:"<<*p_fraction<<"\n";
    for(int i = 0;i < 2*scale+1;i++){
        for(int j = 0;j < scale;j++){
            if(i%2==0){
                if(j == scale-1){
                    cout<<"+ ------ +"<<"\n";
                } else{
                    cout<<"+ ------ ";
                }
            }else{
                if(j == scale-1){
                    if(lattices_map[(i-1)/2][j] != 0){//格式化输出
                        cout<<"|"<<" "<<setw(4)<<lattices_map[(i-1)/2][j]<<"   "<<"|\n";
                        //cout<<setw(8)<<lattices_map[(i-1)/2][j]<<"\n";
                    } else{
                        //cout<<"|"<<"   "<<" "<<"   "<<"|\n";
                        cout<<"|"<<"    "<<setw(4)<<"   "<<"|\n";
                    }

                } else{
                    if(lattices_map[(i-1)/2][j] != 0){
                        cout<<"|"<<" "<<setw(4)<<lattices_map[(i-1)/2][j]<<"   ";
                        //cout<<setw(8)<<lattices_map[(i-1)/2][j];
                    } else{
                        //cout<<"|"<<"   "<<" "<<"   ";
                        cout<<"|"<<"    "<<setw(4)<<"   ";
                    }
                }
            }

        }
    }
}
bool GameBoard :: isFull(int x,int y){//判断某个方格是否填充
    bool result = true;
    if(lattices_map[x][y] == 0){
        result = false;
    }
    return result;
};
void GameBoard ::addRandom(int val,int nums) {
    int count = 0;
    val = getValue();
    while(count < nums){
        int *temp = getRandoms();
        if(isFull(temp[0],temp[1])){
            continue;
        }else{
            lattices_map[temp[0]][temp[1]] = val;
            count++;
        }
    }
}
bool GameBoard :: isFull_lattices(){//判断整个方格是否填满
    bool result = true;
    for(int i = 0;i < scale;i++){
        for(int j = 0;j < scale;j++){
            if(lattices_map[i][j] == 0){
                result = false;
            }
        }
    }
    return result;
}
void GameBoard :: key_w() {//以行为单位
    //cout<<(*p_fraction)++<<"-----------------------\n";
    for(int j = 0;j < scale;j++){
        for(int k = 0,i = 1;i < scale;i++){
            if(lattices_map[i][j] > 0){
                if(lattices_map[k][j] == lattices_map[i][j]){//合并
                    lattices_map[k][j] = 2*lattices_map[k][j];
                    roundFraction = lattices_map[k][j];//计算回合分数
                    lattices_map[i][j] = 0;
                    k++;
                    *p_fraction = *p_fraction+roundFraction;
                } else if(lattices_map[k][j] == 0){//移动
                    lattices_map[k][j] = lattices_map[i][j];
                    lattices_map[i][j] = 0;
                }else{//碰撞
                    lattices_map[k+1][j] = lattices_map[i][j];
                    if(k+1 != i){
                        lattices_map[i][j] = 0;
                    }
                    k++;
                }
            }
        }
    }
}
void GameBoard :: key_s() {
    for(int j = 0;j < scale;j++){
        for(int k = scale-1,i = scale-2;i >= 0;i--){
            if(lattices_map[i][j] > 0){
                if(lattices_map[k][j] == lattices_map[i][j]){
                    lattices_map[k][j] = 2*lattices_map[k][j];
                    roundFraction = lattices_map[k][j];//计算回合分数
                    lattices_map[i][j] = 0;
                    k--;
                    *p_fraction = *p_fraction+roundFraction;
                } else if(lattices_map[k][j] == 0){
                    lattices_map[k][j] = lattices_map[i][j];
                    lattices_map[i][j] = 0;
                }else{
                    lattices_map[k-1][j] = lattices_map[i][j];
                    if(k-1 != i){
                        lattices_map[i][j] = 0;
                    }
                    k--;
                }
            }
        }
    }
}
void GameBoard :: key_a() {
    for(int i = 0;i < scale;i++){
        for(int j = 1,k = 0;j < scale;j++){
            if(lattices_map[i][j] > 0){
                if(lattices_map[i][k] == lattices_map[i][j]){
                    lattices_map[i][k] = 2*lattices_map[i][k];
                    roundFraction = lattices_map[i][k];//计算回合分数
                    lattices_map[i][j] = 0;
                    k++;
                    *p_fraction = *p_fraction+roundFraction;
                }else if(lattices_map[i][k] == 0){
                    lattices_map[i][k] = lattices_map[i][j];
                    lattices_map[i][j] = 0;
                }else{
                    lattices_map[i][k+1] = lattices_map[i][j];
                    if(k+1 != j){
                        lattices_map[i][j] = 0;
                    }
                    k++;
                }
            }
        }
    }
}
void GameBoard :: key_d() {
    for(int i = 0;i < scale;i++){
        for(int j = scale-2,k = scale-1;j >= 0;j--){
            if(lattices_map[i][j] > 0){
                if(lattices_map[i][k] == lattices_map[i][j]){
                    lattices_map[i][k] = 2*lattices_map[i][k];
                    roundFraction = lattices_map[i][k];//计算回合分数
                    lattices_map[i][j] = 0;
                    k--;
                    *p_fraction = *p_fraction+roundFraction;
                }else if(lattices_map[i][k] == 0){
                    lattices_map[i][k] = lattices_map[i][j];
                    lattices_map[i][j] = 0;
                }else{
                    lattices_map[i][k-1] = lattices_map[i][j];
                    if(k-1 != j){
                        lattices_map[i][j] = 0;
                    }
                    k--;
                }
            }
        }
    }
}
bool GameBoard ::check_game_over() {

    for(int i = 0;i < scale-1;i++){
        for(int j = 0;j < scale-1;j++){
            if((lattices_map[i][j] == lattices_map[i][j+1])||(lattices_map[i][j] == lattices_map[i+1][j])){
                return false;
            }
        }
    }
    for(int j = 0;j < scale-1;j++){
        if(lattices_map[scale-1][j] == lattices_map[scale-1][j+1])
            return false;
    }
    for(int i = 0;i < scale-1;i++){
        if(lattices_map[i][scale-1] == lattices_map[i+1][scale-1])
            return false;
    }
    return true;
}
bool GameBoard ::check_game_success() {
    for(int i = 0;i < scale;i++){
        for(int j = 0;j < scale;j++){
            if(lattices_map[i][j] == getSuccessValue()){
                return true;
            }
        }
    }
    return false;
}
int GameBoard ::logical_move(int operate,GameBoard gameBoard) {
    if(operate == 119){
        gameBoard.key_w();
    }else if(operate == 115){
        gameBoard.key_s();
    }else if(operate == 97){
        gameBoard.key_a();
    }else if(operate== 100){
        gameBoard.key_d();
    }else if(operate == 9){
        cout << "已退出游戏!"<<"\n";
        return 0;
    }else if(operate == 13) {
        //cout << "这是回车" <<"\n";
        return 1;
    }else{
        cout << "请输入正确指令!"<<"\n";
        return 1;
    }
    if(gameBoard.check_game_success()){
        //gameBoard.printLattices();
        if(gameBoard.getUsername().empty()) {
            cout << "成功!" << "\n";
            return 0;
        }else{
            return 2;
        }

    }else if (!gameBoard.isFull_lattices()){
        gameBoard.addRandom(gameBoard.getValue(), 1);
        if(gameBoard.isFull_lattices()){
            if (gameBoard.check_game_over()) {
                //gameBoard.printLattices();
                cout << gameBoard.getUsername() <<"游戏失败"<<"\n";
                return 0;
            }else{
                //gameBoard.printLattices();
                cout << gameBoard.getUsername() << "还可以再移动!" << "\n";
                return 1;
            }
        } else if(!gameBoard.isFull_lattices()){
            //gameBoard.printLattices();
            return 1;
        }
    }else{
        if (gameBoard.check_game_over()) {
            //gameBoard.printLattices();
            cout << gameBoard.getUsername() << "游戏失败"<<"\n";
            return 0;
        }else{
            //gameBoard.printLattices();
            cout << gameBoard.getUsername() << "还可以再移动!请继续" << "\n";
            return 1;
        }
    }
}
void GameBoard :: saveStatus(const std::string& filename) {
    ofstream OutFile;
    OutFile.open(filename,ios::out | ios::in | ios::app);
    for(int i = 0 ;i < scale;i++){
        for(int j = 0;j < scale;j++){
            OutFile << lattices_map[i][j] << " ";
        }
    }
    OutFile << fraction;
    OutFile << "\n";
    OutFile.close();
}

void GameBoard::fileEmpty(const string& fileName) {
    fstream file(fileName, ios::out);
}

int * GameBoard::readStatus(std::string filename) {
    DelLineData(filename, CountLines(filename));
    int *array = new int [scale*scale+1];
    char * p = std::strtok (ReadLineData(filename, CountLines(filename))," ");
    int i = 0;
    while (p!=0)
    {
        //cout << p << '\n';
        array[i] = atoi(p);
        //cout << array[i] <<"fff" <<"\n";
        p = std::strtok(NULL," ");
        i++;
    }
    i = 0;
    for(int j = 0;j < scale;j++){
        for(int k = 0;k < scale;k++){
            //cout << array[i] <<"fff" <<"\n";
            lattices_map[j][k] = array[i];
            i++;
        }
    }
    fraction = array[scale*scale];
    return array;
}
std::string GameBoard::CharToStr(char *contentChar) {
    string tempStr;
    for (int i=0;contentChar[i]!='\0';i++)
    {
        tempStr+=contentChar[i];
    }
    return tempStr;
}

char* GameBoard::ReadLineData(const string &fileName, int lineNum) {
    char lineData[1024] = {0};
    ifstream in;
    in.open(fileName);
    int line = 1;
    while (in.getline(lineData,1024))
    {
        if (lineNum == line)
        {
            break;
        }
        line ++ ;
    }
    in.close();
    return lineData;
}

void GameBoard::DelLineData(const string &fileName, int lineNum) {
    ifstream in;
    in.open(fileName);

    string strFileData = "";
    int line = 1;
    char lineData[1024] = {0};
    while(in.getline(lineData, sizeof(lineData)))
    {
        if (line == lineNum)
        {
            //strFileData += "\n";
            continue;
        }
        else
        {
            strFileData += CharToStr(lineData);
            strFileData += "\n";
        }
        line++;
    }
    in.close();

    //写入文件
    ofstream out;
    out.open(fileName);
    out.flush();
    out<<strFileData;
    out.close();
}

void GameBoard::ModifyLineData(const string &fileName, int lineNum, char *lineData) {
    ifstream in;
    in.open(fileName);
    string strFileData = "";
    int line = 1;
    char tmpLineData[1024] = {0};
    while(in.getline(tmpLineData, sizeof(tmpLineData)))
    {
        if (line == lineNum)
        {
            strFileData += CharToStr(lineData);
            strFileData += "\n";
        }
        else
        {
            strFileData += CharToStr(tmpLineData);
            strFileData += "\n";
        }
        line++;
    }
    in.close();
    //写入文件
    ofstream out;
    out.open(fileName);
    out.flush();
    out<<strFileData;
    out.close();
}

int GameBoard::CountLines(std::string filename) {
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
    if(ReadFile.fail())//文件打开失败:返回0
    {
        return 0;
    }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}






