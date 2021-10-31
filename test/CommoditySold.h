//
// Created by 22332 on 2021/5/20.
//

#ifndef TEST_COMMODITYSOLD_H
#define TEST_COMMODITYSOLD_H

#include <string>

using namespace std;
class CommoditySold {
private:
    string commodity_name;
    double discount;

public:
    CommoditySold();

    string getCommodity_name();

    double getDiscount();

    void setCommodity_name(string mCommodity_name);

    void setDiscount(double mDiscount);

    CommoditySold(CommoditySold *pSold);
};

#endif //TEST_COMMODITYSOLD_H
