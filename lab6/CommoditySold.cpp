//
// Created by 22332 on 2021/5/20.
//

#include "CommoditySold.h"

CommoditySold::CommoditySold() {

}

string CommoditySold::getCommodity_name() {
    return this->commodity_name;
}

double CommoditySold::getDiscount() {
    return this->discount;
}

void CommoditySold::setCommodity_name(string mCommodity_name) {
    this->commodity_name = mCommodity_name;
}

void CommoditySold::setDiscount(double mDiscount) {
    this->discount = mDiscount;
}

CommoditySold::CommoditySold(CommoditySold *pSold) {

}
