//
// Created by 22332 on 2021/5/18.
//

#ifndef TEST_FAMILYMART_H
#define TEST_FAMILYMART_H


#include <string>
#include "Commodity.h"
#include <vector>

class FamilyMart {
public:
    FamilyMart();  // no any commodity

    // using file name to construct FamilyMart
    // the format of file is the same as purchase.txt
    FamilyMart(const std::string& cmmodity_file_name);

    // using file name add new commodities in every morning, the format of file is the same as purchase.txt
    void purchase_file(const std::string& cmmodity_file_name);

    //the same as above, this is sell process
    void sell_file(const std::string& sellFile);

    //return a total sales, a turnover snice the start of new FamilyMart.
    double show_turnover();

    // ... your other function

    tm StringToDateTime(char* p);//将字符数组转化为时间

    tm calculateDate(tm tm_,int life);//得到tm+life天后的日期

    bool isBigMonth(int month);//判断是否是大月

    bool overdue(tm tm_,tm tm_now);//判断是否过期

    bool compare(tm tm_1,tm tm_2); //比较两个日期，小于就true

    void quick_sort(Commodity a[], int left, int right);//快速排序
private:
    // some attributes
    tm now;//当前全家的日期
    vector<Commodity> martVector;//存储到当前日期的全家商品
    double turnover;//截至当前日期的利润
};


#endif //TEST_FAMILYMART_H
