//
// Created by 22332 on 2021/5/18.
//

#include "Commodity.h"
#include <iostream>

Commodity::Commodity(string mName,string mPrice,int mLife,tm mProduct_date,tm mExpire_date,bool sold) {
    this->name = mName;
    this->price = mPrice;
    this->life = mLife;
    this->hasSold = sold;
    this->product_date.tm_year = mProduct_date.tm_year;
    this->product_date.tm_mon = mProduct_date.tm_mon;
    this->product_date.tm_mday = mProduct_date.tm_mday;
    this->expire_date.tm_year = mExpire_date.tm_year;
    this->expire_date.tm_mon = mExpire_date.tm_mon;
    this->expire_date.tm_mday = mExpire_date.tm_mday;
}

Commodity::Commodity(Commodity *pCommodity) {

}

Commodity::Commodity() {

}

string Commodity::getName() {
    return this->name;
}

string Commodity::getPrice() {
    return this->price;
}

int Commodity::getLife() {
    return this->life;
}

tm Commodity::getProduct_date() {
    return this->product_date;
}

void Commodity::setName(string mName) {
    this->name = mName;
}

void Commodity::setPrice(string mPrice) {
    this->price = mPrice;
}

void Commodity::setLife(int mLife) {
    this->life = mLife;
}

void Commodity::setProduct_date(tm mProduct_date) {
    this->product_date = mProduct_date;
}

bool Commodity::getSold() {
    return this->hasSold;
}

void Commodity::setSold(bool sold) {
    this->hasSold = sold;
}

tm Commodity::getExpire_date() {
    return this->expire_date;
}

void Commodity::setExpire_date(tm tm_) {
    this->expire_date = tm_;
}

void Commodity::print() {
    cout << "-------------------" <<"\n";
    cout << "name:" << this->name <<"  ";
    cout << "price:" << this->price <<"  ";
    cout << "life:" << this->life <<"  ";
    cout << "product_date:" << this->product_date.tm_year << "/" << this->product_date.tm_mon << "/" << this->product_date.tm_mday <<"  ";
    cout << "expire_date:" << this->expire_date.tm_year << "/" << this->expire_date.tm_mon << "/" << this->expire_date.tm_mday <<"  ";
    cout << "ÊÇ·ñÂô³ö:" << this->hasSold << "  ";
    cout << "-------------------" <<"\n";

}
