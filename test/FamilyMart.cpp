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
    this->now.tm_mday = 2;
    this->counts = 0;
    this->turnover = 0;
}

FamilyMart::FamilyMart(const std::string &cmmodity_file_name) {

}

void FamilyMart::purchase_file(const std::string &cmmodity_file_name) {
    const char *fileName = cmmodity_file_name.data();
    char lineData[1024] = {0};
    ifstream in;
    in.open((const char *) fileName);
    int line = 1;
    int i = 0;
//    cout << CountLines(cmmodity_file_name) << "****"<<"\n";
    Commodity *commodity1= new Commodity[CountLines(cmmodity_file_name)-1];
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
//        cout << lineData <<"\n";
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
        Commodity commodity = new Commodity();
//        cout << getExpireTime(StringToDateTime((char*)(res[3].data())),atoi(res[2].data())).tm_year <<"/" << "\n";
        commodity.setName(res[0]);
        commodity.setPrice(res[1]);
        commodity.setLife(atoi(res[2].data()));
        commodity.setProduct_date(StringToDateTime((char*)(res[3].data())));
        commodity.setExpire_date(getExpireTime(StringToDateTime((char*)(res[3].data())),atoi(res[2].data())));
        commodity.setSold(false);
        commodity1[i] = commodity;
//        cout << commodity.getName() << "////////" <<"\n";
//        cout << commodity1[i].getProduct_date().tm_year <<"/" <<commodity1[i].getProduct_date().tm_mon <<"/" <<commodity1[i].getProduct_date().tm_mday<<"\n";
//        cout << commodity1[i].getExpire_date().tm_year <<"/" <<commodity1[i].getExpire_date().tm_mon <<"/" <<commodity1[i].getExpire_date().tm_mday<<"\n";
//        cout << commodity.getProduct_date().tm_year <<"/" <<commodity.getProduct_date().tm_mon <<"/" <<commodity.getProduct_date().tm_mday<<"\n";
//        cout << commodity.getExpire_date().tm_year <<"/" <<commodity.getExpire_date().tm_mon <<"/" <<commodity.getExpire_date().tm_mday<<"\n";
        i++;
        line ++ ;
    }
    // 排除过期
    int count = 0;
    for(int j = 0;j < CountLines(cmmodity_file_name)-1;j++){
//        cout << commodity1[j].getProduct_date().tm_year <<"/" <<commodity1[j].getProduct_date().tm_mon <<"/" <<commodity1[j].getProduct_date().tm_mday<<"\n";
//        cout << commodity1[j].getExpire_date().tm_year <<"/" <<commodity1[j].getExpire_date().tm_mon <<"/" <<commodity1[j].getExpire_date().tm_mday<<"\n";
        if(!overdue(commodity1[j].getExpire_date(),now)){
            count++;
        }
    }
    // 组成新一天的商店
    Commodity *tmp = new Commodity[count+counts];
    for(int j = 0;j < counts;j++){
        tmp[j] = commodities[j];
        tmp[j].print();
    }
//    for(int j = 0;j < count;j++){
//        tmp[j+counts] = commodity1[j];
//        tmp[j+counts].print();
//    }
    int k = 0;
    for(int j = 0;j < CountLines(cmmodity_file_name)-1;j++){
        if(!overdue(commodity1[j].getExpire_date(),now)){
            tmp[counts+k] = commodity1[j];
            k++;
        }
    }
    commodities = tmp;
    counts = counts+count;

    Quick_Sort(commodities,0,counts-1);
//    for(int j = 0;j < counts ;j++){
//        cout << commodities[j].getExpire_date().tm_year << "/" << commodities[j].getExpire_date().tm_mon << "/" <<commodities[j].getExpire_date().tm_mday <<"\n";
//    }
    in.close();
}

void FamilyMart::sell_file(const std::string &sellFile) {
    const char *fileName = sellFile.data();
    char lineData[1024] = {0};
    ifstream in;
    in.open((const char *) fileName);
    int line = 1;
    int i = 0;
    cout << CountLines(sellFile) << "****" << "\n";
    CommoditySold *commoditySold = new CommoditySold[CountLines(sellFile)-1];
    while (in.getline(lineData, 1024)) {
        if (strlen(lineData) == 0) {
            continue;
        }
        if (line == 1) {
            line++;
            continue;
        }
        cout << lineData << "\n";
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
        commoditySold[i] = commoditySold1;
        i++;
        line ++ ;
    }
    for(int j = 0;j < CountLines(sellFile)-1;j++){
        for(int k = 0;k < counts;k++){
            if(commoditySold[j].getCommodity_name() == commodities[k].getName()){
                commodities[k].setSold(true);
                commodities[k].print();
                double sellPrice = atof((commodities[k].getPrice()).data()) * (commoditySold[j].getDiscount());
                cout << "出售价格:" << sellPrice << "\n";
                turnover = turnover + sellPrice;
                break;
            }else if(k == counts-1){
                cout << commoditySold[j].getCommodity_name() << "已经卖完了!" << "\n";
            }
        }
    }
}

double FamilyMart::show_turnover() {
    int count = 0;
    for(int i = 0;i < counts;i++){
        commodities[i].print();
        if(!commodities[i].getSold()){
            count++;
        }
    }
    Commodity *commodity = new Commodity[count];
    int j = 0;
    for(int i = 0;i < counts;i++){
        if(!commodities[i].getSold()){
            commodity[j] = commodities[i];
            j++;
        }
    }
    commodities = commodity;
    counts = count;
    return this->turnover;
}

int FamilyMart::CountLines(const std::string &fileName1) {
    const char *fileName = fileName1.data();
    char lineData[1024] = {0};
    ifstream in;
    in.open((const char *) fileName);
    int line = 0;
    while (in.getline(lineData,1024)) {
        if(strlen(lineData) == 0){
            continue;
        }
        line++;
    }
    return line;
}

tm FamilyMart::StringToDateTime(char *p) {
    tm tm_;                                    // 定义tm结构体。
    int year, month, day;// 定义时间的各个int临时变量。
    sscanf(p, "%d/%d/%d", &year, &month, &day);// 将string存储的日期时间，转换为int临时变量。
    tm_.tm_year = year;// 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
    tm_.tm_mday = day;                         // 日。
    return tm_;
}

tm FamilyMart::getExpireTime(tm tm_, int life) {
    int year = tm_.tm_year;
    int month = tm_.tm_mon;
    int day = tm_.tm_mday;
//    cout << year <<"/" << month << "/" <<day << "-------------------" <<"\n";
    if(bigMonth(month)){
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
//    cout << year <<"/" << month << "/" <<day << "+++++++++++++++++++" <<"\n";
//    cout << tm_.tm_year <<"/" << tm_.tm_mon << "/" <<tm_.tm_mday << "****************" <<"\n";
    return tm_;
}

bool FamilyMart::bigMonth(int month) {
    return (month == 1)||(month == 3)||(month == 5)||(month == 7)||(month == 8)||(month == 10)||(month == 12);
}

bool FamilyMart::overdue(tm tm_, tm tm_now) {
    if(tm_.tm_year < tm_now.tm_year){
        cout << tm_.tm_year << "/" << tm_.tm_mon << "/" << tm_.tm_mday <<"\n";
//        cout << "该商品过期了" <<"\n";
        return true;
    }else if((tm_.tm_year = tm_now.tm_year)&&(tm_.tm_mon < tm_now.tm_mon)){
//        cout << "该商品过期了" <<"\n";
        return true;
    }else if((tm_.tm_year = tm_now.tm_year)&&(tm_.tm_mon = tm_now.tm_mon)&&(tm_.tm_mday <= tm_now.tm_mday)){
        cout << "该商品过期了" <<"\n";
        return true;
    }
//    cout << "该商品未过期" <<"\n";
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

int FamilyMart::getCounts() {
    return this->counts;
}

void FamilyMart::setCounts(int mCounts) {
    this->counts = mCounts;
}

void FamilyMart::Quick_Sort(Commodity *a, int left, int right) {
    if (left< right)
    {
        int i = left, j = right;
        Commodity temp = a[left];
        while (i < j)
        {
            while (i < j && (!compare(a[j].getExpire_date(),temp.getExpire_date()))) // 从右向左找第一个小于x的数
                j--;
            if (i < j) {
                a[i] = a[j];
                i++;
            }
            while (i < j && (compare(a[i].getExpire_date(), temp.getExpire_date()))) // 从左向右找第一个大于等于x的数
                i++;
            if (i < j) {
                a[j] = a[i];
                j--;
            }
        }
        a[i] = temp;
        Quick_Sort(a, left, i - 1); // 递归调用
        Quick_Sort(a, i + 1, right);
    }
}