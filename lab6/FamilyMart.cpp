//
// Created by 22332 on 2021/5/18.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "FamilyMart.h"
#include "CommoditySold.h"

using namespace std;
FamilyMart::FamilyMart() {
    this->now.tm_year = 2021;
    this->now.tm_mon = 5;
    this->now.tm_mday = 1;
    this->turnover = 0;
}

FamilyMart::FamilyMart(const std::string &cmmodity_file_name) {

}

void FamilyMart::purchase_file(const std::string &cmmodity_file_name) {
    now = calculateDate(now,1);
    const char *fileName = cmmodity_file_name.data();
    char lineData[1024] = {0};
    ifstream in;
    in.open((const char *) fileName);
    int line = 1;
    int i = 0;
    while (in.getline(lineData,1024))
    {
        if(strlen(lineData) == 0){
            continue;
        }
        if (line == 1)
        {
            line++;
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
        //输出res
        Commodity commodity = Commodity(res[0],res[1],atoi(res[2].data()),StringToDateTime((char*)(res[3].data())), false,calculateDate(StringToDateTime((char*)(res[3].data())),atoi(res[2].data())));
        martVector.push_back(commodity);
        i++;
        line ++ ;
    }
    in.close();
    // 排除过期
    std::vector<Commodity>::iterator iter;
    for( iter = martVector.begin(); iter != martVector.end(); ){
         Commodity tmp = *iter;
         if(overdue(tmp.getExpire_date(),now) ){
             iter = martVector.erase(iter);
         }else{
             ++iter;
         }
    }

    Commodity *commodities = new Commodity[martVector.size()];

    //cout << martVector.size() << "----------------" << '\n';
    int j = 0;
    std::vector<Commodity>::iterator iter1;
    for( iter1 = martVector.begin(); iter1 != martVector.end(); ){
        Commodity tmp = *iter1;
        commodities[j] = tmp;
        j++;
        iter1++;
    }
    quick_sort(commodities,0,martVector.size()-1);
    int size = martVector.size();
    martVector.clear();
    for(int k = 0;k < size;k++){
        martVector.push_back(commodities[k]);
    }
    std::vector<Commodity>::iterator iter2;
    for( iter2 = martVector.begin(); iter2 != martVector.end(); ){
        Commodity tmp = *iter2;
        iter2++;
        tmp.print();
    }
}

void FamilyMart::sell_file(const std::string &sellFile) {
    const char *fileName = sellFile.data();
    char lineData[1024] = {0};
    ifstream in;
    in.open((const char *) fileName);
    int line = 1;
    int i = 0;
    vector<CommoditySold> mVector;
    while (in.getline(lineData, 1024)) {
        if (strlen(lineData) == 0) {
            continue;
        }
        if (line == 1) {
            line++;
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
        //输出res
//        for (int j = 0; j < res.size(); j++) {
//            cout << res[j] << endl;
//        }
        CommoditySold commoditySold1 = new CommoditySold();
        commoditySold1.setCommodity_name(res[0]);
        if(res.size() == 1){
            commoditySold1.setDiscount(1);
        }else{
            commoditySold1.setDiscount( atof(res[1].data()));
        }
        mVector.push_back(commoditySold1);
        i++;
        line ++ ;
    }
    std::vector<Commodity>::iterator iter;
    std::vector<CommoditySold>::iterator iter1;
    for( iter1 = mVector.begin(); iter1 != mVector.end(); ){
        CommoditySold commoditySold = *iter1;
        for( iter = martVector.begin(); iter != martVector.end(); ) {
            Commodity tmp = *iter;
            if(tmp.getName() == commoditySold.getCommodity_name()){
                martVector.erase(iter);
                double sellPrice = atof((tmp.getPrice()).data()) * (commoditySold.getDiscount());
                cout << "出售价格:" << sellPrice << "\n";
                turnover = turnover + sellPrice;
                break;
            }
            iter++;
        }
        iter1++;
    }
}

double FamilyMart::show_turnover() {

    return this->turnover;
}

tm FamilyMart::calculateDate(tm tm_, int life) {
    int year = tm_.tm_year;
    int month = tm_.tm_mon;
    int day = tm_.tm_mday;
//    cout << year <<"/" << month << "/" <<day << "-------------------" <<"\n";
    if(isBigMonth(month)){
        day = day + life;
        if(day > 31){
            month++;
            day = day- 31;
            if(month > 12){
                month = month - 12;
                year++;
            }
        }
    }else if(month == 2){
        day = day + life;
        if(day > 28){
            month++;
            day = day -28;
        }
    }else{
        day = day+life;
        if(day > 30){
            month++;
            day = day - 30;
            if(month > 12){
                month = month - 12;
                year++;
            }
        }
    }
    tm_.tm_year = year;
    tm_.tm_mon = month;
    tm_.tm_mday = day;
    return tm_;
}

bool FamilyMart::isBigMonth(int month) {
    return (month == 1)||(month == 3)||(month == 5)||(month == 7)||(month == 8)||(month == 10)||(month == 12);
}

bool FamilyMart::overdue(tm tm_, tm tm_now) {
    if(tm_.tm_year < tm_now.tm_year){
        cout << tm_.tm_year << "/" << tm_.tm_mon << "/" << tm_.tm_mday <<"\n";
        cout << "该商品过期了" <<"\n";
        return true;
    }else if((tm_.tm_year = tm_now.tm_year)&&(tm_.tm_mon < tm_now.tm_mon)){
        cout << "该商品过期了" <<"\n";
        return true;
    }else if((tm_.tm_year = tm_now.tm_year)&&(tm_.tm_mon = tm_now.tm_mon)&&(tm_.tm_mday <= tm_now.tm_mday)){
        cout << "该商品过期了" <<"\n";
        return true;
    }
    cout << "该商品未过期" <<"\n";
    return false;
}

bool FamilyMart::compare(tm tm_1, tm tm_2) {
    if(tm_1.tm_year < tm_2.tm_year){
        return true;
    }else if((tm_1.tm_year = tm_2.tm_year)&&(tm_1.tm_mon < tm_2.tm_mon)){
        return true;
    }else if((tm_1.tm_year = tm_2.tm_year)&&(tm_1.tm_mon = tm_2.tm_mon)&&(tm_1.tm_mday < tm_2.tm_mday)){
        return true;
    }
    return false;
}

void FamilyMart::quick_sort(Commodity *a, int left, int right) {
    if (left< right)
    {
        int i = left, j = right;
        Commodity temp = a[left];
        while (i < j)
        {
            while (i < j && (!compare(a[j].getExpire_date(),temp.getExpire_date()))) // 从右向左找第一个小于temp的数
                j--;
            if (i < j) {
                a[i] = a[j];
                i++;
            }
            while (i < j && (compare(a[i].getExpire_date(), temp.getExpire_date()))) // 从左向右找第一个大于等于temp的数
                i++;
            if (i < j) {
                a[j] = a[i];
                j--;
            }
        }
        a[i] = temp;
        quick_sort(a, left, i - 1); // 递归调用
        quick_sort(a, i + 1, right);
    }
}

tm FamilyMart::StringToDateTime(char *p) {
    tm tm_;                                           // 定义tm结构体。
    int year, month, day;                             // 定义时间的各个int临时变量。
    sscanf(p, "%d/%d/%d", &year, &month, &day);// 将string存储的日期时间，转换为int临时变量。
    tm_.tm_year = year;                               // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month;                               // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
    tm_.tm_mday = day;                                // 日。
    return tm_;
}
