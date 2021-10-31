#include <iostream>
#include "FamilyMart.h"

using namespace std;
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    FamilyMart *test_mart = new FamilyMart();
//    string filename1,filename2;
//    std::cout << "Today is beginning" << std::endl;
//    std::cout << "please input purchase list file name" << std::endl;
//    std::cin>>filename1;
//    test_mart->purchase_file(filename1);
//    std::cout << "input sell list file name" << std::endl;
//    std::cin>>filename2;
//    test_mart->sell_file(filename2);
//    std::cout << "This day is over" << std::endl;
//    std::cout << "turnover:" << test_mart->show_turnover() << std::endl;

//    cout << (5+4-1)/4 << "\n";
//     char a = '6';
//     int b = a-'0';
//     cout << b <<"\n";
//    return 0;
//}

//int dog=1, cat=2, bir=3, fis=4;
//int main() {
//    int i=0, j=1, k=2;
//    int *p;
//    p = &dog;
//    cout << *(p+1) << endl;
//    p = &k;
//    cout << *(p+1) << endl;
//}

//void f(int a) {
//    cout << "a = " << a << endl;
//    a = 5;
//    cout << "a = " << a << endl; }
//int main() {
//    int x = 47;
//    cout << "x = " << x << endl;
//    f(x);
//    cout << "x = " << x << endl;
//}

//class Test
//{
//public:
//    int a;
//    int b;
//};
//void func(Test test){
//    test.a = 2;
//    cout << test.a << endl; }
//int main() {
//    Test test;
//    test.a = 1;
//    cout << test.a << endl;
//    func(test);
//    cout << test.a << endl;
//}

//void f(int* p) {
//    cout << "p = " << p << endl;
//    cout << "*p = " << *p << endl;
//    *p = 5;
//    cout << "p = " << p << endl; }
//int main() {
//    int x = 47;
//    cout << "x = " << x << endl;
//    cout << "&x = " << &x << endl;
//    f(&x);
//    cout << "x = " << x << endl;
//}

//void f(int& r) {
//    cout << "r = " << r << endl;
//    cout << "&r = " << &r << endl;
//    r = 5;
//    cout << "r = " << r << endl; }
//int main() {
//    int x = 47;
//    cout << "x = " << x << endl;
//    cout << "&x = " << &x << endl;
//    f(x); // Looks like pass-by-value, is actually pass by reference
//    cout << "x = " << x << endl;
//}

//typedef struct Structure3 {
//    char c;
//    int i;
//    float f;
//    double d;
//} Structure3;
//
//int main() {
//    Structure3 s1, s2;
//    Structure3* sp = &s1;
//    sp->c = 'a';
//    sp->i = 1;
//    sp->f = 3.14;
//    sp->d = 0.00093;
//    sp = &s2; // Point to a different struct object
//    sp->c = 'a';
//    sp->i = 1;
//    sp->f = 3.14;
//    sp->d = 0.00093;
//    (*sp).d = 0.2;
//}


//}

//void change(int &x, int &y)
//{ int t;
//    int z = 20;
//    t=x; x=y; y=z;
//}
//int main(void)
//{ int a=3,b=5;
//    change(a,b); //实参为变量
//    cout<<a<<"\t"<<b<<endl;
//}

class Data {
public:
    int a, b, c;
    void print() const {
        cout << "a = " << a << ", b = " << b << ", c = " << c << endl; }
};
int main() {
    Data d, *dp = &d;
    int Data::*pmInt = &Data::a;
    dp->*pmInt = 47;
    pmInt = &Data::b; d.*pmInt = 48;
    pmInt = &Data::c;
    dp->*pmInt = 49;
    dp->print();
}