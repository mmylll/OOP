//
// Created by 22332 on 2021/5/29.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include "bigNum.h"

/**
 * 19302010058_李正阳
 */
bigNum::bigNum() {

}

//反着存进去方便计算
bigNum::bigNum(char *input) {
        length =  strlen(input);
        for(int i = 0;i < length;i++){
            array[i] = input[length-1-i] - '0';
        }
}

bigNum::bigNum(bigNum &a) : length(a.length) {
    for(int i = 0;i < a.length;i++){
        array[i] = a.array[i];
    }
}

void bigNum::operator+(bigNum& a) {
    bigNum t(*this);
    bigNum big = a.length > length ? a : t;
    bigNum small = a.length <= length ? a : t;

    for(int i = 0;i < big.length;i++){
        big.array[i] = big.array[i] + small.array[i];
    }
    // 进位
    for(int i = 0;i < big.length;i++){
        if(big.array[i] > 9){
            big.array[i] = big.array[i] - 10;
            big.array[i+1]++;
        }
    }
    if(big.array[big.length] > 0){
        big.length = big.length+1;
    }

    big.print();
}

void bigNum::operator-(bigNum& a) {
    // 确定是绝对值大的-绝对值小的，并且判断最终正负
    bool positiveNumber  = true;
    bigNum t(*this);
    bigNum big;
    bigNum small;
    if(a.length != t.length) {
        big = a.length > length ? a : t;
        small = a.length <= length ? a : t;
    }
    if(big.length > t.length){
        positiveNumber = false;
    }
    if(a.length == t.length){
        for(int i = a.length-1;i >= 0;i--){
            if(a.array[i] > t.array[i]){
                big = a;
                small = t;
                positiveNumber = false;
                break;
            }else{
                if(a.array[i] < t.array[i]){
                    small = a;
                    big = t;
                    break;
                }
                if(a.array[i] == t.array[i]){
                    if(i == 0){
                        cout << 0 << '\n';
                        return;
                    }
                    continue;
                }
            }
        }
    }

    for(int i = 0; i < small.length; i++){
        big.array[i] = big.array[i] - small.array[i];
    }
    // 退位
    for(int i = 0; i < big.length-1;i++){
        if(big.array[i] < 0){
            big.array[i] = 10 + big.array[i];
            big.array[i+1]--;
        }
    }
    if(big.array[big.length-1] == 0){
        big.length --;
    }
    // 处理最后结果
    if (!positiveNumber){
        big.array[big.length-1] = 0 - big.array[big.length-1];
    }
    big.print();
}

istream &operator>>(istream &in, bigNum a) {
    for(int i = 0;i < a.length;i++){
        cin >> a.array[a.length-1-i];
    }
    return in;
}

ostream &operator<<(ostream & out, bigNum a) {
   for(int i = 0;i < a.length;i++){
       out << a.array[a.length-1-i];
   }
    return out;
}


// 反着输出
void bigNum::print() {
    ofstream OutFile;
    OutFile.open("lab7.out",ios::out | ios::in | ios::app);
    for(int i = 0;i < length; i++){
        cout << array[length-i-1];
        OutFile << array[length-i-1];
    }
    cout << "\n";
    OutFile << "\n";
    OutFile.close();
}