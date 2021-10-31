//
// Created by 22332 on 2021/3/16.
//
#include <iostream>
#include <iomanip>
#include "Lattices.h"

using namespace std;

void Lattices :: setWidth(int initWidth){
    this->width = initWidth;
}
void Lattices :: setValue(int initValue){
    this->value = initValue;
}
void Lattices :: setLatticesMap(int x,int y){
    lattices_map[x][y] = value;
}
void Lattices ::setSuccessValue(int val) {
    success_value = val;
}
void Lattices ::setInitNums(int nums) {
    initNums = nums;
}
int Lattices :: getWidth() const{
    return this->width;
}
int Lattices :: getValue() const{
    return this->value;
}
int **Lattices::getLatticesMap() {
    return lattices_map;
}
int * Lattices :: getRandoms() {
    if((width != 0)&&(initNums != 0)) {
        int *randoms = new int[initNums];
        randoms[0] = (rand() % (width - 0)) + 0;
        randoms[1] = (rand() % (width - 0)) + 0;
        //cout<<randoms[0]<<" "<<randoms[1]<<"\n";
        return randoms;
    }
}
int Lattices :: getSuccessValue() {
    return success_value;
}
void Lattices :: initMap(){//�ȳ�ʼ������
    int count = 0;//��¼��ʼ�����ָ���
    if((width != 0)&&(initNums != 0)){
        lattices_map = new int*[width];
        for(int i = 0;i < width;i++){
            lattices_map[i] = new int[width];
        }
        for(int i = 0;i < width;i++){
            for (int j = 0;j < width;j++){
                lattices_map[i][j] = 0;
            }
        }
    }
    //�տ�ʼ���������
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
void Lattices :: printLattices(){//ϸ���У��ַ���
    cout<<width<<"*"<<width<<"\n";
    for(int i = 0;i < 2*width+1;i++){
        for(int j = 0;j < width;j++){
            if(i%2==0){
                if(j == width-1){
                    cout<<"+ ------ +"<<"\n";
                } else{
                    cout<<"+ ------ ";
                }
            }else{
                if(j == width-1){
                    if(lattices_map[(i-1)/2][j] != 0){//��ʽ�����
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
bool Lattices :: isFull(int x,int y){//�ж�ĳ�������Ƿ����
    bool result = true;
    if(lattices_map[x][y] == 0){
        result = false;
    }
    return result;
};
void Lattices ::addRandom(int val,int nums) {
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
bool Lattices :: isFull_lattices(){//�ж����������Ƿ�����
    bool result = true;
    for(int i = 0;i < width;i++){
        for(int j = 0;j < width;j++){
            if(lattices_map[i][j] == 0){
                result = false;
            }
        }
    }
    return result;
}
void Lattices :: key_w() {//����Ϊ��λ
    for(int j = 0;j < width;j++){
        for(int k = 0,i = 1;i < width;i++){
            if(lattices_map[i][j] > 0){
                if(lattices_map[k][j] == lattices_map[i][j]){//�ϲ�
                    lattices_map[k][j] = 2*lattices_map[k][j];
                    lattices_map[i][j] = 0;
                    k++;
                } else if(lattices_map[k][j] == 0){//�ƶ�
                    lattices_map[k][j] = lattices_map[i][j];
                    lattices_map[i][j] = 0;
                }else{//��ײ
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
void Lattices :: key_s() {
    for(int j = 0;j < width;j++){
        for(int k = width-1,i = width-2;i >= 0;i--){
            if(lattices_map[i][j] > 0){
                if(lattices_map[k][j] == lattices_map[i][j]){
                    lattices_map[k][j] = 2*lattices_map[k][j];
                    lattices_map[i][j] = 0;
                    k--;
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
void Lattices :: key_a() {
    for(int i = 0;i < width;i++){
        for(int j = 1,k = 0;j < width;j++){
            if(lattices_map[i][j] > 0){
                if(lattices_map[i][k] == lattices_map[i][j]){
                    lattices_map[i][k] = 2*lattices_map[i][k];
                    lattices_map[i][j] = 0;
                    k++;
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
void Lattices :: key_d() {
    for(int i = 0;i < width;i++){
        for(int j = width-2,k = width-1;j >= 0;j--){
            if(lattices_map[i][j] > 0){
                if(lattices_map[i][k] == lattices_map[i][j]){
                    lattices_map[i][k] = 2*lattices_map[i][k];
                    lattices_map[i][j] = 0;
                    k--;
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
bool Lattices ::check_game_over() {

    for(int i = 0;i < width-1;i++){
        for(int j = 0;j < width-1;j++){
            if((lattices_map[i][j] == lattices_map[i][j+1])||(lattices_map[i][j] == lattices_map[i+1][j])){
                return false;
            }
        }
    }
    for(int j = 0;j < width-1;j++){
        if(lattices_map[width-1][j] == lattices_map[width-1][j+1])
            return false;
    }
    for(int i = 0;i < width-1;i++){
        if(lattices_map[i][width-1] == lattices_map[i+1][width-1])
            return false;
    }
    return true;
}
bool Lattices ::check_game_success() {
    for(int i = 0;i < width;i++){
        for(int j = 0;j < width;j++){
            if(lattices_map[i][j] == getSuccessValue()){
                return true;
            }
        }
    }
    return false;
}
int Lattices ::logical_move(int operate,Lattices lattices) {
    if(operate == 119){
        lattices.key_w();
    }else if(operate == 115){
        lattices.key_s();
    }else if(operate == 97){
        lattices.key_a();
    }else if(operate== 100){
        lattices.key_d();
    }else if(operate == 9){
        cout << "���˳���Ϸ!"<<"\n";
        return 0;
    }else if(operate == 13) {
        //cout << "���ǻس�" <<"\n";
        return 1;
    }else{
        cout << "��������ȷָ��!"<<"\n";
        return 1;
    }
    if(lattices.check_game_success()){
        lattices.printLattices();
        cout<<"�ɹ�!"<<"\n";
        return 0;
    }else if (!lattices.isFull_lattices()){
        lattices.addRandom(lattices.getValue(), 1);
        if(lattices.isFull_lattices()){
            if (lattices.check_game_over()) {
                lattices.printLattices();
                cout<<"��Ϸʧ��"<<"\n";
                return 0;
            }else{
                lattices.printLattices();
                cout << "���������ƶ�!�����" << "\n";
                return 1;
            }
        } else if(!lattices.isFull_lattices()){
            lattices.printLattices();
            return 1;
        }
    }else{
        if (lattices.check_game_over()) {
            lattices.printLattices();
            cout << "��Ϸʧ��"<<"\n";
            return 0;
        }else{
            lattices.printLattices();
            cout << "���������ƶ�!�����" << "\n";
            return 1;
        }
    }
}