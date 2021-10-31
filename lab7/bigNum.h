//
// Created by 22332 on 2021/5/29.
//

#ifndef LAB7_BIGNUM_H
#define LAB7_BIGNUM_H

#include <istream>

#define MAXSIZE 100 //数组最大长度

/**
 * 大数类
 * 特别注意：为了方便计算array里面的数字顺序是反着的，查看的时候需要自己调整过来
 * 19302010058_李正阳
 */
using namespace std;
class bigNum {
private:
    int length = 0;//数组中有效位数的长度
    int array[MAXSIZE] = {0}; // 存放截取的单个字符

public:
    bigNum();

    bigNum(char *input);//将截取的字符串转换成数字存进数组

    bigNum(bigNum& a); //拷贝构造函数

    void operator+(bigNum& a);   //重载加法运算符，两个大数之间的相加运算

    void operator-(bigNum& a);   //重载减法运算符，两个大数之间的相减运算

    friend istream& operator>>(istream& in, bigNum a);   //重载输入运算符

    friend ostream& operator<<(ostream& out, const bigNum a);   //重载输出运算符

    void print();// 打印本对象的array

};


#endif //LAB7_BIGNUM_H
