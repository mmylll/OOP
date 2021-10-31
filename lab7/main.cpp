#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "bigNum.h"

// 自己编写的测试文件，读取sample.in输出到lab7.out
/**
 * 19302010058_李正阳
 */
using namespace std;
int main() {
    char lineData[1024] = {0};
    ifstream in;
    in.open("test.in");
    fstream file("lab7.out", ios::out);
    vector<vector<string>> vector1;
    while (in.getline(lineData,1024)) {
        if (strlen(lineData) == 0) {
            continue;
        }
        //用于存放分割后的字符串
        vector<string> res;
        //暂存从word中读取的字符串
        string result;
        //将字符串读到input中
        stringstream input;
        input << lineData;
        //依次输出到result中，并存入res中
        while (input >> result)
            res.push_back(result);
        vector1.push_back(res);
    }
    for(int i = 0;i < vector1.size();i++) {
//        if ((vector1[i].size() == 1) && (vector1[i + 1].size() == 1) && (vector1[i + 1][0] == ">>")) {
//            if(strlen(vector1[i][0].data()) > MAXSIZE){
//                i = i+2;
//                cout << "warning:it's too long" << "\n";
//                continue;
//            }
//            char *input = (char *) vector1[i][0].data();
//            bigNum bigNum1(input);
//            bigNum1.print();
//            i = i + 2;
//            continue;
        if ((vector1[i].size() == 1) && (vector1[i][0] == ">>")) {
            char input[1024] = {0};
            cin>>input;
            if (strlen(input) > 100) {
                printf("%s","warning:it's too long");
                continue;
            }
            bigNum bigNum1(input);
            bigNum1.print();
            continue;
        } else if ((vector1[i].size() == 2) && (vector1[i][0] == "<<")) {
            if(strlen(vector1[i][1].data()) > MAXSIZE){
                i++;
                cout << "warning:it's too long" << "\n";
                continue;
            }
            char *input = (char *) vector1[i][1].data();
            bigNum bigNum1(input);
            bigNum1.print();
            continue;
        }else if(vector1[i].size() == 3){
            if((strlen(vector1[i][0].data()) > MAXSIZE)||(strlen(vector1[i][2].data()) > MAXSIZE)){
                cout << "warning:it's too long" << "\n";
                continue;
            }
            if(vector1[i][1] == "+"){
                char *input1 = (char *) vector1[i][0].data();
                bigNum bigNum1(input1);
                char *input2 = (char *) vector1[i][2].data();
                bigNum bigNum2(input2);
                bigNum1.operator+(bigNum2);
                continue;
            }
            if(vector1[i][1] == "-"){
                char *input1 = (char *) vector1[i][0].data();
                bigNum bigNum1(input1);
                char *input2 = (char *) vector1[i][2].data();
                bigNum bigNum2(input2);
                bigNum1.operator-(bigNum2);
                continue;
            }
        }
    }
}
