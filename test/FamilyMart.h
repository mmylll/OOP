//
// Created by 22332 on 2021/5/18.
//

#ifndef TEST_FAMILYMART_H
#define TEST_FAMILYMART_H


#include <string>
#include "Commodity.h"

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

    int CountLines(const std::string &fileName1);//读取文件行数

    tm StringToDateTime(char* p);//将字符数组转化为时间

    //Commodity*
    tm getExpireTime(tm tm_,int life);

    bool bigMonth(int month);

    bool overdue(tm tm_,tm tm_now);

    bool compare(tm tm_1,tm tm_2); //小于就true

    int getCounts();

    void setCounts(int mCounts);

    void Quick_Sort(Commodity a[], int left, int right);//快速排序
private:
    // some attributes
    tm now;
    Commodity *commodities;
    int counts;
    double turnover;
};


#endif //TEST_FAMILYMART_H
