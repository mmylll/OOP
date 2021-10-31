//
// Created by 22332 on 2021/5/18.
//

#ifndef TEST_COMMODITY_H
#define TEST_COMMODITY_H

#include <ctime>
#include <string>
#include <vector>
// 商品类
using namespace std;
class Commodity {
private:

    string name;
    string price;
    int life;
    tm product_date;
    bool hasSold;
    tm expire_date;

public:
    Commodity(string mName,string mPrice,int mLife,tm mProduct_date,bool mHasSold,tm mExpire_date);

    Commodity(Commodity *pCommodity);

    Commodity();

    string getName();

    string getPrice();

    int getLife();

    tm getProduct_date();

    bool getSold();

    tm getExpire_date();

    void setName(string mName);

    void setPrice(string mPrice);

    void setLife(int mLife);

    void setProduct_date(tm mProduct_date);

    void setSold(bool sold);

    void setExpire_date(tm tm_);

    void print();
};


#endif //TEST_COMMODITY_H
